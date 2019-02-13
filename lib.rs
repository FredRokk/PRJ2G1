/*
    

    Glitch: It uses the state from the left channel on the right channel and vice versa,
    which creates problems when in stereo. 
    Probably needs to have states for both channels. <- Made mono for now

    TODO: newton_raphson_solver needs an overhaul

    Jacobian matrix needs to be updated
    Inverse of jacobian matrix will always be 0. We need the functions to be reliant on each other, or 
    another implementation of Newton's method
    http://benisrael.net/InverseFreeMethod.pdf   <-- implement this guy instead
    https://arxiv.org/ftp/math/papers/9906/9906055.pdf <-- this guy could be less processor intensive

    TODO: Make a steep FIR filter at nyquist/2 (struct in other file?)

        
*/
 #[macro_use] extern crate vst;
use vst::buffer::AudioBuffer;
use vst::plugin::{Info, Plugin, Category};


#[derive(PartialEq)]
enum EstimateSource //for testing to find the best estimate
{
    State,                      // use current state
    PreviousVout,               // use z-1 of vout[n]
    LinearStateEstimate,        // use linear estimate of future state
    LinearVoutEstimate,         // use linear estimate of vout[n]
}
#[derive(PartialEq)]
enum AnalyticalMethod 
{
    Linear,							// linear solution
	Pivotal,						// Mystran's "cheap" method, using x=0 as pivot
}

//if you want the derivative of tanh(x), put the tanh(x) into this function. Must already be tanh'd
fn derive_tanh_value(tanh_value: f32) -> f32 {
    //tanh'(x) = 1 - tanh^2(x)
    1. - tanh_value * tanh_value
}
//needed for newton's method with multiple variables. Pretty slow. Look into SIMD for optimization
fn times_inverse_matrix(fn_matrix: [f32; 4], mut jacobian_matrix: [[f32; 4]; 4])  -> [f32; 2] {

 
    //times reciprocal of determinant
    let determinant_recip = (jacobian_matrix[0][0] * jacobian_matrix[1][1] -
    jacobian_matrix[1][0] * jacobian_matrix[0][1]).recip();
    for row in 0..2 {
        for col in 0..2 {
            jacobian_matrix[row][col] = jacobian_matrix[row][col] * determinant_recip;
        }
    }
    //then multiply them together
    [
        fn_matrix[0] * jacobian_matrix[0][0] + fn_matrix[1] * jacobian_matrix[0][1],
        fn_matrix[0] * jacobian_matrix[1][0] + fn_matrix[1] * jacobian_matrix[1][1]
    ]

}
//this is a 4-pole filter with resonance, which is why there's 4 states and vouts
struct DecentFilter
{
    //stands in as the output of the filter, since it needs to be edited a bunch of places
    vout: [f32; 4],

    //s is the "state" parameter. it's normally the last value from the filter (buf0 in the last filter)
    //found by trapezoidal integration in a zero-delay feedback filter
    s: [f32; 4],
    //used to avoid calling .tanh() too much. saves CPU
    tanh_result: [f32; 4],
    //the "cutoff" parameter. Determines how heavy filtering is
    g: f32,
    //needed to calculate cutoff. Should get it from the host instead of just setting it to 44.1k
    sample_rate: f32,
    //where the filtering starts
    cutoff: f32,

