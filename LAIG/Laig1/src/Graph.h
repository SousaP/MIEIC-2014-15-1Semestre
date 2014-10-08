#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "CGFscene.h"
#include "Node.h"

class Graph {
	typedef map<string, Node*> graphMap;
	graphMap graph;

public:
	Graph();
	graphMap getGraph();
	void addNode(Node* n);
};

#endif