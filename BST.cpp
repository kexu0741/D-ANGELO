#include <iostream>
#include <string>
#include "BST.hpp"
#define COUNT 10
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

PlayerTree::PlayerTree()
{
  root = nullptr;
}
PlayerTree::~PlayerTree()
{
  destroyRoster(root);
}
void PlayerTree::destroyRoster(player *currNode)
{
  if(currNode!=NULL)
  {
      destroyRoster(currNode->left);
      destroyRoster(currNode->right);

      delete currNode;
      currNode = NULL;
  }
}
void print(player *root)
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
void PlayerTree::printRoster()
{
    print(root);
}
player *spot(player *temp, string name)
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
void PlayerTree::addPlayer(string name,string p, int g, string c, double p1, double f, double t, double f2, double a, double r, double s, double b ,double t2, double a2, double s2, double b2, double s3, double s4, double p2,  int g2, double a3)
{
  player *add = new player(name, p , g, c, p1, f, t, f2, a, r, s, b, t2, a2, s2, b2, s3, s4, p2, g2, a3);
  if(root==NULL)
  {
    root = add;
    return;
  }

  player *temp = root;
  player *z = spot(temp, name);

  if(name > z->name)
  {
      z->right = add;
  }
  else
  {
      z->left = add;
  }

}

void PlayerTree::printPlayerStat(string name)
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
      cout << "Grade: " << root->grade << endl;
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
      cout << "Aggregate Impact Score: " << root->aggregateScore << endl;

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
player* getMinValueNode(player* currNode){

    if(currNode->left == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}
player* PlayerTree::deletePlayerHelper(player *currNode, string value)
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
void PlayerTree::deletePlayer(string v)
{
  deletePlayerHelper(root, v);
}
void printRosterTreeHelper(player *currNode, int space)
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

void PlayerTree::printRosterTree( int space)
{
  printRosterTreeHelper(root, space);
}

string getGradeNum(string grade)
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


int main()
{
  PlayerTree();
  PlayerTree p;
  ifstream file;
  file.open("stats.csv");
  if(file.is_open())
  {
    string line = "";
    int l = 0;
    while(getline(file,line))
    {
      string data[21];
      int count = 0;
      int last = 0;
        for(int i=0; i<line.length(); i++)
        {
          if(line[i]==','|| i==line.length()-1)
          {
            data[count] = line.substr(last,i-last);
            if(i==line.length()-1)
            {
              data[count]+=line[i];
            }
            count++;
            last = i+1;
          }
        }
        data[2] = getGradeNum(data[2]);
        if(data[16]=="N/A")
        {
          data[16] = "-1";
        }
        if(data[17]=="N/A")
        {
          data[17] = "-1";
        }
        p.addPlayer(data[0], data[1], stoi(data[2]),data[3],stod(data[4]),stod(data[5]),stod(data[6]),stod(data[7]),stod(data[8]),stod(data[9]),stod(data[10]),stod(data[11]),stod(data[12]),stod(data[13]),stod(data[14]),stod(data[15]),stod(data[16]),stod(data[17]), stod(data[18]),stoi(data[19]),stod(data[19]));

      l++;
    }
  }

  cout << "Roster of Players: " << endl;
  p.printRoster();
  cout << "Deleting Admiral Schofield----------------------------------" << endl;
  p.deletePlayer("Admiral Schofield");
  p.printRoster();
  cout << "-----------------------------------------------------------" << endl;
  p.printPlayerStat("Zion Williamson");
  cout << "-----------------------------------------------------------" << endl;
  p.printRosterTree(5);
}
