#pragma once

#include <string>


// MovieNode: node struct that will be stored in the MovieTree BST

struct PlayerNode
{
  std::string name; //player name
	// std::string position; //position
	// int grade; //grade; 1-4 scale
	// std::string college; //player's college
	// double ppg; //points per game
	// double fgp; //field goal percentage
	// double threeptp; //3pt percentage
	// double ftp; //free throw percentage
	// double apg; //assists per game
	// double rpg; //rebounds per game
	// double spg; //steals per game
	// double bpg; //blocks per game
	// double tovpg; //turnovers per game
	// double astto; //assist to turnover ratio
	// double stlto; //steal to turnover ratio
	// double blkto; //block to turnover ratio
	// double sceff; //scoring efficiency
	// double sheff; //shooting efficiency
	// double pfpg; //personal fouls per game
	// int gamesPlayed; //games played
  //
	// double aggregateScore; //formula coming soon

	PlayerNode* left = NULL;
	PlayerNode* right = NULL;

  // default constructor
  PlayerNode(){}
  // Parametrized constructor
  PlayerNode(std::string n)
  {
    name = n;
  }
};

class PlayerTree
{
public:
  // Check writeup for detailed function descriptions
  PlayerTree();
  ~PlayerTree();
  void printMovieInventory();
  void addMovieNode(std::string name);
  void findMovie(std::string title);
  void deleteNode(std::string title);
private:
  //MovieNode *search(std::string title);
  PlayerNode* deleteNodeHelper(PlayerNode *currNode, std::string value);
  // Pointer to the root node
  PlayerNode *root;
};
