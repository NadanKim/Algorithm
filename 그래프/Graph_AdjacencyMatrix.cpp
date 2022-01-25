#include "Graph_AdjacencyMatrix.h"

#pragma region Public Functions
/// <summary>
/// �׷����� ��带 �߰��Ѵ�.
/// </summary>
/// <param name="name">�߰��� ��� �̸�</param>
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
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
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