    //makes a peak at cutoff
    res: f32,
    //used to choose if we want it to output 1 or 2 order filtering
    poles: usize,
    oversample: usize,
    upsample_array: [f32; 4],
    dyn_error_factor: f32

}
//member methods for the struct
impl DecentFilter
{
    //the state needs to be updated after each process.
    fn update_state(& mut self)
    {
        self.s[0] = 2. * self.vout[0] - self.s[0];
        //the s[1] formula should be valid? found by trapezoidal integration?
        self.s[1] = 2. * self.vout[1] - self.s[1];
        self.s[2] = 2. * self.vout[2] - self.s[2];
        self.s[3] = 2. * self.vout[3] - self.s[3];
    }
    //used for getting the starting point for estimating how to compute the filtering
    fn get_initial_estimate(& mut self, input: f32, filter_order: usize, source: EstimateSource, method: AnalyticalMethod) -> f32
    {
        if  source == EstimateSource::LinearVoutEstimate || source == EstimateSource::LinearStateEstimate {
            self.run_one_step(input, method);

        }
        match source {
            EstimateSource::State => self.s[filter_order],
            EstimateSource::LinearVoutEstimate => self.vout[filter_order],
            EstimateSource::PreviousVout => self.vout[filter_order],
            EstimateSource::LinearStateEstimate => 2. * self.vout[filter_order] - self.s[filter_order],
        }
    }
    // ------------------------------ Newton's Method ------------------------------------
    //for our function,  this should always converge
    fn newton_raphson_solver(& mut self, input: f32) -> [f32; 4] {
        //the input and estimate get used in a filter to see how well the estimate works.
        let tanh_input = input.tanh();
        //after running run_one_step, vout is updated to the pivotal output, which should be a very good guess
        self.run_one_step(input, AnalyticalMethod::Pivotal);
        let mut estimate = self.vout;
        self.tanh_result = [estimate[0].tanh(), estimate[1].tanh(), estimate[2].tanh(), estimate[3].tanh()];
            //etimate = [estimate[0] - (jacobian/residue).recip()
            //residue = [runfilterwithestimate - estimate]

        let mut residue = [-(self.run_filter(input, tanh_input, estimate, 0) /*- estimate[0]*/),
        -(self.run_filter(input, tanh_input, estimate, 1)), -(self.run_filter(input, tanh_input, estimate, 2)),
        -(self.run_filter(input, tanh_input, estimate, 3)) ];
        let mut num_iterations = 1;
        //residue is compared with the highest error we'll allow
        //self.dyn_error_factor = 1. + (input - 0.0589) * 1000. + self.res;
        while residue[0].abs() > 0.000001 /* * self.dyn_error_factor*/ || residue[1].abs() > 0.000001 /* * self.dyn_error_factor*/
        {
            //estimate = estimate - (run_filter * jacobian^-1) or estimate = estimate - (residue * jacobian^-1)
            //derivative will be the jacobian matrix
            //let derivative = [self.get_derivative(input, tanh_input, 0), self.get_derivative(input, tanh_input, 1) ];
            let jacobian = self.jacobian(input, estimate[3]);

            //estimate = [estimate[0] - residue[0]/derivative[0], estimate[1] - residue[1]/derivative[1]];
            let result = times_inverse_matrix(residue, jacobian);
            estimate = [estimate[0] - result[0], estimate[1] - result[1], estimate[2] - result[2], estimate[3] - result[3]];
            self.tanh_result = [estimate[0].tanh(), estimate[1].tanh(), estimate[2].tanh(), estimate[3].tanh()];
            // get next residue
            residue = [-(self.run_filter(input, tanh_input, estimate, 0) - estimate[0]),
                        -(self.run_filter(input, tanh_input, estimate, 1) - estimate[1]), 
                        -(self.run_filter(input, tanh_input, estimate, 2) - estimate[2]),
                        -(self.run_filter(input, tanh_input, estimate, 3) - estimate[3])];
            num_iterations += 1;
            

            if num_iterations > 50 {
                //this should never happen. maybe figure out logging to spot this?
                //can happen if the guess is horrible or something is wrong with get_derivative
                // if input > 0. {
                //     return [1.,1.];
                // }
                // else if input == 0. {
                //     return [0., 0.,];
                // }
                // else {
                //     return [-1.,-1.];
                // }
                //i'm letting it make a loud pop if it happens lmao
                return [0.,0., 0., 0.];
            }
        }
    estimate
    }
    //the filter is meant to be used with steadily better estimates
    //when an estimate is good enough, the value can be used. newton_raphson_solver takes care of this
    fn run_filter(& mut self, input: f32, tanh_input: f32, v_estimate: [f32; 4], filter_order: usize) -> f32 {
        if filter_order == 0 {
            self.g * ((input - self.res * v_estimate[3]).tanh() - self.tanh_result[0]) + self.s[0]
        }
        else if filter_order == 1 {
            self.g * (self.tanh_result[0] - self.tanh_result[1]) + self.s[1]
        }
        else if filter_order == 2 {
            self.g * (self.tanh_result[1] - self.tanh_result[2]) + self.s[2]
        }
        else if filter_order == 3 {
            self.g * (self.tanh_result[2] - self.tanh_result[3]) + self.s[3]
        }
        else {
            //do nothing
            return 0.;
        }
    }
    //used for newton's method. matrix of partial derivatives of the run_filter functions
    fn jacobian(&self, input: f32, out_estimate: f32) -> [[f32; 4]; 4]  {
        //these variables potentially need to be turned negative. depends on if my implementation still needs it.

        let f1_y1est = self.g * (-derive_tanh_value(self.tanh_result[0])) + 1.;
        let f1_y2est = 0.;
        let f1_y3est = 0.;
        let f1_y4est = -self.g * self.res  *
        (derive_tanh_value((-input + self.res * out_estimate).tanh()));

        let f2_y1est = self.g * (derive_tanh_value(self.tanh_result[0]));
        let f2_y2est = (-derive_tanh_value(self.tanh_result[1])) * self.g + 1.;
        let f2_y3est = 0.;
        let f2_y4est = 0.;

        let f3_y1est = 0.;
        let f3_y2est = self.g * derive_tanh_value(self.tanh_result[1]);
        let f3_y3est = self.g * (-derive_tanh_value(self.tanh_result[2])) + 1.;
        let f3_y4est = 0.;

        let f4_y1est = 0.;
        let f4_y2est = 0.;
        let f4_y3est = self.g * derive_tanh_value(self.tanh_result[2]);
        let f4_y4est = self.g * (-derive_tanh_value(self.tanh_result[3])) + 1.;

        //returns the inverse jacobian matrix
        [[f4_y4est, -f1_y2est, -f1_y3est, -f1_y4est], [-f2_y1est, -f2_y2est, -f2_y3est, -f2_y4est], 
         [-f3_y1est, -f3_y2est, -f3_y3est, -f3_y4est], [-f4_y1est, -f4_y2est, -f4_y3est, f1_y1est]]
    }

