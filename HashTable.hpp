#ifndef HASH_HPP
#define HASH_HPP
#include "playerStruct.h"
#include "MaxHeap.hpp"
#include <vector>
using namespace std;


class HashTable
{
    int tableSize;
    double avgPPG;
    double avgPGR;
    double avgSPG;
    double avgBPG;
    double avg3pt;
    player **hashTable;
  	player* createNode(string s[], double d[]);

    public:

    HashTable(int bsize);
    ~HashTable();
    bool insertItem(player* n);
    unsigned int hashFunction(player* p);
    void printTable();
    player* searchItem(player* p);
    void deletePlayer(player* p);
    void deletePlayer(string n);
    void getAverages(MaxHeap &h);
    void test(player* a);
    vector<player*> getNthBucket(int bucket); //returns entire bucket
};

#endif
