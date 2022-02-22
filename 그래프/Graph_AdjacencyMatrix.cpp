#include "Graph_AdjacencyMatrix.h"

#pragma region Public Functions
/// <summary>
/// �׷��� �ɼ��� �����ϰ� �׷����� ���� ũ�⸦ �����Ѵ�.
/// </summary>
/// <param name="graphOption">�׷��� �ɼ�</param>
/// <param name="size">�׷��� ũ��</param>
Graph_AdjacencyMatrix::Graph_AdjacencyMatrix(GraphOption graphOption, size_t size)
	: Graph(graphOption)
{
	m_capacity = size;
	
	m_matrix = new int* [size];
	for (size_t i = 0; i < size; i++)
	{
		m_matrix[i] = new int[size];
		std::fill_n(m_matrix[i], size, None);
	}
}

/// <summary>
/// �׷����� ��带 �߰��Ѵ�.
/// </summary>
/// <param name="name">�߰��� ��� �̸�</param>
/// <returns>���� ����</returns>
bool Graph_AdjacencyMatrix::AddNode(string name)
{
	if (!Graph::AddNode(name))
	{
		return false;
	}

	if (GetNodeCount() >= m_capacity)
	{
		Resize();
	}

	return true;
}

/// <summary>
/// �׷����� ������ �߰��Ѵ�.
/// </summary>
/// <param name="from">���� ���</param>
/// <param name="to">�� ���</param>
/// <param name="weight">����ġ(�⺻: 1)</param>
void Graph_AdjacencyMatrix::AddEdge(string from, string to, int weight)
{
	size_t fromIdx{ GetNodeIndex(from) }, toIdx{ GetNodeIndex(to) };

	if (fromIdx != -1 && toIdx != -1)
	{
		m_matrix[fromIdx][toIdx] = weight;

		if (CurrentGraphOption() == GraphOption::Undirected)
		{
			m_matrix[toIdx][fromIdx] = weight;
		}
	}
}

/// <summary>
/// �׷������� ��带 �����Ѵ�.
/// </summary>
/// <param name="name">������ ��� �̸�</param>
/// <returns>���� ����</returns>
bool Graph_AdjacencyMatrix::RemoveNode(string name)
{
	size_t idx{ GetNodeIndex(name) };

	if (!Graph::RemoveNode(name))
	{
		return false;
	}

	for (size_t i = 0; i < m_capacity; i++)
	{
		m_matrix[idx][i] = None;
		m_matrix[i][idx] = None;
	}

	return true;
}

/// <summary>
/// �׷������� ������ �����Ѵ�.
/// </summary>
/// <param name="from">���� ���</param>
/// <param name="to">�� ���</param>
void Graph_AdjacencyMatrix::RemoveEdge(string from, string to)
{
	size_t fromIdx{ GetNodeIndex(from) }, toIdx{ GetNodeIndex(to) };

	if (fromIdx != -1 && toIdx != -1)
	{
		m_matrix[fromIdx][toIdx] = None;

		if (CurrentGraphOption() == GraphOption::Undirected)
		{
			m_matrix[toIdx][fromIdx] = None;
		}
	}
}

/// <summary>
/// �׷����� �ʱ�ȭ�Ѵ�.
/// </summary>
void Graph_AdjacencyMatrix::Clear()
{
	Graph::Clear();

	for (size_t i = 0; i < m_capacity; i++)
	{
		std::fill_n(m_matrix[i], m_capacity, None);
	}
}

/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
/// </summary>
void Graph_AdjacencyMatrix::PrintGraph(GraphTraversal graphTraversal, string graphName)
{
	Graph::PrintGraph(graphTraversal, graphName);

	std::cout << "- Graph Edges\n";
	for (size_t i = 0; i < m_capacity; i++)
	{
		std::cout << GetNodeNameAt(i) << " : ";
		for (size_t j = 0; j < m_capacity; j++)
		{
			if (m_matrix[i][j] == None)
			{
				continue;
			}
			std::cout << GetNodeNameAt(j) << " - ";
		}
		std::cout << '\n';
	}
	std::cout << "------------------------------------------\n";

	std::cout << "- Graph Traversal from FIRST NODE\n";
	GraphNode node{ GetFirstNode() };
	size_t nodeIdx{ GetNodeIndex(node.name) };

	if (node.name == "EMPTY")
	{
		std::cout << "EMPTY\n";
	}
	else
	{
		bool* nodeChecker = new bool[m_capacity] {};
		if (graphTraversal == GraphTraversal::BFS)
		{
			PrintGraphBFS(nodeIdx);
		}
		else if (graphTraversal == GraphTraversal::DFS)
		{
			PrintGraphDFS(nodeIdx);
		}
		delete[] nodeChecker;
	}
	std::cout << "\n------------------------------------------\n";
}
#pragma endregion

#pragma region Private Functions
/// <summary>
/// �׷����� ũ�⸦ �ι�� �ø���.
/// </summary>
void Graph_AdjacencyMatrix::Resize()
{
	size_t tempCapacity{ m_capacity * 2 };
	int** tempMatrix{ new int* [tempCapacity] };
	for (size_t i = 0; i < tempCapacity; i++)
	{
		tempMatrix[i] = new int[tempCapacity];
		std::fill_n(tempMatrix[i], tempCapacity, 0);
	}

	for (size_t i = 0; i < m_capacity; i++)
	{
		std::copy_n(m_matrix[i], m_capacity, tempMatrix[i]);
		delete[] m_matrix[i];
	}
	delete[] m_matrix;

	m_capacity = tempCapacity;
	m_matrix = tempMatrix;
}

/// <summary>
/// BFS�� �׷����� ����Ѵ�.
/// </summary>
void Graph_AdjacencyMatrix::PrintGraphBFS(size_t nodeIdx)
{
	bool* nodeChecker = new bool[m_capacity] {};
	queue<size_t> q;
	q.push(nodeIdx);

	while (!q.empty())
	{
		size_t idx{ q.front() };
		q.pop();

		if (!nodeChecker[idx])
		{
			nodeChecker[idx] = true;

			std::cout << GetNodeNameAt(idx) << " - ";
			for (size_t i = 0; i < m_capacity; i++)
			{
				if (m_matrix[idx][i] != None)
				{
					q.push(i);
				}
			}
		}
	}

	delete[] nodeChecker;
}

/// <summary>
/// DFS�� �׷����� ����Ѵ�.
/// </summary>
void Graph_AdjacencyMatrix::PrintGraphDFS(size_t nodeIdx)
{
	bool* nodeChecker = new bool[m_capacity] {};
	stack<size_t> s;
	s.push(nodeIdx);

	while (!s.empty())
	{
		size_t idx{ s.top() };
		s.pop();

		if (!nodeChecker[idx])
		{
			nodeChecker[idx] = true;

			std::cout << GetNodeNameAt(idx) << " - ";
			for (size_t i = 0; i < m_capacity; i++)
			{
				if (m_matrix[idx][i] != None)
				{
					s.push(i);
				}
			}
		}
	}

	delete[] nodeChecker;
}
#pragma endregion