    //performs a complete filter process (iteratively)
    fn tick_newton_raphson(& mut self, input: f32) /*-> f32*/ {
        //let tanh_input = input.tanh(); <- moved into newton_raphson_solver, so we can access
        //both input and tanh_input
        self.vout = self.newton_raphson_solver(input);
        self.update_state();
    }
    //performs a complete filter process (mystran's method)
    fn tick_pivotal(&mut self, input: f32) {
        //let tanh_input = input.tanh();
        self.run_one_step(input, AnalyticalMethod::Pivotal);
        self.update_state();
    }
    fn tick_linear(&mut self, input: f32) {
        self.run_one_step(input, AnalyticalMethod::Linear);
        self.update_state();
    }

    // ------------------------------ linear / analytical methods ------------------------------------
    fn  run_one_step(&mut self, input: f32, method: AnalyticalMethod)  {

        let mut a = [1f32; 5];
        if method == AnalyticalMethod::Pivotal {
            let base = [input - self.res * self.get_initial_estimate(input, 3, EstimateSource::State, AnalyticalMethod::Linear),
            self.get_initial_estimate(input, 0, EstimateSource::State, AnalyticalMethod::Linear),
            self.get_initial_estimate(input, 1, EstimateSource::State, AnalyticalMethod::Linear),
            self.get_initial_estimate(input, 2, EstimateSource::State, AnalyticalMethod::Linear),
            self.get_initial_estimate(input, 3, EstimateSource::State, AnalyticalMethod::Linear)
            ];
            //let tbase = [base[0].tanh(), base[1].tanh(),base[2].tanh()];
            for n in 0..4 {
                if base[n] != 0. {
                a[n] = base[n].tanh()/base[n];
                }
            }
            //denominators of solutions of individual stages. Simplifies the math a bit
            let g0 = 1. / (1. + self.g*a[1]); let g1 = 1. / (1. + self.g*a[2]);
            let g2 = 1. / (1. + self.g*a[3]); let g3 = 1. / (1. + self.g*a[4]);
            // these are just factored out of the feedback solution. Makes the math way easier to read
            let f3 = self.g*a[3]*g3; let f2 = self.g*a[2]*g2*f3; 
            let f1 = self.g*a[1]*g1*f2; let f0 = self.g*a[0]*g0*f1;
            //outputs a 24db filter
            self.vout[3] =  (f1 * g0 * self.s[0] + f2 * g1 * self.s[1] + f3 * g2 * self.s[2] + f0 * input + self.s[3] * g3 ) /
                            (f0 * self.res + 1.);
            //since we know the feedback, we can solve the remaining outputs: 
            self.vout[0] = a[1]* g0 * (self.g * (input - self.res * self.vout[3]) + self.s[0]);
            self.vout[1] = a[2]* g1 * (self.g * self.vout[0] + self.s[1]);
            self.vout[2] = a[3] * g2 * (self.g * self.vout[1] + self.s[2]);
        }
       
    }
}

