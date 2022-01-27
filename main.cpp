#include "Common.h"
#include "그래프/Graph_AdjacencyMatrix.h"

int main()
{
	Graph_AdjacencyMatrix graph;

	graph.AddNode("First");
	graph.AddNode("Second");
	graph.AddNode("Third");
	graph.AddNode("Etc");

	graph.AddEdge("First", "Second");
	graph.AddEdge("Second", "Third");
	graph.AddEdge("Etc", "First");
	graph.AddEdge("Etc", "Third");

	graph.PrintGraph();
}