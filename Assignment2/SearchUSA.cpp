#include "stdafx.h"
#include <algorithm>
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "stdafx.h"

#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "AStar.h"
#include "Greedy.h"
#include "Uniform.h"

using namespace std;


int main(int argc, char* argv[])
{
	string line;
	Graph USGraph;

	ifstream myfile("usroads.pl");
	if (myfile.is_open())
	{
		int found_node = -1;
		int found_edge = -1;
		while (getline(myfile, line))
		{
			found_node = line.find("city(");
			found_edge = line.find("road(");
			if (found_node == 0)
			{
				
				std::size_t name_found = line.find(",");
				string name = line.substr(5, name_found-5);

				std::size_t lat_found = line.find(",", name_found +1);
				float latitude = stof(line.substr(name_found + 1, lat_found - name_found - 1));

				std::size_t long_found = line.find(",", lat_found + 1);
				float longitude = stof(line.substr(lat_found + 1, long_found - lat_found - 1));
				
				//cout << name << "\t " << endl;
				Node new_node(name, latitude, longitude);
				USGraph.AddNewNode(new_node);
				found_node = -1;
			}
			if (found_edge == 0)
			{
				std::size_t name_found = line.find(",");
				string city_one = line.substr(5, name_found - 5);

				std::size_t city1_found = line.find(",", name_found + 1);
				string city_two = line.substr(name_found + 2, city1_found - name_found - 2);

				std::size_t city2_found = line.find(",", city1_found + 1);
				float distance = stof(line.substr(city1_found + 2, city2_found - city1_found - 1));

				//cout << city_one  << city_two << distance << endl;
				Edge new_edge(city_one, city_two, distance);
				USGraph.AddNewEdge(new_edge);
				found_edge = -1;
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	cout << "SOURCE CITY : " << argv[2] << ", DESTINATION CITY : " << argv[3] << "\n";
	string search_type = argv[1];
	string source = argv[2];
	string destination = argv[3];
	
	
	/*
	for (Node node1 : USGraph.NodeList)
	{
		for (Node node2 : USGraph.NodeList)
		{

			if (node1.Name.compare(node2.Name) != 0)
			{
				AStar a(USGraph, node1.Name, node2.Name);
				Uniform g(USGraph, node1.Name, node2.Name);
				a.ExecutePathSearchAlgorithm();
				g.ExecutePathSearchAlgorithm();
				if (a.SolutionPath.size() < g.SolutionPath.size())
				{
					cout << node1.Name << " " << node2.Name << "\n";
					break;
				}
			}
		}
	}
	*/
	
	if (search_type.compare("astar") == 0)
	{
		cout << "ASTAR ALGORITHM\n\n";
		AStar astar_on_USA(USGraph, source, destination);
		astar_on_USA.ExecutePathSearchAlgorithm();

		cout << "Nodes Expanded: ";
		map<vector<string>, float>::iterator node_iter;
		for (string node_iter : astar_on_USA.ExpandedNodes)
		{
			cout << node_iter << " ";
		}

		cout << "\nNumber of Nodes Expanded : " << astar_on_USA.ExpandedNodes.size() <<"\n\n";
		cout << "SOLUTION PATH : ";
		for (int index = 0; index < astar_on_USA.SolutionPath.size(); index++)
		{
			cout << astar_on_USA.SolutionPath[index] << " ";
		}

		cout << "\nNumber of Nodes in Solution : " << astar_on_USA.SolutionPath.size() << "\n";
		cout << "\nDistance till Destination : " << astar_on_USA.ActualCost[destination] << "\n";
		
	}
	else if (search_type.compare("greedy") == 0)
	{
		cout << "GREEDY ALGORITHM\n\n";
		Greedy greedy_on_USA(USGraph, source, destination);
		greedy_on_USA.ExecutePathSearchAlgorithm();

		cout << "Nodes Expanded: ";
		map<vector<string>, float>::iterator node_iter;
		for (string node_iter : greedy_on_USA.ExpandedNodes)
		{
			cout << node_iter << " " ;
		}

		cout << "\nNumber of Nodes Expanded : " << greedy_on_USA.ExpandedNodes.size() << "\n\n";
		cout << "SOLUTION PATH : ";
		for (int index = 0; index < greedy_on_USA.SolutionPath.size(); index++)
		{
			cout << greedy_on_USA.SolutionPath[index] << " ";
		}

		cout << "\nNumber of Nodes in Solution : " << greedy_on_USA.SolutionPath.size() << "\n";
		cout << "\nDistance till Destination : " << greedy_on_USA.ActualCost[destination] << "\n";

	}
	else if (search_type.compare("uniform") == 0)
	{
		cout << "UNIFORM ALGORITHM\n\n";
		Uniform uniform_on_USA(USGraph, source, destination);
		uniform_on_USA.ExecutePathSearchAlgorithm();

		cout << "Nodes Expanded: ";
		map<vector<string>, float>::iterator node_iter;
		for (string node_iter : uniform_on_USA.ExpandedNodes)
		{
			cout << node_iter << " " ;
		}


		cout << "\nNumber of Nodes Expanded : " << uniform_on_USA.ExpandedNodes.size() << "\n\n";
		cout << "SOLUTION PATH : ";
		for (int index = 0; index < uniform_on_USA.SolutionPath.size(); index++)
		{
			cout << uniform_on_USA.SolutionPath[index] << " ";
		}
		cout << "\nNumber of Nodes in Solution : " << uniform_on_USA.SolutionPath.size() << "\n";
		cout << "\nDistance till Destination : " << uniform_on_USA.ActualCost[destination] << "\n";
	}
	else
	{
		cout << "UNKNOWN SEARCH TYPE ALGORITHM \n";
	}
	
	getchar();
    return 0;
}

