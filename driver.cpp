#include <iostream>
#include <fstream>
#include <sstream>
#include "MaxHeap.hpp"
#include "BST.hpp"
#include "HashTable.hpp"
#include <vector>

using namespace std;

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
	cout << "The user can then search for their desired reccomended player" << endl;
	cout << "and select them with their pick." << endl;
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

	while (!start){ //displays starting options
		cout << "1. Instructions" << endl;
		cout << "2. Enter D'ANGELO" << endl;

		getline(cin, startInput);

		if (startInput == "1" || startInput == "2"){ //user input handling
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

int displayDraftMenu(MaxHeap &h, PlayerTree &t, HashTable ht){
	vector<player*> temp; //temp vector for printing

	for (int i = 0; i < 15; i++)
		cout << endl;

	cout << "---------------------------------------" << endl;
	cout << "Top 10 Available Prospects: " << endl;

	for (int i = 0; i < 10; i++){
		cout << i+1 << ". ";
		
		player* curr = h.extractMax();
		temp.push_back(curr); //makes sure nodes are kept

		cout << curr->name << ", " << curr->position
		<< ", " << curr->college << ", " << curr->ppg << " ppg, "
		<< curr->rpg << " rpg, " << curr->apg << " astpg" << endl;
	}

	cout << "---------------------------------------" << endl;

	for (int i = 0; i < temp.size(); i++){
		h.insertPlayer(temp[i]); //nodes put back into the heap
	}

	temp.clear();

	for (int i = 0; i < 5; i++)
		cout << endl;

	//add while loop for input
	bool openMenu = true;
	int userInput;
	int pickCount = 0;

	while (openMenu){
		MaxHeap recs(50); //heap for reccomendations

		if (pickCount == 60){ //ends the draft after 60 picks
			break;
		}

 		bool pickOver = false;

 		while (!pickOver){

 			cout << endl;
 			cout << "----------------PICK #" << pickCount + 1 << "--------------------"<< endl;
			cout << "--------------------------------------" << endl;
			cout << "1. Auto Draft Best Available" << endl;
			cout << "2. Enter Team Needs" << endl;
			cout << "3. Search for Desired Player" << endl;
			cout << "4. Quit draft" << endl;
			cout << "--------------------------------------" << endl;

    		cin >> userInput;

			switch(userInput){
				case 1: //auto drafts best available player
				{
					//deletes player from all three data structures
					player* curr = h.extractMax();
					string name = curr->name;
					t.deletePlayer(curr->name);

					cout << curr->name << ", " << curr->position
					<< ", " << curr->college << ", " << curr->ppg << " ppg, "
					<< curr->rpg << " rpg, " << curr->apg << " astpg "
					<< "---- drafted " << pickCount + 1 << " overall." << endl;

					ht.deletePlayer(name);

					pickOver = true;
				}
				break;

				case 2:
				{
					int choice;
					
					//bools to ensure duplicate team needs are not entered
					bool recsEntered = false;
					bool scoringMarked = false;
					bool playMakingMarked = false;
					bool perimDMarked = false;
					bool inDMarked = false;
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
									vector<player*> scorers = ht.getNthBucket(1); //scorers bucket is passed
									for (int i = 0; i < scorers.size(); i++){
									player* current = scorers[i];

									//copies node to ensure completely new pointer is made (in case heap is modified)
									player* newPlayer = new player(current->name, current->position, current->grade, current->college,
									current->ppg, current->fgp, current->threeptp, current->ftp, current->apg, current->rpg, current->spg, current->bpg,
									current->tovpg, current->astto, current->stlto, current->blkto, current->sceff, current->sheff, current->pfpg, current->gamesPlayed);
									newPlayer->aggregateScore = current->aggregateScore;

									recs.insertPlayer(newPlayer); //inserts player into reccomendation heap

									}
									scoringMarked = true;
									recsEntered = true;

								}
								else{
									cout << "Scoring already added. " << endl;
								}
							break;

							case 2:
								if (!playMakingMarked){
									vector<player*> playmakers = ht.getNthBucket(2); //playmakers bucket is passed
									for (int i = 0; i < playmakers.size(); i++){
										player* current = playmakers[i];

										player* newPlayer = new player(current->name, current->position, current->grade, current->college,
										current->ppg, current->fgp, current->threeptp, current->ftp, current->apg, current->rpg, current->spg, current->bpg,
										current->tovpg, current->astto, current->stlto, current->blkto, current->sceff, current->sheff, current->pfpg, current->gamesPlayed);

										newPlayer->aggregateScore = current->aggregateScore;
										recs.insertPlayer(newPlayer);
									}
									cout << "Playmaking added." << endl;
									playMakingMarked = true;
									recsEntered = true;

								}
								else{
									cout << "Playmaking already added" << endl;
								}
							break;

							case 3:
								if (!perimDMarked){
									vector<player*> pDefenders = ht.getNthBucket(3); //perimiter defenders bucket is passed
									for (int i = 0; i < pDefenders.size(); i++){
										player* current = pDefenders[i];

										player* newPlayer = new player(current->name, current->position, current->grade, current->college,
										current->ppg, current->fgp, current->threeptp, current->ftp, current->apg, current->rpg, current->spg, current->bpg,
										current->tovpg, current->astto, current->stlto, current->blkto, current->sceff, current->sheff, current->pfpg, current->gamesPlayed);

										newPlayer->aggregateScore = current->aggregateScore;

										recs.insertPlayer(newPlayer);
									}
									cout << "Perimeter Defense added." << endl;
									perimDMarked = true;
									recsEntered = true;
								}
								else{
									cout << "Perimeter Defense already added." << endl;
								}
							break;

							case 4:
								if (!inDMarked){
									vector<player*> inDefenders = ht.getNthBucket(4); //interior defenders bucket is passed
									for (int i = 0; i < inDefenders.size(); i++){
										player* current = inDefenders[i];

										player* newPlayer = new player(current->name, current->position, current->grade, current->college,
										current->ppg, current->fgp, current->threeptp, current->ftp, current->apg, current->rpg, current->spg, current->bpg,
										current->tovpg, current->astto, current->stlto, current->blkto, current->sceff, current->sheff, current->pfpg, current->gamesPlayed);

										newPlayer->aggregateScore = current->aggregateScore;

										recs.insertPlayer(newPlayer);
									}
									cout << "Interior Defense added." << endl;
									inDMarked = true;
									recsEntered = true;
								}
								else{
									cout << "Interior Defense already added." << endl;
								}
							break;

							case 5:
								if (!shootingMarked){
									vector<player*> shooters = ht.getNthBucket(5); //shooters bucket is passed
									for (int i = 0; i < shooters.size(); i++){
										player* current = shooters[i];

										player* newPlayer = new player(current->name, current->position, current->grade, current->college,
										current->ppg, current->fgp, current->threeptp, current->ftp, current->apg, current->rpg, current->spg, current->bpg,
										current->tovpg, current->astto, current->stlto, current->blkto, current->sceff, current->sheff, current->pfpg, current->gamesPlayed);

										newPlayer->aggregateScore = current->aggregateScore;

										recs.insertPlayer(newPlayer);
									}
									cout << "Shooting added." << endl;
									shootingMarked = true;
									recsEntered = true;
								}
								else{
									cout << "Shooting already added." << endl;
								}
							break;

							case 6:
								menu = true;
							break;
						}
					}
					//printing reccomended prospects
					if (recsEntered){
							cout << endl;
							cout << "Top reccomendations: " << endl;

							vector<player*> temp; //vector for printing

							for (int i = 0; i < 5; i++){
								player* curr = recs.extractMax();
								temp.push_back(curr);

								if (curr != NULL){
									cout << curr->name << ", " << curr->position
									<< ", " << curr->college << ", " << curr->ppg << " ppg, "
									<< curr->rpg << " rpg, " << curr->apg << " astpg" << endl;
								}
								else if (curr == NULL){
									break;
								}
							}

							for (int i = 0; i < temp.size(); i++){
								recs.insertPlayer(temp[i]); //reinserts popped nodes back into heap
							}
					}

				}
				break;

				case 3: //searching, calls BST functions
			    {
			        string n;
			        cout << "Enter player name: " << endl;

			        cin.ignore();
			        getline(cin, n);
 
			        player* curr = t.findPlayer(n);

			        if(curr!=NULL)
			        {
			          string name = curr->name;
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
			              case 2: //deletes player from all three data structures
			              {
			                cout << curr->name << ", " << curr->position
			        				<< ", " << curr->college << ", " << curr->ppg << " ppg, "
			        				<< curr->rpg << " rpg, " << curr->apg << " astpg "
			        				<< "---- drafted " << pickCount + 1<< " overall." << endl;
									h.draftPlayer(curr->name);
			                		t.deletePlayer(n);
			                		ht.deletePlayer(name);
			                		menu = true;
			                		pickOver = true;
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

					break;
			      }

				case 4:
				//exits from menu
				pickOver = true;
				openMenu = false;
				break;
			}
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

	cout << "Draft Finished." << endl;

}

//FOR ADDING TO HEAP: CALL CREATEPLAYER

//file format: PPG, FG%, 3PT%, FT%, APG, RPG, SPG, BPG, TOVPG, AST/TO ratio
//STL/TO (steals to turnovers), BLK/TO(Blocks to turnovers), scoring efficiency
//Shooting efficiency, personal fouls per game, Games played

int main(){
	displayStartingMenu();

	ifstream in;
	in.open("stats.csv"); //reading in file

	string line;
	string token;
	char delim = ',';

	MaxHeap best(100); //best available heap- main heap

	HashTable playerMap(6); //team need hash table

	PlayerTree(); //main BST
	PlayerTree tree;

	vector<string> components; //temp vector for reading in strings from file

	string strComponents[5]; //array for storing string components read from file
	int strCnt = 0;
	
	double dblComponents[15]; //array for storing double components read from file
	int dblCnt = 0;

	while (getline(in, line)){ //reading in every line
		stringstream ss(line);
		while (getline(ss, token, delim)){ //pushes every word that's not a comma
			components.push_back(token);
		}
		for (int i = 0; i < components.size(); i++){
			if (i == 0 || i == 1 || i == 2 || i == 3 || i == 19){ //parses string components in file into string array
				strComponents[strCnt] = components[i];
				strCnt++;
			}
			else{ //parses double components in file into double array
				if (components[i] == "N/A"){ //handles if "N/A is read in"
					dblComponents[dblCnt] = 0;
				}
				else{
					dblComponents[dblCnt] = stod(components[i]);
				}
				dblCnt++;
			}
		}

		best.createPlayer(strComponents, dblComponents); //creates heap nodes from components read in
	    tree.addPlayer(strComponents, dblComponents); //creates tree nodes from components read in

	    strCnt = 0;
		dblCnt = 0;
		components.clear();
	}

	playerMap.getAverages(best); //initializes averages for heap

	vector<player*> builder; //temp vector for building heap

	player* curr = best.extractMax(); //pops player from top of heap

	while (curr != NULL){ //pops every player from heap
		builder.push_back(curr);

		//copies node so that separate pointers are created
		player* newPlayer = new player(curr->name, curr->position, curr->grade, curr->college,
		curr->ppg, curr->fgp, curr->threeptp, curr->ftp, curr->apg, curr->rpg, curr->spg, curr->bpg,
		curr->tovpg, curr->astto, curr->stlto, curr->blkto, curr->sceff, curr->sheff, curr->pfpg, curr->gamesPlayed);

		newPlayer->aggregateScore = curr->aggregateScore;

		playerMap.insertItem(newPlayer); //inserts player into heap
		curr = best.extractMax(); //pops player from top of heap
	}

	for (int i = 0; i < builder.size(); i++){
		best.insertPlayer(builder[i]); //reinserts nodes into heap
	}

	int choice = displayDraftMenu(best, tree, playerMap); //starts the draft
	
	return 0;
}
