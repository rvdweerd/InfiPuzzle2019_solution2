#include <set>
#include <vector>
#include <map>
#include <iostream>
#include "SimpleGraph.h"

void Infi1()
{	// aoc.infi.nl 2019, deel 1
	// input
	std::vector<std::pair<int, int>> flats = { {3,3},{5,5},{9,6},{13,7},{15,9},{16,10},{18,9},{21,10},{23,3},{25,4},{28,5},{29,7},{30,8},{34,7},{37,9},{39,7},{41,8},{42,10},{43,9},{47,10},{48,10},{50,6},{52,7},{53,10},{56,6},{57,4},{58,6},{59,2},{62,2} };
	std::vector < std::pair<int, int>> sprongen = { {1,2},{3,1},{0,0},{1,2},{0,1},{1,0},{2,1},{1,0},{1,1},{2,1},{0,2},{0,1},{3,0},{2,2},{1,0},{1,1},{0,2},{0,0},{3,1},{0,0},{1,0},{1,1},{0,3},{2,0},{0,0},{0,2},{0,0},{2,0}, {1,2},{3,1},{0,0},{1,2},{0,1},{1,0},{2,1},{1,0},{1,1},{2,1},{0,2},{0,1},{3,0},{2,2},{1,0},{1,1},{0,2},{0,0},{3,1},{0,0},{1,0},{1,1},{0,3},{2,0},{0,0},{0,2},{0,0},{2,0} };

	// Maak map van alle hoogtes van de flats: KEY= positie x van flat, VALUE = hoogte
	std::map<int, int> hoogtes;
	for (auto p : flats) hoogtes[p.first] = p.second;

	// Initialiseer
	std::pair<int, int> pos = flats[0];
	int nSprongen = 0;

	// Main loop: voer sprong uit tot [vallen] of tot [successvol landen na laatste sprong]
	for (int i = 0; i < sprongen.size(); i++)
	{
		std::cout << "Positie: (" << pos.first << "," << pos.second << "). ";
		pos.first += sprongen[i].first + 1;
		pos.second += sprongen[i].second;
		auto landingsHoogte = hoogtes.find(pos.first);
		if (landingsHoogte != hoogtes.end() && landingsHoogte->second <= pos.second)
		{
			pos.second = landingsHoogte->second;
			nSprongen++;
			std::cout << "Succesvolle " << nSprongen << "e sprong naar (" << pos.first << "," << pos.second << ")" << std::endl;
		}
		else break;
	}

	// Resultaat tonen
	if (nSprongen == sprongen.size()) std::cout << "success, nSprongen = " << nSprongen; else std::cout << "Fail na sprong: " << nSprongen << ", de kerstman valt dus bij sprong " << nSprongen + 1;
	std::cout << "\nDruk [Enter] om door te gaan..";
	std::cin.get();
}

bool kanVooruitLanden(std::pair<int, int> startpos, std::pair<int, int> sprong, const std::map<int, int>& hoogtes)
{
	std::pair<int, int> endposition = { startpos.first + sprong.first + 1, startpos.second += sprong.second };
	auto landingsHoogte = hoogtes.find( endposition.first);
	if (landingsHoogte != hoogtes.end() && landingsHoogte->second <= endposition.second)
	{
		return true;
	}
	else return false;
}
std::string SerializeNodePosition(std::pair<int,int> pos)
{
	std::string posName;
	posName.append("(");
	posName.append(std::to_string(pos.first));
	posName.append(",");
	posName.append(std::to_string(pos.second));
	posName.append(")");
	return posName;
}
void VulGraph(	SimpleGraph& graph,
				std::queue<std::pair<int, int>>& positionsQueue,
				const std::vector < std::pair<int, int>>& basisSprongen, 
				const std::map<int, int>& hoogtes)
{
	while (!positionsQueue.empty())
	{
		std::pair<int, int> currentPos = positionsQueue.front(); positionsQueue.pop();
		std::string currentNodeName = SerializeNodePosition(currentPos);
		{
			// Loop alle alle mogelijke landingsposities vanuit de huidige positie  af en:
			for (auto s : basisSprongen)
			{
				if (kanVooruitLanden(currentPos, s, hoogtes))
				{
					// creeer nieuwe landingspositie
					std::pair<int, int> landingPos;
					landingPos.first = currentPos.first + s.first + 1;
					landingPos.second = hoogtes.find(landingPos.first)->second;
					int energy = s.first + s.second;
					// als de landingspositie nog niet in de graph zit, voeg deze toe aan de queue
					std::string landingNodeName = SerializeNodePosition(landingPos);
					if (!graph.NodeExists(landingNodeName))
					{
						positionsQueue.push(landingPos);
					}
					// voeg deze arc to aan de graph
					graph.AddOneWayConnection(SerializeNodePosition(currentPos), SerializeNodePosition(landingPos), energy);
					
					
				}
			}
		}
	}
}

