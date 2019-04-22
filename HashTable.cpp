#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "HashTable.hpp"
#include "playerStruct.h"

using namespace std;

player* HashTable::createNode(string s[], double d[]) //instantiating a node manually
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

    return add;
}
//
HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    hashTable = new player*[tableSize];
    for(int i=0;i<bsize;i++)
        hashTable[i] = nullptr;
}

HashTable::~HashTable()
{
  for(int i = 0; i<tableSize; i++)
  {
      player *temp = hashTable[i];
      while(temp!=NULL)
      {
          player *del = temp;
          temp = temp->next;
          delete del;
      }
  }
  delete hashTable;
}
// //function to calculate hash function
   //players hashed by player type- or stat they're above average in
unsigned int HashTable::hashFunction(player* p)
{
	double PGR = p->apg * p->astto;
    if (p->position != "PG" && p->ppg >= avgPPG){ //scorers are hashed into index 1
    	return 1;
    }
    else if (PGR >= avgPGR){ //playmakers are hashed into index 2
    	return 2;
    }
    else if (p->spg >= avgSPG){ //perimeter defenders are hashed into index 3
    	return 3;
    }
    else if (p->bpg >= avgBPG){ //interior defenders are hashed into index 4
    	return 4;
    } 
    else if (p->threeptp >= avg3pt){ //shooters are hashed into index 5
    	return 5;
    }
    else{ //rest are hashed into index 0
    	return 0;
    }
}

player* HashTable::searchItem(player* p)
{
    //Compute the index by using the hash function
    int index = hashFunction(p);
    player *temp = hashTable[index];
    while(temp!=NULL)
    {
      if(temp==p)
      {
        return temp;
      }
      temp = temp->next;
    }
    return NULL;
}

bool HashTable::insertItem(player* n) //inserts player into hashtable
{
    if(!searchItem(n))
    {
        int index = hashFunction(n);
        if(hashTable[index]==NULL)
        {
          hashTable[index] = n;

        }
        else
        {
          n->next = hashTable[index];
          hashTable[index] = n;
        }
     }
    else{
        cout<<"duplicate entry." <<endl;
        return false;
    }

}

void HashTable::printTable() //utility function, iterates through each bucket and prints each node's name
{
    for (int i = 0; i < tableSize; i++) {
        player *temp = hashTable[i];
        cout << i <<"|| ";
        while(temp)
        {
          cout << temp->name << "--->";
          temp = temp->next;
        }
        cout << endl;
        //TODO
    }
}

void HashTable::deletePlayer(string n){ //searches entire hash table by name, since hash function is by player node iteself
	for (int i = 0; i < tableSize; i++){
		player* temp = hashTable[i];
		player* prev = temp;

		if (temp->name == n){
			hashTable[i] = temp->next;
			delete temp;
			return;
		}

		while (temp != NULL){
			if (temp->name == n){
			   	prev->next = temp->next; 
			    delete temp;  // Free memory 
				return;
			}
			prev = temp;
			temp = temp->next;
		}
	}
}


void HashTable::getAverages(MaxHeap &h){ //gets averages from heap
	avgPPG = h.calcAvgPPG();
	avgPGR = h.calcAvgPGR();
	avgSPG = h.calcAvgSPG();
	avgBPG = h.calcAvgBPG();
	avg3pt = h.calcAvg3ptp();
}


vector<player*> HashTable::getNthBucket(int bucket){ //returns entire bucket, or all players with specialty N
	vector<player*> ret;
	player* temp = hashTable[bucket];

	while (temp != NULL){
		ret.push_back(temp);
		temp = temp->next;
	}

	return ret;
}
