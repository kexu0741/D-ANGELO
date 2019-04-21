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
  void addPlayer(std::string name, string p, int g, string c, double p1, double f, double t, double f2, double a, double r, double s, double b ,double t2, double a2, double s2, double b2, double s3, double s4,double p2,  int g2, double a3);
  void printPlayerStat(std::string name);
  void deletePlayer(std::string name);
  void printRosterTree( int space);
private:
  player* deletePlayerHelper(player *currNode, std::string value);
  void destroyRoster(player *currNode);
  player *root;
};
