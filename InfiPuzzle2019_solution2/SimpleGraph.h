#pragma once
#include <string>
#include <set>
#include <map>
#include <queue>

class SimpleGraph
{
public:
	struct Arc;
	struct Node
	{
		// Basisvelden t.b.v. graph functionaliteit
		Node(std::string n)
			:
			name(n)
		{
		}
		std::string name;
		std::set<Arc*> arcs;
		// Voeg hier aanvullende datavelden per node toe
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
	SimpleGraph() = default;
	~SimpleGraph() = default;
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