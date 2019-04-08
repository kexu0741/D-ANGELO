#include <iostream>
#include <list>

using namespace std;

class Graph{
	int V; //number of vertices

	//pointer to an array containing adjacency lists
	list <int> *adj;

public:
	Graph(int V);

	void addEdge(int v, int w);

	//prints BFS traversal from a given source s
	void BFS(int s);

	//recursive helper function
	void DFSUtil(int v, bool visited[]);
	//DFS traversal of the vertices reachable from v
	void DFS(int v);
};

Graph::Graph(int V){
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
	adj[v].push_back(w);
}

void Graph::BFS(int s){
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++){
		visited[i] = false;
	}

	list<int> queue;

	//mark the current node as visited and enqueue it
	visited[s] = true;
	queue.push_back(s);

	list<int>::iterator i;
	while(!queue.empty()){
		//dequeue a vertex from the queue and print it
		s = queue.front();
		cout << s << " ";
		queue.pop_front();

		//get all adjacent vertices of the deqeued vertex s. If adjacent has not been visited, mark it,
		//enqueue it
		for (i = adj[s].begin(); i !=adj[s].end(); ++i){
			if (!visited[*i]){
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}

}

void Graph::DFSUtil(int v, bool visited[]){
	visited[v] = true;
	cout << v << " ";

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i){
		if (!visited[*i]){
			DFSUtil(*i, visited);
		}
	}
}

void Graph::DFS(int v){
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++){
		visited[i] = false;
	}

	DFSUtil(v, visited);

}

//new comment aye

int main(){
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Depth First Traversal starting from vertex 2: " << endl;
	g.DFS(2);
	cout << endl;
	
	cout << "Bredth First Traversal starting from vertex 2: " << endl;
	g.BFS(2);
	cout << endl;

	return 0;
}