//default values for parameters
impl Default for DecentFilter
{
    fn default() -> DecentFilter {
        DecentFilter {
            vout: [0f32; 4],
            s: [0f32; 4],
            //used to avoid calling .tanh() too much. saves CPU
            tanh_result: [0f32; 4],

            sample_rate: 44100.,
            cutoff: 1000.,
            res: 2.0,

            g:  0.07135868087,
            poles: 3,
            oversample: 4,
            upsample_array: [0f32; 4],
            dyn_error_factor: 1.,
        }
    }
}

impl Plugin for DecentFilter
{
    fn set_sample_rate(&mut self, rate: f32) {
        self.sample_rate = rate;
    }
    fn get_info(&self) -> Info
    {
        Info  {
            name: "ZeroDelayFilter".to_string(),
            unique_id: 9263,
            inputs: 1,
            outputs: 1,
            category: Category::Effect,
            parameters: 4,
            ..Default::default()
        }
    }
    fn get_parameter(&self, index: i32) -> f32 {
    match index {
        0 => self.cutoff,
        1 => self.res,
        2 => (self.poles) as f32 + 1.,
        3 => self.oversample as f32,
        _ => 0.0,
        }
    }
    fn set_parameter(&mut self, index: i32, value: f32) {
        match index {
            0 => self.cutoff = 20000. * (1.8f32.powf(10. * value - 10.)).min(0.999),
            //self.g = value * 10.,
            1 => self.res = value * 4.4,
            2 => self.poles = ((value * 3.).round()) as usize,
            3 => self.oversample = ((value * 2.).round()).exp2() as usize,
            _ => (),
        }
        //the formula for g seems to be accurate, but it could have something to do with the cutoff problem
        self.g = ( 3.1415 * self.cutoff / (self.sample_rate * self.oversample as f32)).tan();

    }

    fn get_parameter_name(&self, index: i32) -> String {
        match index {
            0 => "cutoff".to_string(),
            1 => "res".to_string(),
            2 => "filter order".to_string(),
            3 => "oversampling".to_string(),
            _ => "".to_string(),
        }
    }
    fn get_parameter_label(&self, index: i32) -> String {
        match index {
            0 => "Hz".to_string(),
            1 => "%".to_string(),
            2 => "poles".to_string(),
            3 => "times".to_string(),
            _ => "".to_string(),
        }
    }
    fn process(&mut self, buffer: &mut AudioBuffer<f32>) {
        if self.oversample > 1 {
             for (input_buffer, output_buffer) in buffer.zip() {
                for (input_sample, output_sample) in input_buffer.iter().zip(output_buffer) {
                    //self.tick_newton_raphson(*input_sample);
                    //oversampling process
                    //we oversample with a zero-stuffing process. Leaves original signal untouched, but creates
                    //a mirror image at twice the frequency
                    
                    self.upsample_array[0] = *input_sample;
                    for n in 1..self.oversample {
                    self.upsample_array[n] = 0.;
                    }
                    //after upsample process, we should use a steep lowpass to get rid of the mirror image
                    //omitted for now, since our process is a lowpass anyway. Might give trouble at high frequencies
                    for n in 0..self.oversample {

                        //self.tick_newton_raphson(self.upsample_array[n]);
                        self.tick_pivotal(self.upsample_array[n]);
                        if n == 0 {
                            *output_sample = self.vout[self.poles];
                        }
                    }
                    //self.tick_pivotal(*input_sample);
                }
            }
        }
        else {
            for (input_buffer, output_buffer) in buffer.zip() {
                for (input_sample, output_sample) in input_buffer.iter().zip(output_buffer) {
                    self.tick_pivotal(*input_sample);
                    //self.tick_linear(*input_sample);
                    //self.tick_newton_raphson(*input_sample);
                    *output_sample = self.vout[self.poles];
                }
            }
        }
    }
}
plugin_main!(DecentFilter);
