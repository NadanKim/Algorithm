#pragma once
#include "../Common.h"
#include <cmath>
#include <string>
#include <vector>

using std::string;
using std::vector;

/// <summary>
/// �׷����� ���� ó�� ���
/// </summary>
enum class GraphOption
{
	Undirected,
	Directed,
};

/// <summary>
/// �׷����� ��ȸ ���
/// </summary>
enum class GraphTraversal
{
	BFS,
	DFS,
};

/// <summary>
/// �׷��� ��带 ��Ÿ���� ���� ����ü
/// </summary>
struct GraphNode
{
	GraphNode(string name) : name(name) {}

	string name;
};

/// <summary>
/// �׷����� ���� ��� �׽�Ʈ�� ���� ���̽� Ŭ����
/// </summary>
class Graph
{
public:
	Graph(GraphOption graphOption = GraphOption::Undirected) : m_graphOption(graphOption) {};

	virtual bool AddNode(string name);
	virtual void AddEdge(string from, string to, int weight = 1) = 0;
	virtual bool RemoveNode(string name);
	virtual void RemoveEdge(string from, string to) = 0;
	virtual void Clear();

	virtual void PrintGraph(GraphTraversal graphTraversal = GraphTraversal::BFS, string graphName = "Graph");

	bool Exists(string name);
	size_t GetNodeIndex(string name);

private:
	string GetGraphOptionString();
	string GetGraphTraversalString(GraphTraversal graphTraversal);

protected:
	GraphOption CurrentGraphOption() { return m_graphOption; }
	size_t GetNodeCount() { return m_graphNodeList.size(); }

private:
	GraphOption m_graphOption;
	vector<GraphNode> m_graphNodeList;
};