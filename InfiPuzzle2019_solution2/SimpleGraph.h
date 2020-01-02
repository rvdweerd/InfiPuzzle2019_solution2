#pragma once
#include <string>
#include <set>
#include <map>
#include <queue>

class SimpleGraph
{
public:
	SimpleGraph() = default;
	~SimpleGraph() // destructor t.b.v. memory mgt
	{
		for (Arc* a : arcs) delete a;
		for (Node* n : nodes) delete n;
	}
	struct Arc;
	struct Node
	{
		Node(std::string name)
			:
			name(name)
		{}
		// Basisvelden t.b.v. graph functionaliteit
		std::string name;
		std::set<Arc*> arcs;
		// Voeg hier aanvullende datavelden per node toe
		std::pair<int,int> DeSerializeNodePosition(std::string name)
		{
			auto pos0 = name.find("("); 
			auto pos1 = name.find(",");
			auto pos2 = name.find(")");
			int first = std::stoi(name.substr(pos0 + 1, pos1 - pos0 - 1));
			int second = std::stoi(name.substr(pos1 + 1, pos2 - pos1 - 1));
			return { first,second };
		}

	};
	struct Arc
	{
		Arc(Node* s, Node* f, int c)
			:
			start(s),
			finish(f),
			cost(c)
		{
		}
		Node* start;
		Node* finish;
		int cost;
	};
public:
	void AddNode(std::string name);
	void AddArc(Node* start, Node* finish, int cost);
	void AddOneWayConnection(std::string n1, std::string n2, int c);
	void AddTwoWayConnection(std::string n1, std::string n2, int c);
	void PrintAdjacencyList();
	void DFS(std::string startname);
	void DFS(Node* startnode);
	void BFS(std::string startname);
	void BFS(Node* startnode);
	void VisitFunction1(Node* node);
	bool NodeExists(std::string name)
	{
		return (nodeMap.find(name) != nodeMap.end());
	}

	struct GreaterPathLength
	{
		bool operator()(const std::vector<Arc*>& lhs, const std::vector<Arc*>& rhs) const
		{
			return getPathCost(lhs) > getPathCost(rhs);
		}
	};
	std::vector<Arc*> findShortestPath(std::string start, std::string finish)
	{
		return findShortestPath(nodeMap[start], nodeMap[finish]);
	}
	std::vector<Arc*> findShortestPath(Node* start, Node* finish);
	static int getPathCost(const std::vector<Arc*>& path);


private:
	void visitUsingDFS(Node* node);
	void visitUsingBFS();

private:
	std::map<std::string, Node*> nodeMap;
	std::set<Node*> nodes;
	std::set<Arc*> arcs;
	std::set<Node*> visited;
	std::queue<Node*> tovisit;
};