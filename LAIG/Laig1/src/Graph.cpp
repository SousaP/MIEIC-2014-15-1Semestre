#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Graph.h"
#include "Node.h"

Graph::Graph() {

}

Graph::graphMap Graph::getGraph() {
	return this->graph;
}

void Graph:: addNode(Node* n){
	graph[n->getID()] = n;
}