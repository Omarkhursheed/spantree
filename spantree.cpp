#include <iostream>
#include <cstdlib>
#include <list>
#include <tuple>
using namespace std;

class Graph
{
public:
	int numberOfVertices;
	list<int> *adjList;
	int adjMatrix[numberOfVertices][numberOfVertices];
	bool containsCycle(int n, bool visitedArray[], int parent);
	vector<int> edgeList;
	int numberOfEdges = 0;
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
	numberOfEdges++;
	edgeList.push_back(firstVertex);
	edgeList.push_back(secondVertex);
	adjList[secondVertex].push_back(firstVertex);
}

void Graph::removeEdge(int firstVertex, int secondVertex){
	adjList[firstVertex].erase(remove(adjList[firstVertex].begin(), adjList[firstVertex].end(), secondVertex),adjList[firstVertex].end());
	adjList[secondVertex].erase(remove(adjList[secondVertex].begin(), adjList[secondVertex].end(), firstVertex),adjList[secondVertex].end());
}

bool Graph::containsCycle(int n, bool visitedArray[], int parent){
	 visitedArray[n] = true;
	 list<int>::iterator i;
	 for(i = adjList[n].begin(); i != adjList[n].end(); i++){
	 	if(!visitedArray[*i]){
	 		if(containsCycle(*i, visitedArray, n)){
	 			return true;
	 		}
	 	}
	 	else if (*i != parent){
	 		return true;
	 	}
	 }
	 return false;
}

bool Graph::isTree(){
	bool *visitedArray = new bool[numberOfVertices];
	for(int i = 0; i < numberOfVertices; i++){
		visitedArray[i] = false;
	}
	if(containsCycle(0, visitedArray, -1)){
		return false;
	}
	for(int j = 0; j < numberOfVertices; j++){
		if(!visitedArray[j]){
			return false;
		}
	}
	return true;
}

void allSpanTrees(Graph g, int x, int numberOfEdges){
	//Select x=numberOfVertices-1 edges from all edges
	vector<int>::iterator i;
	bool mask[numberOfEdges];
	int numbers[numberOfEdges];
	for(int i = 0; i < numberOfEdges; i++){
		mask[i] = true;
		numbers = i;
	}

	
}
void Combo(int arr[], int n, int r){
	int data[r],
	comboUtil(arr, n, r, 0, data, 0);
}

void comboUtil(int arr[], int n, int r, int index, int data[], int i){
	if(index == r){
		for(int j = 0; j < r; j++){
			cout << data[j];
		}
		cout << endl;
	}

	if(i >= n){
		return;
	}
	data[index] = arr[i];
	comboUtil(arr, n, r, index + 1, data, i+1);
	comboUtil(arr, n, r, index, data, i+1);
}
int main(int argc, char const *argv[])
{	
	int numberOfVertices;
	int numberOfEdges;
	cout << "Enter the number of vertices in the graph: ";
	cin >> numberOfVertices;
	cout << "How many edges do you want in the graph? ";
	cin >> numberOfEdges;
	cout << "Enter the edges: " << endl;
	
	Graph g(numberOfVertices);
	int firstVertex;
	int secondVertex;
	for(int i = 0; i < numberOfEdges; i++){
		cout << "Edge " << i << ":" << endl;
		cout << "First Vertext: ";
		cin >>  firstVertex;
		cout << "Second Vertex: ";
		cin >> secondVertex;
		g.insertEdge(firstVertex, secondVertex);
	}

	allSpanTrees(g, numberOfVertices-1);
	return 0;
}