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
	string GetNodeNameAt(size_t idx);

private:
	string GetGraphOptionString();
	string GetGraphTraversalString(GraphTraversal graphTraversal);

protected:
	GraphOption CurrentGraphOption() { return m_graphOption; }
	size_t GetNodeCount() { return m_graphNodeList.size(); }

	GraphNode GetFirstNode()
	{
		size_t nodeCount{ GetNodeCount() };
		if (nodeCount > 0)
		{
			for (size_t i = 0; i < nodeCount; i++)
			{
				if (m_graphNodeList[i].name != "")
				{
					return m_graphNodeList[i];
				}
			}
			return m_graphNodeList[0];
		}
		return m_emptyNode;
	}
	GraphNode GetLastNode()
	{ 
		size_t nodeCount{ GetNodeCount() };
		if (nodeCount > 0)
		{
			for (size_t i = nodeCount - 1; ; i--)
			{
				if (m_graphNodeList[i].name != "")
				{
					return m_graphNodeList[i];
				}

				if (i == 0)
				{
					return m_graphNodeList[GetNodeCount() - 1];
				}
			}
		}
		return m_emptyNode;
	}

private:
	GraphOption m_graphOption;
	vector<GraphNode> m_graphNodeList;

	GraphNode m_emptyNode{ "EMPTY" };
};