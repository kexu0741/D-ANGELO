#include <climits>
#include <iostream>
#include "MaxHeap.hpp"

using namespace std;

void MaxHeap::swap(player* a, player* b){
	player temp = *a;
	*a = *b;
	*b = temp;
}

MaxHeap::MaxHeap(int cap){
	currentSize = 0;
	capacity = cap;
	heapArr = new player*[capacity];
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

player* MaxHeap::createPlayer(string s[], double d[]){ //params: arrays passed in from main, read from file
	player* newPlayer = new player;
	newPlayer->name = s[0];  
	newPlayer->position = s[1];
	if (s[2] == "Freshman" || s[2] == "International" || s[2] == "N/A"){
		newPlayer->grade = 1;
	}
	else if(s[2] == "Sophomore"){
		newPlayer->grade = 2;
	}
	else if(s[3] == "Junior"){
		newPlayer->grade = 3;
	}
	else if(s[4] == "Senior"){
		newPlayer->grade = 4;
	}
	newPlayer->college = s[3];
	newPlayer->gamesPlayed = stoi(s[4]); 

	newPlayer->ppg = d[0];
	newPlayer->fgp = d[1];
	newPlayer->threeptp = d[2];
	newPlayer->ftp = d[3];
	newPlayer->apg = d[4]; //assists per game
	newPlayer->rpg = d[5];//rebounds per game
	newPlayer->spg = d[6]; //steals per game
	newPlayer->bpg = d[7]; //blocks per game
	newPlayer->tovpg = d[8]; //turnovers per game
	newPlayer->astto = d[9]; //assist to turnover ratio
	newPlayer->stlto = d[10]; //steal to turnover ratio
	newPlayer->blkto = d[11]; //block to turnover ratio
	newPlayer->sceff = d[12]; //scoring efficiency
	newPlayer->sheff = d[13]; //shooting efficiency
	newPlayer->pfpg = d[14];

	double ageMultiplier = 1;
	double scoringMultiplier = 85.910;

	if (newPlayer->grade == 1){
		ageMultiplier = 10.0;
		if (newPlayer->ppg > 20.0){
			scoringMultiplier = 105.910;
		}
	}
	else if (newPlayer->grade == 2){
		ageMultiplier = 5.0;
		if (newPlayer->ppg >= 20.0){
			scoringMultiplier = 105.910;
		}
	}
	else if (newPlayer->grade == 3){
		ageMultiplier = 2.0;
	}
	else if (newPlayer->grade == 4){
		ageMultiplier = 1.0;
	}

	//"inflated" PER- per game stats are used instead of aggregate stats
	double PER = ((newPlayer->ppg * scoringMultiplier)

	+ (newPlayer->spg * 83.897)

	+ (newPlayer->threeptp * 51.757)

	+ (newPlayer->ftp * 46.845)

	+ (newPlayer->bpg * 39.190)

	+ (newPlayer->blkto	* 39.190)

	+ (newPlayer->apg * 84.677)

	+ (newPlayer->rpg * 24.707)

	- (newPlayer->pfpg * 17.174)

	- ((1 - newPlayer->ftp) * 20.091)

	- ((1 - newPlayer->fgp)	* 39.190)

	- (newPlayer->tovpg * 33.897 )) * (ageMultiplier);

	newPlayer->aggregateScore = PER;

	insertPlayer(newPlayer);

}    //call insertPlayer() in this

void MaxHeap::insertPlayer(player* p){
	if(currentSize == capacity)
  	{
	    cout<<"Error: Maximum heap size reached. Cannot insert anymore"<<endl;
	    return;
  	}

	currentSize = currentSize + 1;
	int index = currentSize - 1;
	heapArr[index] = p;

	while (index != 0 && heapArr[parent(index)]->aggregateScore <= heapArr[index]->aggregateScore)
	{
		//swap(&heapArr[index], &heapArr[parent(index)]);
		if (heapArr[parent(index)]->aggregateScore == heapArr[index]->aggregateScore){
			if (heapArr[parent(index)]->ppg < heapArr[index]->ppg){
				swap(*&heapArr[index], *&heapArr[parent(index)]);
			}
		}
		else if(heapArr[parent(index)]->aggregateScore < heapArr[index]->aggregateScore){
			swap(*&heapArr[index], *&heapArr[parent(index)]);
		}
		index = parent(index);
	}
}

player* MaxHeap::extractMax(){
	if (currentSize <= 0){
		cout << "ERROR: EMPTY" << endl;
	}

	else if (currentSize == 1){
		return heapArr[0];
	}
	else{
		player* max = heapArr[0];
		heapArr[0] = heapArr[currentSize - 1];
		currentSize--;
		maxHeapify(0);

		return max;
	}
}

void MaxHeap::maxHeapify(int index){
	int l = leftChild(index);
	int r = rightChild(index);
	int largest = index;

	if (l < currentSize && heapArr[l]->aggregateScore >= heapArr[index]->aggregateScore){
		if (heapArr[l]->aggregateScore == heapArr[index]->aggregateScore){
			if (heapArr[l]->ppg > heapArr[index]->ppg){
				largest = l;
			}
		}
		else if (heapArr[l]->aggregateScore > heapArr[index]->aggregateScore){
			largest = l;
		}
	}

	if (r < currentSize && heapArr[r]->aggregateScore >= heapArr[largest]->aggregateScore){
		if (heapArr[r]->aggregateScore == heapArr[largest]->aggregateScore){
			if (heapArr[r]->ppg > heapArr[largest]->ppg){
				largest = r;
			}
		}
		else if (heapArr[r]->aggregateScore > heapArr[largest]->aggregateScore){
			largest = r;
		}
	}

	if (largest != index){
		swap(*&heapArr[index], *&heapArr[largest]);
		maxHeapify(largest);
	}

}

// int main(){

// }