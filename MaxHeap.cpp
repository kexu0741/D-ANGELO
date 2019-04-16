#include <iostream>
#include <climits>
#include "MaxHeap.hpp"

//TODO: EXTRACTMAX (REPAIR DOWNWARD), DELETE PLAYER NODE

using namespace std;

void MaxHeap::swap(player* a, player* b){
	player temp = *a;
	*a = *b;
	*b = temp;
}

MaxHeap::MaxHeap(int cap){
	currentSize = 0;
	capacity = cap;
	heapArr = new player[capacity];
}	

MaxHeap::~MaxHeap(){

}

/*
Finds the parent of a node, given its index.
*/
int MaxHeap::parent(int index)
{
  return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int MaxHeap::leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int MaxHeap::rightChild(int index)
{
  return ((2*index) + 2);
}

void MaxHeap::insertPlayer(player p){
	if(currentSize == capacity)
  	{
	    cout<<"Error: Maximum heap size reached. Cannot insert anymore"<<endl;
	    return;
  	}

	currentSize = currentSize + 1;
	int index = currentSize - 1;
	heapArr[index] = p;

	while (index != 0 && heapArr[parent(index)].aggregateScore <= heapArr[index].aggregateScore)
	{
		//swap(&heapArr[index], &heapArr[parent(index)]);
		if (heapArr[parent(index)].aggregateScore == heapArr[index].aggregateScore){
			if (heapArr[parent(index)].ppg < heapArr[index].ppg){
				swap(&heapArr[index], &heapArr[parent(index)]);
			}
			else if(heapArr[parent(index)].aggregateScore < heapArr[index].aggregateScore){
				swap(&heapArr[index], &heapArr[parent(index)]);
			}
		}
		index = parent(index);
	}
}
