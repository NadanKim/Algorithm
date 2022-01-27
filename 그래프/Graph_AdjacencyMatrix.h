#pragma once
#include "Graph.h"
#include <algorithm>

/// <summary>
/// 그래프의 구성 요소 테스트를 위한 베이스 클래스
/// </summary>
class Graph_AdjacencyMatrix : public Graph
{
public:
	Graph_AdjacencyMatrix(GraphOption graphOption = GraphOption::Undirected, size_t size = 10);

	virtual bool AddNode(string name);
	virtual void AddEdge(string from, string to, int weight = 1);
	virtual bool RemoveNode(string name);
	virtual void RemoveEdge(string from, string to);
	virtual void Clear();

	virtual void PrintGraph(GraphTraversal graphTraversal = GraphTraversal::BFS, string graphName = "Graph_AdjacencyMatrix");

private:
	void Resize();

protected:
	size_t GetNodeCapacity() { return m_capacity; }

private:
	int** m_matrix;
	size_t m_capacity;
};