void Infi2()
{
	// aoc.infi.nl 2019, deel 2
	// Input (kan json load doen, maar dit was even sneller en is triviaal)
	std::vector<std::pair<int, int>> flats = { {3,3},{5,5},{9,6},{13,7},{15,9},{16,10},{18,9},{21,10},{23,3},{25,4},{28,5},{29,7},{30,8},{34,7},{37,9},{39,7},{41,8},{42,10},{43,9},{47,10},{48,10},{50,6},{52,7},{53,10},{56,6},{57,4},{58,6},{59,2},{62,2} };
	std::vector < std::pair<int, int>> basisSprongen = { {0,0},{0,1},{0,2 },{0,3},{0,4},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{3,0},{3,1},{4,0} };

	// Maak map van alle hoogtes van de flats: KEY= positie x van flat, VALUE = hoogte
	std::map<int, int> hoogtes;
	for (auto p : flats) hoogtes[p.first] = p.second;
	
	// Maak een graph die geschikt voor Dijkstra (arcs zijn de sprongen met energie als cost). SimpleGraph is eigen implementatie van graph class & dijkstra
	SimpleGraph graph;
	// Maak een hulp-queue om chart te maken en vul deze met de startpositie
	std::queue<std::pair<int, int>> positionsQueue; 
	positionsQueue.push(flats[0]);
	// Vul de graph met een BFS routine
	VulGraph(graph, positionsQueue, basisSprongen, hoogtes);
	graph.PrintAdjacencyList();

	// Voer het Dijktra shortes path algoritme uit
	std::string startNode = SerializeNodePosition(flats[0]);
	std::string endNode = SerializeNodePosition(flats.back());
	std::vector<SimpleGraph::Arc*> shortestPath = graph.findShortestPath(startNode,endNode);
	
	// Presenteer resultaten
	std::cout << "\nShortest path with Dijkstra: " << SimpleGraph::getPathCost(shortestPath)<<std::endl;
	std::cout << "\nOptimale route:\n";
	std::cout << "\n== START ===\n";
	for (auto a : shortestPath)
	{
		std::cout << a->start->name << " -cost[" << a->cost << "]->" << a->finish->name << std::endl;
	}
	std::cout << "== END ===\n";
	std::cout << "\nDruk [Enter] om te sluiten..";
	std::cin.get();
}

int main()
{
	// Deze oplossing maakt gebruik Dijkstra's shortest path algorithm, mooi om onze Nederlandse trots toe te passen. 
	// 
	// Naast de C++ Standard Library (STL) includes voor standaard container classes heb ik eigen "SimpleGraph" class 
	// gebouwd en included.
	//
	// Basisgedachte: Vertaal de sprongen in een Directed Graph:
	// > iedere positie is een Vertex (/Node)
	// > iedere mogelijke sprong is een Edge (/Arc) naar een nieuwe positie
	// > de kosten van iedere sprongen is een dataveld van de Edge
	//
	// Als de graph eenmaal goed geconstrueerd is, is het eenvoudig om Dijkstra toe te passen.
	// groeten! Rogier

	Infi1(); // deel 1 van de puzzel
	Infi2(); // deel 2
	return 0;
}