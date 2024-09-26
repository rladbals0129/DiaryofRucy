#include "Stdafx.h"
#include "Kruskal.h"

//   0   1   2   3   4
//   5   6   7   8   9
//   10  11  12  13  14
//   15  16  17  18  19
//
// 노드 20개
// 간선 31개
// 선택되는 간선의 개수는 19개
// 거리가 짧은 순서대로 포함시킨다 -> vector에  넣기
// 사이클을 만들지 않는다. -> 사이클이 생기는 간선은 넣지 않는다.
//
// 난수로 랜덤한 수를 16개를 뽑는다.
// 랜덤으로 뽑힌 랜덤을 노드로 각각의 경로 세로 10, 가로 20 를 가중치로 벡터에 저장한다.
// 알고리즘을 돌려 사이클이 돌지 않는 도로를 생성한다.
// 맨 시작 부분과, 끝 부분, 끝의 전부분에 고정된 맵이미지를 출력하게끔하고
// 랜덤으로 이벤트 및 보상 방을 설정하여 맵 이미지를 생성한다.
int Kruskal::findParent(vector<int>& parent, int node)
{
	if (parent[node] == node)
	{
		if (parent[node] == node)
		{
			return node;
		}
	}

	return parent[node] = findParent(parent, parent[node]);
}

vector<Edge> Kruskal::kruskal(vector<Edge>& edges, int numNodes)
{
	vector<Edge> minimumSpanningTree;
	vector<int> parent(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		parent[i] = i;
	}

	for (int i = 0; i < edges.size(); i++)
	{
		int rootFromX = findParent(parent, edges[i].fromX);
		int rootFromY = findParent(parent, edges[i].fromY);
		int rootToX = findParent(parent, edges[i].toX);
		int rootToY = findParent(parent, edges[i].toY);

		if (rootFromX != rootToX)
		{
			if(rootFromY != rootToY)
			minimumSpanningTree.push_back(edges[i]);
			parent[rootFromX] = rootToX;
			parent[rootFromY] = rootToY;
		}
	}

	return minimumSpanningTree;
}

int Kruskal::generateMap(int nodeNumber)
{
	int numNodes = nodeNumber;
	vector<Edge> edges;

	edges.push_back(Edge(0, 1, 0, 2, 10));
	edges.push_back(Edge(0, 2, 0, 3, 10));
	edges.push_back(Edge(0, 2, 1, 2, 10));
	edges.push_back(Edge(1, 2, 1, 3, 10));
	edges.push_back(Edge(1, 2, 2, 2, 10));
	edges.push_back(Edge(2, 2, 3, 2, 10));
	edges.push_back(Edge(3, 2, 3, 3, 10));
	edges.push_back(Edge(3, 3, 3, 4, 10));

	vector<Edge> minimumSpanningTree = kruskal(edges, numNodes);

	return 0;
}
