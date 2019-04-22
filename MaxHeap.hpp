#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include <iostream>
#include "playerStruct.h"

using namespace std;

class MaxHeap{
	// pointer to array of elements in heap
  player** heapArr;
  // maximum possible size of min heap
  int capacity;
  // Current number of elements in min heap
  int currentSize;

  void swap(player *a, player *b);

public:
	MaxHeap(int cap);
	~MaxHeap();
	int parent(int index);
	int leftChild(int index);
	int rightChild(int index);
	void maxHeapify(int index);
	int getCurrentSize();
	player* extractMax();
  	player* createPlayer(string s[], double d[]);
	void insertPlayer(player* p);
	void print();
	void draftPlayer(string name);
  	int draftPlayerHelper(string name);
  	double calcAvgPPG();
  	double calcAvgPGR();
  	double calcAvgSPG();
  	double calcAvgBPG();
  	double calcAvg3ptp();
  	void resetAverages();

};

#endif
