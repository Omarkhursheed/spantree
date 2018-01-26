#include <iostream>
#include <cstdlib>
#include <list>
using namespace std;

class Graph
{
	int numberOfVertices;
	list<int> *adjList;
	bool containsCycle(int n, bool visitedArray[], int parent);
public:
	Graph(int numberOfVertices);
	void insertEdge(int firstVertex, int secondVertex);
	void removeEdge(int firstVertex, int secondVertex);
	bool isTree();
};

Graph::Graph(int numberOfVertices){
	this->numberOfVertices = numberOfVertices;
	adjList = new list<int>[numberOfVertices];
}

void Graph::insertEdge(int firstVertex, int secondVertex){
	adjList[firstVertex].push_back(secondVertex);
	adjList[secondVertex].push_back(firstVertex);
}

void Graph::removeEdge(int firstVertex, int secondVertex){
	adjList[firstVertex].remove(secondVertex);
	adjList[secondVertex].remove(firstVertex);
}
int main(int argc, char const *argv[])
{
	
	return 0;
}