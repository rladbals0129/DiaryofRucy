#pragma once

struct Edge
{
	int fromX, fromY, toX, toY, weight;

	Edge(int fromX, int fromY, int toX, int toY, int weight) : fromX(fromX), fromY(fromY), toX(toX), toY(toY), weight(weight) {}

	bool operator<(const Edge& other) const
	{
		return weight < other.weight;
	}
};

class Kruskal
{
public:

	int findParent(vector<int>& parent, int node);
	vector<Edge> kruskal(vector<Edge>& edges, int numNodes);
	int generateMap(int nodeNumber);

	Kruskal() {}
	~Kruskal() {}
};

