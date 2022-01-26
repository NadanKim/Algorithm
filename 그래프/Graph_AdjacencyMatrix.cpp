#include "Graph_AdjacencyMatrix.h"

#pragma region Public Functions
/// <summary>
/// 그래프 옵션을 결정하고 그래프의 최초 크기를 설정한다.
/// </summary>
/// <param name="graphOption">그래프 옵션</param>
/// <param name="size">그래프 크기</param>
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
/// 그래프에 노드를 추가한다.
/// </summary>
/// <param name="name">추가할 노드 이름</param>
/// <returns>성공 여부</returns>
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
/// 그래프에서 노드를 제거한다.
/// </summary>
/// <param name="name">제거할 노드 이름</param>
/// <returns>성공 여부</returns>
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
/// 해시 테이블의 현 상태를 출력한다.
/// </summary>
void Graph_AdjacencyMatrix::PrintGraph(GraphTraversal graphTraversal, string graphName)
{
	Graph::PrintGraph(graphTraversal, graphName);
}
#pragma endregion

#pragma region Private Functions
/// <summary>
/// 그래프의 크기를 두배로 늘린다.
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