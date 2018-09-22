#pragma once
#include <algorithm>
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "stdafx.h"
using namespace std;

class Edge
{
	
public:
	string StartCity;
	string EndCity;
	float Distance;
	Edge(string city_one, string city_two, float distance);
	~Edge();
};

Edge::Edge(string city_one, string city_two, float distance)
{
	StartCity = city_one;
	EndCity = city_two;
	Distance = distance;
}

Edge::~Edge()
{
}