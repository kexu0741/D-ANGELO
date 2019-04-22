#include <iostream>
#include <fstream>
#include <sstream>
#include "MaxHeap.hpp"
#include "BST.hpp"
#include "HashTable.hpp"
// #include "playerStruct.h"
// #include "MaxHeap.hpp"
//#include "MaxHeap.cpp"
#include <vector>

//TODO: IMPLEMENT TEAMS, IMPLEMENT MENU, MERGE AVNISH'S CODE

using namespace std;

// void buildTable(vector<player*> &builder, HashTable &ht){

// 	for (int i = 0; i < builder.size(); i++){
// 		ht.insertItem(builder[i]);
// 	}

// 	ht.printTable();

// }

void printInstructions(){
	cout << "-----------------------------------------------------" << endl;
	cout << "D'ANGELO is an analytical tool for NBA scouts, general " << endl;
	cout << "managers, and draft enthusiasts." << endl;
	cout << endl;
	cout << "The user will go pick by pick, controlling all teams," << endl;
	cout << "selecting players. The user will be prompted initially" << endl;
	cout << "with three options: "<< endl;
	cout << "1) auto pick the best available player" << endl;
	cout << "2) select a player based on team needs." << endl;
	cout << "3) search for player by name to draft or view stats" << endl;
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

int displayDraftMenu(MaxHeap &h, PlayerTree &t, HashTable &ht){ //ADD BST PARAM
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
	int userInput;
	int pickCount = 0;

	while (openMenu){
		if (pickCount == 60){
			break;
		}

		cout << "--------------------------------------" << endl;
		cout << "1. Auto Draft Best Available" << endl;
		cout << "2. Enter Team Needs" << endl;
		cout << "3. Search for Player" << endl;
		cout << "4. Quit draft" << endl;
		cout << "--------------------------------------" << endl;

		//getline(cin, userInput);
    	cin >> userInput;
		player* curr;

		switch(userInput){
			case 1:
				//delete from heap and the tree
				curr = h.extractMax();
				t.deletePlayer(curr->name);
				cout << curr->name << ", " << curr->position
				<< ", " << curr->college << ", " << curr->ppg << " ppg, "
				<< curr->rpg << " rpg, " << curr->apg << " astpg "
				<< "---- drafted " << pickCount + 1 << " overall." << endl;
				ht.deletePlayer(curr);

			break;

			case 2:
			{	
				int choice;

				MaxHeap recs(50);

				bool scoringMarked = false;
				bool playMakingMarked = false;
				bool perimDMarked = false;
				bool inD = false;
				bool shootingMarked = false;

				bool menu = false;
				while (!menu){
					cout << "Enter ALL desired team needs before hitting finish." << endl;
					cout << "1. Scoring" << endl;
					cout << "2. Playmaking" << endl;
					cout << "3. Perimeter Defense" << endl;
					cout << "4. Interior Defense" << endl;
					cout << "5. Shooting" << endl;
					cout << "6. Finished" << endl;

					cin >> choice;
					switch(choice){
						case 1:
							if (!scoringMarked){
								cout << "Scoring added." << endl;
								ht.printTable();
								vector<player*> scorers = ht.getNthBucket(0);
								for (int i = 0; i < scorers.size(); i++){
									cout << scorers[i]->name << endl;
								}
								scoringMarked = true;
							}
							else{
								cout << "Scoring already added. " << endl;
							}

						break;

						case 2:
							cout << "Playmaking added." << endl;

						break;

						case 3:
							cout << "Perimeter Defense added." << endl;

						break;

						case 4:
							cout << "Interior Defense added." << endl;
						break;

						case 5:
							cout << "Shooting added." << endl;
						break;

						case 6: 
							menu = true;
						break;
					}
				}
				//print recommended prospects
			}
			break;

			case 3:
		    {
		        string n = "";
		        cout << "Enter player name: " << endl;
		        cin.ignore();
		        getline(cin, n);
		        curr = t.findPlayer(n);
		        if(curr!=NULL)
		        {
		          int choice;
		          bool menu = false;
		          while(menu==false)
		          {
		            cout << "1. View Stats" << endl << "2. Draft Player" << endl <<"3. Discard" << endl;
		            cin >> choice;
		            switch(choice)
		            {
		              case 1:
		              {
		                t.printPlayerStat(n);
		                break;
		              }
		              case 2:
		              {
		                cout << curr->name << ", " << curr->position
		        				<< ", " << curr->college << ", " << curr->ppg << " ppg, "
		        				<< curr->rpg << " rpg, " << curr->apg << " astpg "
		        				<< "---- drafted " << pickCount << " overall." << endl;
								h.draftPlayer(curr->name);
		                		t.deletePlayer(n);
		                		ht.deletePlayer(curr);
		                		menu = true;
		                break;
		              }
		              case 3:
		              {
		                menu = true;
		              }
		            }
		          }
		        }
		        else
		        {
		          cout <<  n << " Not Found" << endl;
		        }
						//call for BST
				break;
		      }

			case 4:
				//exits from menu
			openMenu = false;
			break;

		}

		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "Top Available Prospects: " << endl;

		for (int i = 0; i < 10; i++){
			player* curr = h.extractMax();
			if (curr != NULL){
				cout << i+1 << ". ";
				temp.push_back(curr);
				cout << curr->name << ", " << curr->position
				<< ", " << curr->college << ", " << curr->ppg << " ppg, "
				<< curr->rpg << " rpg, " << curr->apg << " astpg" << endl;
			}
			else if (curr == NULL){
				break;
			}
		}

		cout << "---------------------------------------" << endl;

		for (int i = 0; i < temp.size(); i++){
			h.insertPlayer(temp[i]);
		}

		temp.clear();
		pickCount++;

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

	HashTable playerMap(6);

	PlayerTree();
	PlayerTree tree;

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
	    tree.addPlayer(strComponents, dblComponents);

	    strCnt = 0;
		dblCnt = 0;
		components.clear();
	}

	playerMap.getAverages(best);

	vector<player*> builder;

	player* curr = best.extractMax();
	while (curr != NULL){
		builder.push_back(curr);
		player* newPlayer = new player(curr->name, curr->position, curr->grade, curr->college, 
		curr->ppg, curr->fgp, curr->threeptp, curr->ftp, curr->apg, curr->rpg, curr->spg, curr->bpg,
		curr->tovpg, curr->astto, curr->stlto, curr->blkto, curr->sceff, curr->sheff, curr->pfpg, curr->gamesPlayed);


		playerMap.insertItem(newPlayer);
		curr = best.extractMax();
	}

	for (int i = 0; i < builder.size(); i++){
		best.insertPlayer(builder[i]);
	}

	//playerMap.printTable();
	int choice = displayDraftMenu(best, tree, playerMap);

	return 0;
}
