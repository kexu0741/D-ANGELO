#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "HashTable.hpp"
#include "playerStruct.h"

using namespace std;

player* HashTable::createNode(string s[], double d[])
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
    //player* nw = new player(name, p , g, c, p1, f, t, f2, a, r, s, b, t2, a2, s2, b2, s3, s4, p2, g2);
    // nw->data = data;
    // nw->next = NULL;
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
unsigned int HashTable::hashFunction(player* p)
{
	double PGR = p->apg * p->astto;
    if (p->position != "PG" && p->ppg >= avgPPG){
    	return 1;
    }
    else if (PGR >= avgPGR){
    	return 2;
    }
    else if (p->spg >= avgSPG){
    	return 3;
    }
    else if (p->bpg >= avgBPG){
    	return 4;
    } 
    else if (p->threeptp >= avg3pt){
    	return 5;
    }
    else{
    	return 0;
    }
}
//
// // TODO Complete this function
// //function to search
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

void HashTable::deletePlayer(player *p){
	int index = hashFunction(p);
	player* temp = hashTable[index];
	player* prev;

	if (hashTable[index]->name == p->name){
		hashTable[index] = temp->next;
		delete temp;
		return;
	}

	while (temp != NULL && temp->name != p->name) 
	{ 
	    prev = temp; 
	    temp = temp->next; 
	} 

	if (temp == NULL) return;

    prev->next = temp->next; 
    delete temp;  // Free memory 
	return;
}

//string name,string p, int g, string c, double p1, double f, double t, double f2, double a, double r, double s, double b ,double t2, double a2, double s2, double b2, double s3, double s4, double p2,  int g2, double a3

bool HashTable::insertItem(player* n)
{
    if(!searchItem(n))
    {
    	cout << "called for: " << n->name << endl;
        // TODO :
        // Use the hash function on the data to get the index/slot,
        // create a new node with the data and insert it in this slot's list

        int index = hashFunction(n);
        cout << "index for : " << n->name << ": " << index << endl;
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
//
// //TODO Complete this function
// // function to display hash table
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        player *temp = hashTable[i];
        cout << i <<"|| ";
        while(temp)
        {
          cout << temp->name << ", " << temp->ppg << "--->";
          temp = temp->next;
        }
        cout << endl;
        //TODO
    }
}


void HashTable::getAverages(MaxHeap &h){
	avgPPG = h.calcAvgPPG();
	avgPGR = h.calcAvgPGR();
	avgSPG = h.calcAvgSPG();
	avgBPG = h.calcAvgBPG();
	avg3pt = h.calcAvg3ptp();
}


vector<player*> HashTable::getNthBucket(int bucket){
	vector<player*> ret;
	player* temp = hashTable[bucket];

	while (temp != NULL){
		cout << "pushing: " << temp->name << endl;
		ret.push_back(temp);
		temp = temp->next;
	}

	return ret;
}
// void HashTable::buildTable(MaxHeap h){
// 	vector<player*> temp;

// 	h.calcAvgPPG();
// 	h.calcAvgPGR();
// 	h.calcAvgSPG();
// 	h.calcAvgBPG();
// 	h.calcAvg3ptp();

// 	int size = h.getCurrentSize();

// 	for (int i = 0; i < size; i++){
// 		player* curr = h.extractMax();

// 		temp.push_back(curr);
// 		insertItem(curr);
// 	}

// 	for (int i = 0; i < temp.size(); i++){
// 		h.insertPlayer(temp[i]);
// 	}

// }
