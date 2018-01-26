#pragma once
#include <algorithm>
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "stdafx.h"

#include <map>
using namespace std;

class Graph
{
	
public:
	vector<Node> NodeList;
	vector<Edge> EdgeList;
	Graph();
	void AddNewNode(Node node);
	void AddNewEdge(Edge edge);
	Node GetNode(string);
	map<string, float> GetNodeNeighbours(string);
	~Graph();
};

Graph::Graph()
{

}

void Graph::AddNewNode(Node node)
{
	NodeList.push_back(node);
}

void Graph::AddNewEdge(Edge edge)
{
	EdgeList.push_back(edge);
}

Node Graph::GetNode(string nodeName)
{
	for (Node current_node : NodeList)
	{
		if (current_node.Name.compare(nodeName) == 0)
		{
			return current_node;
		}
	}

	cout << "No node named %s in the graph." << "\n";
}

 map<string, float> Graph::GetNodeNeighbours( string startNode)
{
	map< string, float> result;
	for (Edge current_edge : EdgeList)
	{
		if (current_edge.StartCity.compare(startNode) == 0 )
		{
			//result[GetNode(current_edge.EndCity)] = current_edge.Distance;
			result[current_edge.EndCity] = current_edge.Distance;
		}	
		else if (current_edge.EndCity.compare(startNode) == 0)
		{
			//result[GetNode(current_edge.StartCity)] = current_edge.Distance;
			result[current_edge.StartCity] = current_edge.Distance;
		}
	}

	return result;
}

Graph::~Graph()
{
}