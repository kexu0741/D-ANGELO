#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream in;
	in.open("stats.csv");

	string line;

	//file format: Name, position, year, college, PPG, FG%, 3PT%, FT%, APG, RPG, SPG, BPG, TOVPG, AST/TO ratio
	//STL/TO (steals to turnovers), BLK/TO(Blocks to turnovers), scoring efficiency
	//Shooting efficiency, personal fouls per game, Games played

	while (getline(in, line)){
		cout << line << endl; //should print every athlete with their respective stats, seperated by comma delim
	}

	return 0;
}
