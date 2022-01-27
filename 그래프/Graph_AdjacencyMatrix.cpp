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
		std::fill_n(m_matrix[i], size, 0);
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
		m_matrix[idx][i] = 0;
		m_matrix[i][idx] = 0;
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
		m_matrix[fromIdx][toIdx] = 0;

		if (CurrentGraphOption() == GraphOption::Undirected)
		{
			m_matrix[toIdx][fromIdx] = 0;
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
		std::fill_n(m_matrix[i], m_capacity, 0);
	}
}

/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
/// </summary>
void Graph_AdjacencyMatrix::PrintGraph(GraphTraversal graphTraversal, string graphName)
{
	Graph::PrintGraph(graphTraversal, graphName);

	// GraphTraversal �� ���� �� ���� ���� �߰� �ʿ�
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
#pragma endregion