#include "skeleton.h"

/* Graph implementations */

bool Graph::RemoveEdge(Vertex *from, Edge *from_to) {
    // this func is totally un-useful.

    return RemoveEdge(from, from_to->destination);
}

bool Graph::RemoveEdge(Vertex *from, Vertex *to) {
    Edge *preEdge = from->firstEdge;

    Edge *eDel;

    if (preEdge) {
        if (preEdge->destination->data == to->data) {
            from->outDegree--;
            to->inDegree--;
            from->firstEdge = preEdge->nextEdge;
            delete preEdge;
            preEdge = 0;
            return true;
        } else {
            while ((eDel = preEdge->nextEdge)) {
                if (eDel->destination->data == to->data) {
                    from->outDegree--;
                    to->inDegree--;
                    preEdge->nextEdge = eDel->nextEdge;
                    delete eDel, eDel = 0;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Graph::RemoveEdge(int fromData, int toData) {
    Vertex *from = GetVertex(fromData);
    Vertex *to   = GetVertex(toData);

    return from && to && RemoveEdge(from, to);
}

bool Graph::RemoveVertex(Vertex *vDel) {
    Vertex *preV         = gHead;
    bool    existInGraph = false;

    if (preV) {
        // remove edges connected with this vertex, and detact this vertex from
        // the graph
        // Note: data of vDel is not deallocated.
        if (preV->data == vDel->data) {
            preV         = gHead = gHead->nextVertex;
            existInGraph = true;
        }

        while (preV) {
            RemoveEdge(preV, vDel);

            if (preV->nextVertex && (preV->nextVertex->data == vDel->data)) {
                preV->nextVertex = preV->nextVertex->nextVertex;
                existInGraph     = true;
            }
            preV = preV->nextVertex;
        }
        Edge *eDel;
        Edge *eCur = vDel->firstEdge;

        while ((eDel = eCur)) {
            eCur              = eCur->nextEdge;
            delete eDel, eDel = 0;
        }
    }
    return existInGraph;
}

bool Graph::RemoveVertex(int reData) {
    Vertex *vDel = GetVertex(reData);

    return vDel && RemoveVertex(vDel);
}

void e6() {
    Graph *gph = graphReader("input/E6.txt");

    std::cout << "Origin graph:" << '\n';
    gph->Print();
    std::cout << "Enter vertex to delete, type -1 to stop:" << '\n';
    int vertexData;

    while ((vertexData = getInt()) != -1) gph->RemoveVertex(vertexData);

    std::cout << "Final graph:" << '\n';
    gph->Print();
}

void avlToGraph(Node *root, Graph *graph) {
    if (root->left) {
        graph->InsertEdge(root->data, root->left->data);
        avlToGraph(root->left, graph);
    }

    if (root->right) {
        graph->InsertEdge(root->data, root->right->data);
        avlToGraph(root->right, graph);
    }
}

void e9() {
    AVLTree *avl = avlReader("input/E9.txt");

    avl->PrintAVL();

    Graph *graph = new Graph();

    if (avl->root) avlToGraph(avl->root, graph);

    graph->Print();

    delete avl;
    delete graph;
}
