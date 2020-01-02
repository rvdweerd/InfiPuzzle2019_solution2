#pragma once
#include <iostream>
#include <vector>

struct Node
{
	std::pair<int, int> pos;
	std::pair<int, int> reachedWithJump;
	std::vector<Node*> nextFlats;
	int totalEnergyUsed;
};

namespace GraphTraversalFunctions
{
	void PrintFunc(Node* node, std::set<int> & set )
	{
		std::cout << "Eind node bereikt, info:\m";
		std::cout << "pos = (" << node->pos.first << "," << node->pos.second << ")\n";
		std::cout << "reached with jump (" << node->reachedWithJump.first << "," << node->reachedWithJump.second << ")\n";
		std::cout << "next flat addresses: "; for (auto n : node->nextFlats) { std::cout << n; }
		std::cout << "total energy used = " << node->totalEnergyUsed << std::endl;
		std::cin.get();
	}
	void GetEnergySet(Node* node, std::set<int>& routeEnergy)
	{
		routeEnergy.insert(node->totalEnergyUsed);
	}
}