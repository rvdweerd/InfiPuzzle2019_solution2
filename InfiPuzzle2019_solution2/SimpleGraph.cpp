#include "SimpleGraph.h"
#include <iostream>
#include <queue>

void SimpleGraph::AddNode(std::string name)
{
	if (nodeMap.find(name) == nodeMap.end()) // safety: avoid duplicate node entries
	{
		Node* newnode = new Node(name);
		nodeMap[name] = newnode;
		nodes.insert(newnode);
	}
}

void SimpleGraph::AddArc(Node* start, Node* finish, int cost)
{
	bool arcexists = false;
	for (auto a : start->arcs) // safety: avoid duplicate arc entries
	{
		if (a->start == start && a->finish == finish)
		{
			arcexists = true;
			break;
		}
	}
	if (!arcexists)
	{
		Arc* newarc = new Arc(start, finish, cost);
		start->arcs.insert(newarc);
		arcs.insert(newarc);
	}
}

void SimpleGraph::AddOneWayConnection(std::string n1, std::string n2, int c)
{
	if (nodeMap.find(n1) == nodeMap.end())
	{
		AddNode(n1);
	}
	if (nodeMap.find(n2) == nodeMap.end())
	{
		AddNode(n2);
	}
	AddArc(nodeMap[n1], nodeMap[n2], c);
}
void SimpleGraph::AddTwoWayConnection(std::string n1, std::string n2, int c)
{
	if (nodeMap.find(n1) == nodeMap.end())
	{
		AddNode(n1);
	}
	if (nodeMap.find(n2) == nodeMap.end())
	{
		AddNode(n2);
	}
	AddArc(nodeMap[n1], nodeMap[n2], c);
	AddArc(nodeMap[n2], nodeMap[n1], c);
}

void SimpleGraph::PrintAdjacencyList()
{
	std::cout << "\nAdjacency List van de graph\n";
	std::cout << "==== van ==== -> ======= naar ========================\n";

	for (Node* n : nodes)
	{
		std::cout << n->name << " [" << n->arcs.size() << "] arcs -> ";
		for (Arc* a : n->arcs)
		{
			std::cout << a->finish->name << " cost[" << a->cost << "], ";
		}
		std::cout << std::endl;
	}
}

void SimpleGraph::DFS(std::string startname)
{
	if (nodeMap.find(startname) != nodeMap.end())
	{
		DFS(nodeMap[startname]);
	}
}

void SimpleGraph::DFS(Node* startnode)
{
	visited.clear();
	visitUsingDFS(startnode);
}

void SimpleGraph::BFS(std::string startname)
{
	if (nodeMap.find(startname) != nodeMap.end())
	{
		BFS(nodeMap[startname]);
	}
}

void SimpleGraph::BFS(Node* startnode)
{
	visited.clear();
	while (!tovisit.empty()) tovisit.pop();
	tovisit.push(startnode);
	visited.insert(startnode);
	visitUsingBFS();
}

void SimpleGraph::VisitFunction1(Node* node)
{
	std::cout << node->name << " visited.\n";
}

std::vector<SimpleGraph::Arc*> SimpleGraph::findShortestPath(Node* start, Node* finish)
{
	std::vector<Arc*> path;
	std::priority_queue< std::vector<Arc*>, std::vector<std::vector<Arc*>>, GreaterPathLength> queue;
	std::map<std::string, int> fixed;
	while (start != finish)
	{
		if (fixed.find(start->name) == fixed.end())
		{
			fixed[start->name] = getPathCost(path);
			for (Arc* arc : start->arcs)
			{
				if (fixed.find(arc->finish->name) == fixed.end())
				{
					path.push_back(arc);
					queue.push(path);
					path.pop_back();
				}
			}
		}
		if (queue.size() == 0)
		{
			path.clear();
			return path;
		}
		path = queue.top(); queue.pop();
		start = path[path.size() - 1]->finish;
	}
	return path;
}

int SimpleGraph::getPathCost(const std::vector<Arc*>& path)
{
	int cost = 0;
	for (Arc* arc : path)
	{
		cost += arc->cost;
	}
	return cost;
}



void SimpleGraph::visitUsingDFS(Node* node)
{
	if (visited.find(node) == visited.end())
	{
		VisitFunction1(node);
		visited.insert(node);
		for (Arc* a : node->arcs)
		{
			visitUsingDFS(a->finish);
		}
	}
	else
	{
		return;
	}
}

void SimpleGraph::visitUsingBFS()
{
	while (!tovisit.empty())
	{
		Node* nextnode = tovisit.front();
		tovisit.pop();
		VisitFunction1(nextnode);

		for (Arc* a : nextnode->arcs)
		{
			if (visited.find(a->finish) == visited.end())
				tovisit.push(a->finish);
			visited.insert(a->finish);
		}
	}
	return;
}
