#include "skeleton.h"
#include "../InputReader.h"
#include "../Graph.h"


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

void e5() {
  int* vertexDataArr;
  int vertexCount;
  int** edgeDataArr;
  int edgeCount;
  ReadArrayInputOfGraph("input/E5.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);
  Graph graph;
  for (size_t i = 0; i < vertexCount; i++) {
    graph.InsertVertex(vertexDataArr[i]);
  }
  for (size_t i = 0; i < edgeCount; i++) {
    graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
    delete[] edgeDataArr[i];
  }
  graph.Print();
  // collect garbage
  delete[] vertexDataArr;
  delete[] edgeDataArr;
}
