#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "HashTable.hpp"
#include "playerStruct.h"

using namespace std;

player* HashTable::createNode(string name,string p, int g, string c, double p1, double f, double t, double f2, double a, double r, double s, double b ,double t2, double a2, double s2, double b2, double s3, double s4, double p2,  int g2, double a3)
{
    player* nw = new player(name, p , g, c, p1, f, t, f2, a, r, s, b, t2, a2, s2, b2, s3, s4, p2, g2, a3);
    // nw->data = data;
    // nw->next = NULL;
    return nw;
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
unsigned int HashTable::hashFunction(int data)
{
    return (data % tableSize);
}
//
// // TODO Complete this function
// //function to search
player* HashTable::searchItem(int aggregateScore)
{
    //Compute the index by using the hash function
    int index = hashFunction(aggregateScore);
    player *temp = hashTable[index];
    while(temp!=NULL)
    {
      if(temp->aggregateScore==aggregateScore)
      {
        return temp;
      }
      temp = temp->next;
    }
    return NULL;
}

bool HashTable::insertItem(string name,string p, int g, string c, double p1, double f, double t, double f2, double a, double r, double s, double b ,double t2, double a2, double s2, double b2, double s3, double s4, double p2,  int g2, double a3)
{
    if(!searchItem(a3))
    {
        // TODO :
        // Use the hash function on the data to get the index/slot,
        // create a new node with the data and insert it in this slot's list
        player* n = new player(name, p , g, c, p1, f, t, f2, a, r, s, b, t2, a2, s2, b2, s3, s4, p2, g2, a3);
        // n->data = data;
        // n->next = NULL;
        int index = hashFunction(n->aggregateScore);
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
        cout<<"duplicate entry: "<<name<<endl;
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
          cout << temp->name << " ";
          temp = temp->next;
        }
        cout << endl;
        //TODO
    }

 }

int main()
{
  HashTable h(7);
  h.insertItem("A", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,17);
  h.insertItem("V", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,2);
  h.insertItem("T", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,7);
  h.insertItem("E", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,47);
  h.insertItem("Y", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,27);
  h.insertItem("B", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,18);
  h.insertItem("C", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,13);
  h.insertItem("Q", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,15);
  h.insertItem("M", "point guard", 9, "Duke", 1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,11);

  h.printTable();
}
