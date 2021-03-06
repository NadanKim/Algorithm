#include "Graph.h"

#pragma region Public Functions
/// <summary>
/// 그래프에 노드를 추가한다.
/// </summary>
/// <param name="name">추가할 노드 이름</param>
/// <returns>성공 여부</returns>
bool Graph::AddNode(string name)
{
	if (Exists(name))
	{
		return false;
	}

	bool isAdded{ false };
	for (size_t total = m_graphNodeList.size(), i = 0; i < total; i++)
	{
		if (m_graphNodeList[i].name == "")
		{
			m_graphNodeList[i].name = name;
			isAdded = true;
			break;
		}
	}

	if (!isAdded)
	{
		m_graphNodeList.push_back(GraphNode(name));
	}

	return true;
}

/// <summary>
/// 그래프에서 노드를 제거한다.
/// </summary>
/// <param name="name">제거할 노드 이름</param>
/// <returns>성공 여부</returns>
bool Graph::RemoveNode(string name)
{
	for (size_t total = m_graphNodeList.size(), i = 0; i < total; i++)
	{
		if (m_graphNodeList[i].name == name)
		{
			m_graphNodeList[i].name = "";
			return true;
		}
	}

	return false;
}

/// <summary>
/// 그래프를 초기화한다.
/// </summary>
void Graph::Clear()
{
	for (size_t total = m_graphNodeList.size(), i = 0; i < total; i++)
	{
		m_graphNodeList[i].name = "";
	}
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
	std::cout << "\n------------------------------------------\n";
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
size_t Graph::GetNodeIndex(string name)
{
	for (size_t total = m_graphNodeList.size(), i = 0; i < total; i++)
	{
		if (m_graphNodeList[i].name == name)
		{
			return i;
		}
	}
	return -1;
}

/// <summary>
/// 인덱스 값에 해당하는 노드 이름을 반환한다.
/// </summary>
/// <param name="idx">이름을 가져올 노드 인덱스</param>
/// <returns>노드 이름</returns>
string Graph::GetNodeNameAt(size_t idx)
{
	if (idx < GetNodeCount())
	{
		return m_graphNodeList[idx].name;
	}
	return "None";
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