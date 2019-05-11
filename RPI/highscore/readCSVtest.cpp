#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


	class Score
	{
	public:
		Score(string n, int p, int t): name(n), points(p), time(t){};
		string name;
		int points;
		int time;
		void printScore(){
			cout << "Name: " << name << endl << "Points: " << points << endl << "Time: " << time << endl;
			cout << endl;
		}
	};

int main(){
	ifstream ip("data.csv");

	if(!ip.is_open()) cout << "File already open" << endl;

	string name = "";
	string points = "";
	string time = "";

	vector<Score> scores;

	int count = 0;

	while(ip.good()){

		getline(ip, name, ',');
		getline(ip, points, ',');
		getline(ip, time, '\n');
		scores.push_back(Score(name, stoi(points), stoi(time)));
		count++;
		name = "";
		points = "";
		time = "";
	}

	cout << "Count is " << count << endl;

	/*
	for (int i = 0; i < count; i++){
		if (i < 100 || i > 2000)
		{
		cout << "Output nr. " << i << endl;
		scores[i].printScore();
		} else if (i % 100 == 0){
			cout << "Output nr. " << i << endl;
			scores[i].printScore();
		}
	} */


}