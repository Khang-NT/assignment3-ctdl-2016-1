#include "skeleton.h"
#include "../InputReader.h"
#include "../Graph.h"

/**
 * Implementation of Graph::Print();
 */
void Graph::Print() {
  Vertex* vertex = this->gHead;
  Edge* edge;
  while (vertex) {
    edge = vertex->firstEdge;
    std::cout << vertex->data;
    while (edge) {
      std::cout << " -> " << edge->destination->data;
      edge = edge->nextEdge;
    }
    std::cout << " -> NULL\n|\n";
    vertex = vertex->nextVertex;
  }
  std::cout << "NULL\n";
}

/**
 * Helper func: Parse graph from file, using {@link ReadArrayInputOfGraph}.
 * @param fileName The relative path to file contain graph data.
 */
Graph* graphReader(string fileName) {
  int* vertexDataArr;
  int vertexCount;
  int** edgeDataArr;
  int edgeCount;
  ReadArrayInputOfGraph(fileName, vertexDataArr, vertexCount, edgeDataArr, edgeCount);
  Graph* graph = new Graph();
  for (size_t i = 0; i < vertexCount; i++) {
    graph->InsertVertex(vertexDataArr[i]);
  }
  for (size_t i = 0; i < edgeCount; i++) {
    graph->InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
    delete[] edgeDataArr[i];
  }
  // collect garbage
  delete[] vertexDataArr;
  delete[] edgeDataArr;

  return graph;
}

/**
 * Implementation of func e5() in skeleton.h
 */
void e5() {
  Graph* graph = graphReader("input/E5.txt");
  graph->Print();
  // collect garbage
  delete graph;
}

/**
 * Implementation of func e14() in skeleton.h
 */
void e14() {
  Graph* graph = graphReader("input/E14.txt");
  graph->Print();
}
