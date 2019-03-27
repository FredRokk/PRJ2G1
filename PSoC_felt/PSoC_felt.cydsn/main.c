/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
//værdier fra 0-4 for felter? funktion der omdanner det til rgb-værdier
//læses fra venstre til højre, oppefra og ned
int FELTARRAY[9] = {1, 2, 1, 2, 3, 2, 1, 2, 1};
//sætter pins, eller sender i2c kommando, for at sætte et felts farve. <-
//^ Actually just setting fields in array for now. Need to figure out I2c before implementing that

void set_field(int field_value, int field_pos);
//score, for sending to RPI
int SCORE;

int SENSORARRAY[6] = {0, 0, 0, 0, 0, 0,};



int main(void)
{
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    for(;;)
    {
        //adds points from reading from sensors to score. 
        //needs a delay when a field is read. Maybe reset a variable when ready to fire?
        SCORE += read_sensors();
    }
}
int read_sensors() 
{
    int points;
    //assumed active low for now
    if (SENSORARRAY[0] && SENSORARRAY[4])
    {
        points = give_points(FELTARRAY[1]);
        set_field(0, 1);
    }
    if (SENSORARRAY[0] && SENSORARRAY[5])
    {
        points = give_points(FELTARRAY[4]);    
        set_field(0, 4);
    }
    if (SENSORARRAY[0] && SENSORARRAY[6])
    {
        points = give_points(FELTARRAY[7]);          
        set_field(0, 7);
    }    
    return points;
    
}
int give_points(int field_value)
{
    switch field_value {
        //0 is field off
        case 0 :
            return 0;
        case 1 : 
            return 10;
        case 2 : 
            return 25;
        case 3 : 
            return 50;
        case 4 : 
            return 100;
        default : 
            return 0;
    }
}
void set_field(int field_value, int field_pos)
{
    SENSORARRAY[field_pos] = field_value;   
}



/* [] END OF FILE */
