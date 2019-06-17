#pragma once
#include "playerStruct.h"
#include <string>
using namespace std;


class PlayerTree
{
public:
  PlayerTree();
  ~PlayerTree();
  void printRoster();
  void addPlayer(string s[], double d[]);
  void printPlayerStatHelper(std::string name, player* node);
  void printPlayerStat(std::string name);
  void deletePlayer(std::string name);
  void printRosterTree(int space);
  player* findPlayer(string name);
private:
  player* deletePlayerHelper(player *currNode, std::string value);
  void destroyRoster(player *currNode);
  player *root;
};
