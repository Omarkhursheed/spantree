#include <iostream>
#include <cstdlib>
#include <list>
#include <tuple>
#include <vector>
using namespace std;

int numberOfTrees = 0;
class Graph
{
public:
	int numberOfVertices;
	vector<int> *adjList;
	bool containsCycle(int n, bool visitedArray[], int parent);
	vector<int> edgeList;
	int numberOfEdges;
	Graph(int numberOfVertices);
	void insertEdge(int firstVertex, int secondVertex);
	void removeEdge(int firstVertex, int secondVertex);
	int getEdges();
	bool isTree();
	void printGraph();
};

void allSpanTrees(Graph *g, int x, int numberOfEdges);
void comboUtil(Graph *g, bool mask[], int arr[], int n, int r, int index, int data[], int i);
void Combo(Graph *g, bool mask[],int arr[], int n, int r);
void printTree(Graph *g, bool mask[], int n);
Graph::Graph(int numberOfVertices){
	this->numberOfVertices = numberOfVertices;
	adjList = new vector<int>[numberOfVertices];
	//cout<<"GRAPH CREATED!"<<endl;
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
	 vector<int>::iterator i;
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

int Graph::getEdges(){
	return numberOfEdges;
}

void Graph::printGraph(){
	vector<int>::iterator j;
	cout << "Vertex" << "\t Connections" << endl;
	for(int i = 0; i < numberOfVertices; i++){
		cout << i << "\t";
		for(j = adjList[i].begin(); j != adjList[i].end(); j++){
			cout << *j << "  ";
		}
		cout << endl;
	}
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
	
	//Graph g(numberOfVertices);
	Graph *g = new Graph(numberOfVertices);
	int firstVertex;
	int secondVertex;
	for(int i = 0; i < numberOfEdges; i++){
		cout << "Edge " << i << ":" << endl;
		cout << "First Vertex: ";
		cin >>  firstVertex;
		cout << "Second Vertex: ";
		cin >> secondVertex;
		g->insertEdge(firstVertex, secondVertex);
	}
	cout << "Your graph is: " << endl;
	g->printGraph();
	allSpanTrees(g, numberOfVertices-1, numberOfEdges);
	return 0;
}

void Combo(Graph *g, bool mask[],int subsetArray[], int totalNumber, int numberRequested){
	int data[numberRequested];
	comboUtil(g, mask, subsetArray, totalNumber, numberRequested, 0, data, 0);
}
void comboUtil(Graph *g, bool mask[], int subsetArray[], int totalNumber, int  numberRequested, int index, int data[], int i){
	if (index == numberRequested) {
		for(int j = 0; j < totalNumber; j++){
			mask[j] = false;
		}
        for (int j = 0; j < numberRequested; j++){
            //cout << data[j] << "\t";
        	mask[data[j]] = true;
        }
        printTree(g, mask, totalNumber);
        cout << endl;
        return;
    }
 
    if (i >= totalNumber)
        return;
	
	data[index] = subsetArray[i];
	comboUtil(g, mask, subsetArray, totalNumber, numberRequested, index + 1, data, i+1);
	comboUtil(g, mask, subsetArray, totalNumber, numberRequested, index, data, i+1);
}
void allSpanTrees(Graph *g, int x, int numberOfEdges){
	//Select x=numberOfVertices-1 edges from all edges
	bool mask[numberOfEdges];
	int numbers[numberOfEdges];
	for(int i = 0; i < numberOfEdges; i++){
		mask[i] = false;
		numbers[i] = i;
	}
	cout << endl;
	Combo(g, mask, numbers, numberOfEdges, x);
	
}




void printTree(Graph *g, bool mask[], int n){
	//Graph gCopy(numberOfVertices);
	Graph *gCopy  = new Graph(g->numberOfVertices);
	int some = g->numberOfVertices;
	gCopy->numberOfVertices = some;
	vector<int>::iterator i;
	for(int j = 0; j < some; j++){
		 for(i = g->adjList[j].begin(); i != g->adjList[j].end(); i++){
		 	gCopy->adjList[j].push_back(*i);
		 }
	}
	for(i = g->edgeList.begin(); i != g->edgeList.end(); i++){
		gCopy->edgeList.push_back(*i);
	} 
	gCopy->numberOfEdges = g->numberOfEdges;
	int j = 0; 
	int x = gCopy->getEdges();
	i = gCopy->edgeList.begin();
	/*cout << "mask in tree\n";
	for(int i = 0; i < n; i++){
		cout << mask[i] << '\t';
	}*/
	cout << endl;
	for(j = 0; j < n; j++){
		if(!mask[j]){
			gCopy->removeEdge(*i,*(i+1));
//			gCopy.removeEdge(gCopy.edgeList[*i], gCopy.edgeList[*(i+1)]);
		}
		i+=2;
	}
	if(gCopy->isTree()){
		cout << "Spanning Tree " << ++numberOfTrees << endl;
		gCopy->printGraph();
	}
}