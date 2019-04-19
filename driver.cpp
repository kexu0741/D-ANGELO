#include <iostream>
#include <fstream>
#include <sstream>
#include "MaxHeap.hpp"
// #include "playerStruct.h"
// #include "MaxHeap.hpp"
//#include "MaxHeap.cpp"
#include <vector>

//TODO: IMPLEMENT TEAMS, IMPLEMENT MENU, MERGE AVNISH'S CODE

using namespace std;

void printInstructions(){
	cout << "-----------------------------------------------------" << endl;
	cout << "D'ANGELO is an analytical tool for NBA scouts, general " << endl;
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
	cout << endl;
	cout << "CALCULATION INFO: " << endl;
	cout << "Best overall available prospects are calculated using a modified " << endl;
	cout << "version of John Hollinger's Player Efficiency Rating (PER). " << endl;
	cout << "Multipliers are modified, as an aggregate average for every stat "<< endl;
	cout << "over all of college basketball is unfeasible." << endl;
	cout << "There is also an added multiplier based on age, in order to factor in " << endl;
	cout << "a player's 'untapped potential.'" << endl;
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

int displayDraftMenu(MaxHeap &h){ //ADD BST PARAM
	vector<player*> temp; //temp vector for printing
	for (int i = 0; i < 15; i++)
		cout << endl;
	cout << "---------------------------------------" << endl;
	cout << "Top 10 Available Prospects: " << endl;
	for (int i = 0; i < 10; i++){
		cout << i+1 << ". ";
		player* curr = h.extractMax();
		temp.push_back(curr);
		cout << curr->name << ", " << curr->position
		<< ", " << curr->college << ", " << curr->ppg << " ppg, "
		<< curr->rpg << " rpg, " << curr->apg << " astpg" << endl;
	}
	cout << "---------------------------------------" << endl;

	for (int i = 0; i < temp.size(); i++){
		h.insertPlayer(temp[i]);
	}

	temp.clear();

	for (int i = 0; i < 5; i++)
		cout << endl;
	//add while loop for input
	bool openMenu = true;
	string userInput;

	while (openMenu){
		cout << "--------------------------------------" << endl; 
		cout << "1. Auto Draft Best Available" << endl;
		cout << "2. Enter Team Needs" << endl;
		cout << "3. Search for Player" << endl;
		cout << "4. Quit draft" << endl;
		cout << "--------------------------------------" << endl; 

		getline(cin, userInput);
		player* curr;

		switch(stoi(userInput)){
			case 1:
				//delete from heap and the tree
				curr = h.extractMax();
				cout << curr->name << ", " << curr->position
				<< ", " << curr->college << ", " << curr->ppg << " ppg, "
				<< curr->rpg << " rpg, " << curr->apg << " astpg " 
				<< "---- drafted. " << endl;

			break;

			case 2:
				//new menu
			break;

			case 3:
				//call for BST
			break;

			case 4:
				//exits from menu
			openMenu = false;
			break;

		}

		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "Top 10 Available Prospects: " << endl;

		for (int i = 0; i < 10; i++){
			cout << i+1 << ". ";
			player* curr = h.extractMax();
			temp.push_back(curr);
			cout << curr->name << ", " << curr->position
			<< ", " << curr->college << ", " << curr->ppg << " ppg, "
			<< curr->rpg << " rpg, " << curr->apg << " astpg" << endl;
		}

		cout << "---------------------------------------" << endl;

		for (int i = 0; i < temp.size(); i++){
			h.insertPlayer(temp[i]);
		}

		temp.clear();


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

	MaxHeap best(100);

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

		best.createPlayer(strComponents, dblComponents);

		strCnt = 0;
		dblCnt = 0;
		components.clear();
	}
	
	int choice = displayDraftMenu(best);



	return 0;
}