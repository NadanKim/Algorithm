#include "Graph_AdjacencyMatrix.h"

#pragma region Public Functions
/// <summary>
/// 그래프에 노드를 추가한다.
/// </summary>
/// <param name="name">추가할 노드 이름</param>
void Graph_AdjacencyMatrix::AddNode(string name)
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
void Graph_AdjacencyMatrix::PrintGraph(GraphTraversal graphTraversal, string graphName)
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
#pragma endregion