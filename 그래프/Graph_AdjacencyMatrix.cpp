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
		std::fill_n(m_matrix[i], size, None);
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
/// 그래프에 에지를 추가한다.
/// </summary>
/// <param name="from">시작 노드</param>
/// <param name="to">끝 노드</param>
/// <param name="weight">가중치(기본: 1)</param>
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
		m_matrix[idx][i] = None;
		m_matrix[i][idx] = None;
	}

	return true;
}

/// <summary>
/// 그래프에서 에지를 제거한다.
/// </summary>
/// <param name="from">시작 노드</param>
/// <param name="to">끝 노드</param>
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
/// 그래프를 초기화한다.
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
/// 해시 테이블의 현 상태를 출력한다.
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

/// <summary>
/// BFS로 그래프를 출력한다.
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
/// DFS로 그래프를 출력한다.
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