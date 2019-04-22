#ifndef HASH_HPP
#define HASH_HPP
#include "playerStruct.h"
#include "MaxHeap.hpp"

using namespace std;

// struct node
// {
//     int data; // data to be stored in the node
//     struct node* next; // pointer to the next node
// };

class HashTable
{
    // No. of buckets (Size of the Hash Table)
    int tableSize;
    double avgPPG;
    double avgPGR;
    double avgSPG;
    double avgBPG;
    double avg3pt;

    // Pointer to an array containing buckets (the Hash Table)
    player **hashTable;

  	/*
  	Method Name: createNode
  	Purpose: Create a node with data as 'key'
    return: pointer to the new node
  	*/
    player* createNode(string name,string p, int g, string c, double p1, double f, double t, double f2, double a, double r, double s, double b ,double t2, double a2, double s2, double b2, double s3, double s4, double p2,  int g2, double a3);

    public:

    /*
    constructor
    Purpose: perform all operations necessary to instantiate a class object
    Param: Size of the Hash Table
    return: none
    */
    HashTable(int bsize);

    /*
    destructor
    Purpose: perform all operations necessary to destroy class object
    return: none
    */
    ~HashTable();

  	/*
  	Method Name: insertItem
  	Purpose: inserts a node with data as 'key' into the Hash Table
    return: false if 'key' already exists in the table, otherwise true
  	*/
    bool insertItem(player* n);

    /*
  	Method Name: hashFunction
  	Purpose: function to hash "key" into an index
    return: index in the Hash Table
  	*/
    unsigned int hashFunction(player* p);

    /*
  	Method Name: printTable
  	Purpose: function to display the Hash Table
    return: none
  	*/
    void printTable();

    /*
  	Method Name: searchItem
  	Purpose: function to search for "key" in the Hash Table
    return: node with "key" as it's data if found, otherwise NULL
  	*/
    player* searchItem(player* p);

    void buildTable(MaxHeap &h);
};

#endif
