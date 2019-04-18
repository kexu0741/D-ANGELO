#include <iostream>
#include <fstream>
#include <sstream>
#include "MaxHeap.hpp"
// #include "playerStruct.h"
// #include "MaxHeap.hpp"
//#include "MaxHeap.cpp"
#include <vector>

using namespace std;

void printInstructions(){
	cout << "-----------------------------------------------------" << endl;
	cout << "D'ANGELO is an analytic tool for NBA scouts, general " << endl;
	cout << "managers, and draft enthusiasts." << endl;
	cout << endl;
	cout << "The user will go pick by pick, controlling all teams," << endl;
	cout << "selecting players. The user will be prompted initially" << endl;
	cout << "with two options: auto pick the best available player," << endl;
	cout << "or select a player based on team needs." << endl;
	cout << "The user will be prompted with team needs, and as more" << endl;
	cout << "needs are entered, D'ANGELO will give the user the best" << endl;
	cout << "available player based on these team needs." << endl;
	cout << endl;
	cout << "Happy drafting!" << endl;
	cout << "-----------------------------------------------------" << endl;

}

void displayStartingMenu(){
	for (int i = 0; i < 10; i++)
		cout << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Welcome to the D'ANGELO NBA Draft emulator- " << endl;
	cout << "a tool for scouting the next generation of NBA talent" << endl;
	cout << "-----------------------------------------------------" << endl;

	for (int i = 0; i < 5; i++)
		cout << endl;

	bool start = false;
	string startInput;
	string prompt;

	while (!start){
		cout << "1. Instructions" << endl;
		cout << "2. Enter D'ANGELO" << endl;

		getline(cin, startInput);

		if (startInput == "1" || startInput == "2"){
			if (startInput == "1"){
				printInstructions();
			}
			if (startInput == "2"){
				start = true;
			}
		}	
		else{
			cout << "invalid input." << endl;
		}
	}
}

//FOR ADDING TO HEAP: CALL CREATEPLAYER

//file format: PPG, FG%, 3PT%, FT%, APG, RPG, SPG, BPG, TOVPG, AST/TO ratio
//STL/TO (steals to turnovers), BLK/TO(Blocks to turnovers), scoring efficiency
//Shooting efficiency, personal fouls per game, Games played

int main(){
	displayStartingMenu();

	ifstream in;
	in.open("stats.csv");

	string line;
	string token;
	char delim = ',';

	MaxHeap test(100);

	vector<string> components;
	string strComponents[5];
	int strCnt = 0;
	double dblComponents[15];
	int dblCnt = 0;

	while (getline(in, line)){
		stringstream ss(line);
		while (getline(ss, token, delim)){
			components.push_back(token);
		}
		for (int i = 0; i < components.size(); i++){
			if (i == 0 || i == 1 || i == 2 || i == 3 || i == 19){
				strComponents[strCnt] = components[i];
				strCnt++;
			}
			else{
				if (components[i] == "N/A"){
					dblComponents[dblCnt] = 0;
				}
				else{
					dblComponents[dblCnt] = stod(components[i]);
				}
				dblCnt++;
			}
		}

		test.createPlayer(strComponents, dblComponents, 420);

		strCnt = 0;
		dblCnt = 0;
		components.clear();
	}

	for (int i = 0; i < 10; i++){
		cout << test.extractMax()->name << " -----> " << test.extractMax()->ppg << endl;
	}




	return 0;
}