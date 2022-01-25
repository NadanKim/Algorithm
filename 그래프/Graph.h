#pragma once
#include "../Common.h"
#include <cmath>
#include <string>
#include <vector>

using std::string;
using std::vector;

/// <summary>
/// 그래프의 간선 처리 방식
/// </summary>
enum class GraphOption
{
	Undirected,
	Directed,
};

/// <summary>
/// 그래프의 순회 방식
/// </summary>
enum class GraphTraversal
{
	BFS,
	DFS,
};

/// <summary>
/// 그래프 노드를 나타내기 위한 구조체
/// </summary>
struct GraphNode
{
	GraphNode(string name) : name(name) {}

	string name;
};

/// <summary>
/// 그래프의 구성 요소 테스트를 위한 베이스 클래스
/// </summary>
class Graph
{
public:
	Graph(GraphOption graphOption = GraphOption::Undirected) : m_graphOption(graphOption) {};

	virtual void AddNode(string name);
	virtual void AddEdge(string from, string to, int weight = 1) = 0;
	virtual void RemoveNode(string name);
	virtual void RemoveEdge(string from, string to) = 0;
	virtual void Clear() = 0;

	virtual void PrintGraph(GraphTraversal graphTraversal = GraphTraversal::BFS, string graphName = "Graph");

	bool Exists(string name);
	int GetNodeIndex(string name);

private:
	string GetGraphOptionString();
	string GetGraphTraversalString(GraphTraversal graphTraversal);

protected:
	GraphOption CurrentGraphOption() { return m_graphOption; }

private:
	GraphOption m_graphOption;
	vector<GraphNode> m_graphNodeList;
};