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
using namespace std;


class Node
{
public:
	string Name = "";
	float Latitude = -1;
	float Longitude = -1;
	Node(string name, float latitude, float longitude);
	~Node();
};


Node::Node(string name, float latitude, float longitude)
{
	Name = name;
	Latitude = latitude;
	Longitude = longitude;
}


Node::~Node()
{
}

