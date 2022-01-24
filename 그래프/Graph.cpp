#include "Graph.h"

#pragma region Public Functions
/// <summary>
/// 그래프에 노드를 추가한다.
/// </summary>
/// <param name="name">추가할 노드 이름</param>
void Graph::AddNode(string name)
{
	if (Exists(name))
	{
		return;
	}

	for (size_t total = m_graphNodeList.size(), i = 0; i < total; i++)
	{
		if (m_graphNodeList[i].name == "")
		{
			m_graphNodeList[i].name = name;
			return;
		}
	}

	m_graphNodeList.push_back(GraphNode(name));
}

/// <summary>
/// 해시 테이블의 현 상태를 출력한다.
/// </summary>
void Graph::PrintGraph(GraphTraversal graphTraversal, string graphName)
{
	std::cout << "------------------------------------------\n";
	std::cout << "- Class Name		: " << graphName << '\n';
	std::cout << "- GraphOption		: " << GetGraphOptionString() << '\n';
	std::cout << "- GraphTraversal	: " << GetGraphTraversalString(graphTraversal) << '\n';
	std::cout << "- Graph Nodes\n";
	if (m_graphNodeList.empty())
	{
		std::cout << "EMPTY\n";
	}
	else
	{
		for (size_t total = m_graphNodeList.size(), i = 0; i < total; i++)
		{
			std::cout << "Index[" << i << "] : ";

			if (m_graphNodeList[i].name == "")
			{
				std::cout << "None";
			}
			else
			{
				std::cout << m_graphNodeList[i].name;
			}

			if (i < total - 1)
			{
				std::cout << " - ";
			}
		}
	}
	std::cout << "------------------------------------------\n";
}

/// <summary>
/// 주어진 이름의 노드가 존재하는지 여부를 반환한다.
/// </summary>
/// <param name="name">검색할 노드의 이름</param>
/// <returns>존재 여부</returns>
bool Graph::Exists(string name)
{
	for (size_t total = m_graphNodeList.size(), i = 0; i < total; i++)
	{
		if (m_graphNodeList[i].name == name)
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// 그래프에 주어진 이름을 가진 노드의 인덱스를 검색하여 반환한다.
/// </summary>
/// <param name="name">검색할 노드의 이름</param>
/// <returns>노드의 인덱스(없으면 -1)</returns>
int Graph::GetNodeIndex(string name)
{
	for (size_t total = m_graphNodeList.size(), i = 0; i < total; i++)
	{
		if (m_graphNodeList[i].name == name)
		{
			return static_cast<int>(i);
		}
	}
	return -1;
}
#pragma endregion

#pragma region Private Functions
/// <summary>
/// 현재 그래프 옵션을 string 으로 반환한다.
/// </summary>
/// <returns>그래프 옵션 string</returns>
std::string Graph::GetGraphOptionString()
{
	if (m_graphOption == GraphOption::Undirected)
	{
		return "Undirected";
	}
	return "Directed";
}

/// <summary>
/// 주어진 그래프 순회 옵션을 string 으로 변환한다.
/// </summary>
/// <param name="graphTraversal">그래프 순회 방법</param>
/// <returns>그래프 순회 방법 string</returns>
string Graph::GetGraphTraversalString(GraphTraversal graphTraversal)
{
	if (graphTraversal == GraphTraversal::BFS)
	{
		return "BFS";
	}
	return "DFS";
}
#pragma endregion