#ifndef PLAYERSTRUCT_H
#define PLAYERSTRUCT_H
using namespace std;
#include <string>

struct player{
	std::string name; //player name
	std::string position; //position
	int grade; //grade; 1-4 scale
	std::string college; //player's college
	double ppg; //points per game
	double fgp; //field goal percentage
	double threeptp; //3pt percentage
	double ftp; //free throw percentage
	double apg; //assists per game
	double rpg; //rebounds per game
	double spg; //steals per game
	double bpg; //blocks per game
	double tovpg; //turnovers per game
	double astto; //assist to turnover ratio
	double stlto; //steal to turnover ratio
	double blkto; //block to turnover ratio
	double sceff; //scoring efficiency
	double sheff; //shooting efficiency
	double pfpg; //personal fouls per game
	int gamesPlayed; //games played

	double aggregateScore; //Modified Hollinger PER calculation
	int aboveAverageCount;

	player* left = NULL;
	player* right = NULL;
	player* next = NULL;

		player(){}
	  player(string n, string p, int g, string c, double p1, double f, double t, double f2, double a, double r, double s, double b ,double t2, double a2, double s2, double b2, double s3, double s4,double p2,  int g2)
	  {
	    name = n;
	    position = p;
	    grade = g;
	    college = c;
	    ppg = p1;
	    fgp = f;
	    threeptp = t;
	    ftp = f2;
	    apg = a;
	    rpg = r;
	    spg = s;
	    bpg = b;
	    tovpg = t2;
	    astto = a2;
	    stlto = s2;
	    blkto = b2;
	    sceff = s3;
	    sheff = s4;
	    pfpg = p2;
	    gamesPlayed = g2;
	    //aggregateScore = a3;
	  }
};

#endif
