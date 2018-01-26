#pragma once
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Greedy.h"
#include "Uniform.h"

#include <functional> 
#include <set>
#include<map>
#include <cmath>
# define PI           3.14159265358979323846  /* pi */
using namespace std;


class Greedy
{
	Graph GenericGraph;
	string SourceCity;
	string TargetCity;

public:
	Greedy(Graph, string, string);
	~Greedy();
	vector<string> ExpandedNodes;
	map<string, float> ActualCost;
	vector<string> SolutionPath;
	void ExecutePathSearchAlgorithm();
	map<vector<string>, float> estimated_cost_data_structure;
private:
	float EstimateHeuristic(string, string);
	void RemoveDuplicatePaths();
	vector<string> ShiftMinCostElementToTop(map<vector<string>, float>);
};

Greedy::Greedy(const Graph USGraph, const string source, const  string destination)
{
	GenericGraph = USGraph;
	SourceCity = source;
	TargetCity = destination;
}

void Greedy::ExecutePathSearchAlgorithm()
{
	/** Declare data structures */

	/** Initialize open_list, estimated_cost in data structure and priority queue for min_cost */
	estimated_cost_data_structure[vector<string> {SourceCity}] = 0;
	vector<string> next_path = vector<string>{ SourceCity };
	ActualCost[SourceCity] = 0;
	float current_path_cost = 0;
	/** While there are elements in open_list */
	while (estimated_cost_data_structure.size() != 0)
	{
		/** Take out the path with min_cost ... saved at the back of the list */
		vector<string> current_node = next_path;

		/** Remove from open_list*/
		estimated_cost_data_structure.erase(current_node);
		/** Add to Closed_list ... ExpandedNodes*/
		ExpandedNodes.push_back(current_node.back());
		current_path_cost = ActualCost[current_node.back()];

		/** If last node on path is goal, then add return */
		if (current_node.back().compare(TargetCity) == 0)
		{
			SolutionPath = current_node;
			return;
		}
		else
		{
			/** Get the successors of the last node on path*/
			map<string, float> successor_list = GenericGraph.GetNodeNeighbours(current_node.back());
			map <string, float> ::iterator succ_iterator;
			float minimum_cost = FLT_MAX;
			/** For each successor */
			for (succ_iterator = successor_list.begin(); succ_iterator != successor_list.end(); ++succ_iterator)
			{
				/** Find cost to reach fron source*/
				if (find(ExpandedNodes.begin(), ExpandedNodes.end(), succ_iterator->first) == ExpandedNodes.end())
				{
					float updated_cost = current_path_cost + succ_iterator->second;
					if (ActualCost.find(succ_iterator->first) == ActualCost.end())
					{
						ActualCost[succ_iterator->first] = updated_cost;
					}
					else
					{
						ActualCost[succ_iterator->first] = ActualCost[succ_iterator->first] > updated_cost ? updated_cost : ActualCost[succ_iterator->first];
					}

					/** Find remaining cost to goal */
					float heuristic_distance = EstimateHeuristic(succ_iterator->first, TargetCity);

					/** Add successor path to open_list */
					vector<string> current_path = current_node;
					current_path.push_back(succ_iterator->first);

					/** Add correspoding cost of successor to the data structure */
					estimated_cost_data_structure[current_path] = heuristic_distance;
				}
			}
			/** Remove two paths reaching to same destination and keep the one path with least cost */
			if (current_node.back().compare("richmond") == 0)
			{
				string temp = current_node.back();
			}

			RemoveDuplicatePaths();

			next_path = ShiftMinCostElementToTop(estimated_cost_data_structure);
		}
	}
}


inline float Greedy::EstimateHeuristic(string start, string end)
{
	/** Value is sqrt((69.5 * (Lat1 - Lat2)) ^ 2 + (69.5 * cos((Lat1 + Lat2)/360 * pi) * (Long1 - Long2)) ^ 2) */
	float a = (float)pow(69.5 * (GenericGraph.GetNode(start).Latitude - GenericGraph.GetNode(end).Latitude), 2);
	float b = (float)cos((GenericGraph.GetNode(start).Latitude + GenericGraph.GetNode(end).Latitude) / 360 * PI);
	float c = (float)(GenericGraph.GetNode(start).Longitude - GenericGraph.GetNode(end).Longitude);
	return (float)sqrt(a + pow((69.5 * b * c), 2));
}


vector<string> Greedy::ShiftMinCostElementToTop(map <vector<string>, float> estimated_cost_data_structure)
{
	map<vector<string>, float>::iterator cost_iter;
	float min = FLT_MAX;
	vector<string> required_path;
	for (cost_iter = estimated_cost_data_structure.begin(); cost_iter != estimated_cost_data_structure.end(); cost_iter++)
	{
		if (min > cost_iter->second)
		{
			required_path = cost_iter->first;
			min = cost_iter->second;
		}
	}

	return required_path;
}

void Greedy::RemoveDuplicatePaths()
{
	set<vector<string>> remove_indices;
	set<vector<string>>::iterator set_iterator;
	map <vector<string>, float> result;
	map<vector<string>, float>::iterator cost_iter, inner_cost_iter;

	for (cost_iter = estimated_cost_data_structure.begin(); cost_iter != estimated_cost_data_structure.end(); cost_iter++)
	{
		for (inner_cost_iter = estimated_cost_data_structure.begin(); inner_cost_iter != estimated_cost_data_structure.end(); inner_cost_iter++)
		{
			if (cost_iter->first.back().compare(inner_cost_iter->first.back()) == 0 && cost_iter != inner_cost_iter)
			{
				if (cost_iter->second > inner_cost_iter->second)
				{
					remove_indices.insert(cost_iter->first);
				}
				else
				{
					remove_indices.insert(inner_cost_iter->first);
				}
			}
		}
	}


	for (set_iterator = remove_indices.begin(); set_iterator != remove_indices.end(); set_iterator++)
	{
		estimated_cost_data_structure.erase(*set_iterator);
	}


}


Greedy::~Greedy()
{
}

