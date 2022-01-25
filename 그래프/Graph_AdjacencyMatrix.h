#pragma once
#include "Graph.h"

/// <summary>
/// �׷����� ���� ��� �׽�Ʈ�� ���� ���̽� Ŭ����
/// </summary>
class Graph_AdjacencyMatrix : public Graph
{
public:
	Graph_AdjacencyMatrix(GraphOption graphOption = GraphOption::Undirected) : Graph(graphOption) {};

	virtual void AddNode(string name);
	virtual void AddEdge(string from, string to, int weight = 1);
	virtual void RemoveNode(string name);
	virtual void RemoveEdge(string from, string to);
	virtual void Clear();

	virtual void PrintGraph(GraphTraversal graphTraversal = GraphTraversal::BFS, string graphName = "Graph");
};