#include <iostream>
#include <string>
#include "BST.hpp"
#define COUNT 10
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

PlayerTree::PlayerTree() //constructor for the root of the tree
{
  root = nullptr;
}
PlayerTree::~PlayerTree() //destructor for the tree
{
  destroyRoster(root);
}
void PlayerTree::destroyRoster(player *currNode) //helper for the tree destructor
{
  if(currNode!=NULL)
  {
      destroyRoster(currNode->left);
      destroyRoster(currNode->right);

      delete currNode;
      currNode = NULL;
  }
}
void print(player *root) //helper function for the print function
{
    if(root==NULL)
    {
        return;
    }
    if (root->left != NULL)
	{
		print(root->left);
	}
		cout << "Player: " << root->name << endl;

	if (root->right != NULL)
	{
		print(root->right);
	}
}
void PlayerTree::printRoster() //prints all players, used for testing
{
    print(root);
}
player *spot(player *temp, string name) //returns the spot of where in the tree to add the player
{

    if(name > temp->name)
    {
        if(temp->right!=NULL)
        {
            temp=spot(temp->right, name);
        }

            return temp;

    }
    else if(name < temp->name)
    {
        if(temp->left!=NULL)
        {
            temp=spot(temp->left, name);
        }

            return temp;

    }
}
void PlayerTree::addPlayer(string s[], double d[]) //adds a player to the tree of players
{
  int g;
  if (s[2] == "Freshman" || s[2] == "International" || s[2] == "N/A"){
		g = 1;
	}
	else if(s[2] == "Sophomore"){
		g = 2;
	}
	else if(s[3] == "Junior"){
		g = 3;
	}
	else if(s[4] == "Senior"){
		g = 4;
	}
  player *add = new player(s[0], s[1] , g, s[3], d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], d[8], d[9], d[10], d[11], d[12], d[13], d[14], stoi(s[4]));
  if(root==NULL)
  {
    root = add;
    return;
  }

  player *temp = root;
  player *z = spot(temp, s[0]); //helper function called to find where to add the new node

  if(s[0] > z->name)
  {
      z->right = add;
  }
  else
  {
      z->left = add;
  }

}

void PlayerTree::printPlayerStat(string name) //prints the player stats for user viewing
{
  if(root==NULL)
  {
    cout << "Player not found." << endl;
      return;
  }
  if(root->name == name)
  {
      cout << "Player Stats:" << endl;
      cout << "==================" << endl;
      cout << "Name:" << root->name << endl;
      cout << "Position: " << root->position << endl;
      cout << "College: " << root->college << endl;
      cout << "Points Per Game: " << root->ppg << endl;
      cout << "Field Goal Percentage: " << root->fgp << endl;
      cout << "3-pointer percentage: " << root->threeptp << endl;
      cout << "Free Throw Percentage: " << root->ftp << endl;
      cout << "Assists Per Game: " << root->apg << endl;
      cout << "Rebounds Per Game: " << root->rpg << endl;
      cout << "Steals Per Game: " << root->spg << endl;
      cout << "Blocks Per Game: " << root->bpg << endl;
      cout << "Turnovers Per Game: " << root->tovpg << endl;
      cout << "Assist to Turnover Ratio: " << root->astto << endl;
      cout << "Steal to Turnover Ratio: " << root->stlto << endl;
      cout << "Block to Turnover Ratio: " << root->blkto << endl;
      cout << "Scoring Efficency: " << root->sceff << endl;
      cout << "Shooting Efficency: " << root->sheff << endl;
      cout << "Personal Fouls Per Game: " << root->pfpg << endl;
      cout << "Total Games Played: " << root->gamesPlayed << endl;
      cout << "==================" << endl;
  }
  else if(root->name.compare(name) > 0)
  {
    root = root->left;
    printPlayerStat(name);
  }
  else
  {
    root = root->right;
    printPlayerStat(name);
  }
}
player* getMinValueNode(player* currNode) //minds the player with the smallest aggregate score
{
    if(currNode->left == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}

player* findPlayerHelper(player* currNode, string name) //helper function to search for a player
{
  if(currNode == NULL)
      return NULL;

  if(currNode->name == name)
      return currNode;

  if(currNode->name > name)
      return findPlayerHelper(currNode->left, name);

  return findPlayerHelper(currNode->right, name);
}

player* PlayerTree::findPlayer(string name) //finds a player by name for the user to draft, discard, or view stats
{
  player* temp = root;
  player *s = findPlayerHelper(temp, name);
  return s;
}
player* PlayerTree::deletePlayerHelper(player *currNode, string value) //helps take out a player from the tree
{

    if(currNode == NULL)
    {
      return NULL;
    }
    else if(value < currNode->name)
    {
      currNode->left = deletePlayerHelper(currNode->left, value);
    }
    else if(value > currNode->name)
    {
      currNode->right = deletePlayerHelper(currNode->right, value);
    }
    else
    {
      if(currNode->left == NULL && currNode->right == NULL)
      {
        delete currNode;
        currNode = NULL;
      }
      else if(currNode->left == NULL)
      {
        player *delNode = currNode;
        currNode = currNode->right;
        delete delNode;
      }
      else if(currNode->right == NULL)
      {
         player *delNode = currNode;
        currNode = currNode->left;
        delete delNode;
      }
      else
      {
        string min = (getMinValueNode(currNode->right))->name;
        currNode->name = min;
        currNode->right = deletePlayerHelper(currNode->right, min);
      }
     }
   return currNode;
}
void PlayerTree::deletePlayer(string v) //deletes player from the tree if they have been drafted
{
  deletePlayerHelper(root, v);
}
void printRosterTreeHelper(player *currNode, int space) //helper to print the entire roster of prospects
{
    if (currNode == NULL)
        return;

    space += COUNT;

    printRosterTreeHelper(currNode->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    cout << currNode->name << endl;
    printRosterTreeHelper(currNode->left, space);
}

void PlayerTree::printRosterTree( int space) //prints all the college prospects, used for testing
{
  printRosterTreeHelper(root, space);
}

string getGradeNum(string grade) //converts string to a number representing their grade in college
{
  if(grade=="Freshman")
  {
    return "9";
  }
  else if(grade=="Sophomore")
  {
    return "10";
  }
  else if(grade=="Junior")
  {
    return "11";
  }
  else if(grade=="Senior")
  {
    return "12";
  }
  else if(grade=="International")
  {
    return "0";
  }
  else
  {
    return "-1";
  }
}
