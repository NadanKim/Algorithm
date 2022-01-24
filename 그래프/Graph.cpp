#include "Graph.h"

#pragma region Public Functions
/// <summary>
/// �׷����� ��带 �߰��Ѵ�.
/// </summary>
/// <param name="name">�߰��� ��� �̸�</param>
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
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
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
/// �־��� �̸��� ��尡 �����ϴ��� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="name">�˻��� ����� �̸�</param>
/// <returns>���� ����</returns>
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
/// �׷����� �־��� �̸��� ���� ����� �ε����� �˻��Ͽ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="name">�˻��� ����� �̸�</param>
/// <returns>����� �ε���(������ -1)</returns>
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
/// ���� �׷��� �ɼ��� string ���� ��ȯ�Ѵ�.
/// </summary>
/// <returns>�׷��� �ɼ� string</returns>
std::string Graph::GetGraphOptionString()
{
	if (m_graphOption == GraphOption::Undirected)
	{
		return "Undirected";
	}
	return "Directed";
}

/// <summary>
/// �־��� �׷��� ��ȸ �ɼ��� string ���� ��ȯ�Ѵ�.
/// </summary>
/// <param name="graphTraversal">�׷��� ��ȸ ���</param>
/// <returns>�׷��� ��ȸ ��� string</returns>
string Graph::GetGraphTraversalString(GraphTraversal graphTraversal)
{
	if (graphTraversal == GraphTraversal::BFS)
	{
		return "BFS";
	}
	return "DFS";
}
#pragma endregion