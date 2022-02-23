#pragma once
#include "Graph.h"
#include <algorithm>
#include <queue>
#include <stack>

using std::queue;
using std::stack;

/// <summary>
/// 그래프의 구성 요소 테스트를 위한 베이스 클래스
/// </summary>
class Graph_AdjacencyList : public Graph
{
public:
	Graph_AdjacencyList(GraphOption graphOption = GraphOption::Undirected, size_t size = 10);

	virtual bool AddNode(string name);
	virtual void AddEdge(string from, string to, int weight = 1);
	virtual bool RemoveNode(string name);
	virtual void RemoveEdge(string from, string to);
	virtual void Clear();

	virtual void PrintGraph(GraphTraversal graphTraversal = GraphTraversal::BFS, string graphName = "Graph_AdjacencyMatrix");

private:
	void Resize();

	void PrintGraphBFS(size_t nodeIdx);
	void PrintGraphDFS(size_t nodeIdx);

protected:
	size_t GetNodeCapacity() { return m_capacity; }

private:
	int** m_matrix;
	size_t m_capacity;

	static const int None{ INT_MIN };
};