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

bool isBetween(int min, int max, int v) {
    return v > min && v < max;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int abs(int v) {
    return v < 0 ? -v : v;
}

/**
 * A class helper to create a tree quickly, include ability to get height of a
 * node,
 * and convert to {@link Node} instance (ommit {@link Node$balance} field).
 * <br> Height of a node is evaluated by max height of its children
 * and one for the height of itself.
 */
class EasyNode {
private:

    void updateHeight() {
        height = max(right ? right->height : 0,
                     left ? left->height : 0) + 1;
    }

public:

    int data;

    EasyNode(int data) : data(data) {
        left   = right = 0;
        height = 1;
    }

    void setLeft(EasyNode *left) {
        this->left = left;
        updateHeight();
    }

    void setRight(EasyNode *right) {
        this->right = right;
        updateHeight();
    }

    EasyNode* getLeft() {
        return left;
    }

    EasyNode* getRight() {
        return right;
    }

    int getHeight() {
        return height;
    }

    Node* asTreeNode() {
        Node *node = new Node(data);

        if (left) node->left = left->asTreeNode();

        if (right) node->right = right->asTreeNode();
        return node;
    }

    virtual ~EasyNode() {
        delete left, left   = 0;
        delete right, right = 0;
    }

protected:

    EasyNode *left;
    EasyNode *right;
    int height;
};

/**
 * Verify if a vertex can convert to a node AVL tree.
 */
bool verifyVertexIsAvlNode(Vertex *vertex, Vertex *& lVertex, Vertex *& rVertex) {
    // num of child must not be larger than 2
    if (vertex->firstEdge && vertex->firstEdge->nextEdge &&
        vertex->firstEdge->nextEdge->nextEdge) return false;

    // has no children,
    if (!vertex->firstEdge) {
        lVertex = rVertex = NULL;
        return true;
    }

    // has only one child
    if (vertex->firstEdge && !vertex->firstEdge->nextEdge) {
        if (vertex->data > vertex->firstEdge->destination->data) {
            lVertex = vertex->firstEdge->destination;
            rVertex = 0;
        } else {
            rVertex = vertex->firstEdge->destination;
            lVertex = 0;
        }
        return true;
    }

    // has two childs
    // check if data is valid
    if (isBetween(vertex->firstEdge->destination->data,
                  vertex->firstEdge->nextEdge->destination->data,
                  vertex->data)) {
        lVertex = vertex->firstEdge->destination;
        rVertex = vertex->firstEdge->nextEdge->destination;
        return true;
    }

    if (isBetween(vertex->firstEdge->nextEdge->destination->data,
                  vertex->firstEdge->destination->data,
                  vertex->data)) {
        lVertex = vertex->firstEdge->nextEdge->destination;
        rVertex = vertex->firstEdge->destination;
        return true;
    }

    return false; // invalid data
}

EasyNode* graphToAvl(Vertex *vertex) {
    EasyNode *root = 0;
    Vertex   *leftVertex = 0, *rightVertex = 0;

    if (verifyVertexIsAvlNode(vertex, leftVertex, rightVertex)) {
        EasyNode *left  = 0;
        EasyNode *right = 0;
        int leftHeight  = 0;
        int rightHeight = 0;

        if (leftVertex) {
            left = graphToAvl(leftVertex);

            if (!left) return NULL;

            leftHeight = left->getHeight();
        }

        if (rightVertex) {
            right = graphToAvl(rightVertex);

            if (!right) {
                delete left, left = 0;
                return NULL;
            }

            rightHeight = right->getHeight();
        }

        if (abs(leftHeight - rightHeight) > 1) {
            delete left, left   = 0;
            delete right, right = 0;
            return NULL;
        } else {
            root = new EasyNode(vertex->data);
            root->setLeft(left);
            root->setRight(right);
        }
    }
    return root;
}

Graph* readGraphFromMatrix(string filename, bool printMatrix) {
    int  **matrix;
    int    size;
    Graph *graph = new Graph;

    ReadAdjacencyMat(filename, matrix, size);

    for (size_t i = 0; i < size; i++) {
        if (!graph->VertexExist(i + 1)) graph->InsertVertex(i + 1);

        for (size_t j = 0; j < size; j++) {
            if (printMatrix) std::cout << matrix[i][j] << ' ';

            if (matrix[i][j]) graph->InsertEdge(i + 1, j + 1);
        }
        delete matrix[i];
        std::cout << "\n";
    }
    delete matrix;
    matrix = 0;
    return graph;
}

void e17() {
    Graph *graph = readGraphFromMatrix("input/E17b.txt");

    graph->Print();

    // if graph is an AVL tree, it will have one and only one vertex with
    // inDegree is zero, and this vertex should be "root" of the tree.

    Vertex *rootVertex = 0;
    Vertex *temp       = graph->gHead;

    while (temp) {
        if (temp->inDegree == 0) {
            if (rootVertex) { // invalid
                rootVertex = 0;
                break;
            } else {
                rootVertex = temp;
            }
        }
        temp = temp->nextVertex;
    }

    if (rootVertex) {
        EasyNode *easyNode = graphToAvl(rootVertex);

        if (easyNode) {
            AVLTree *avlTree = new AVLTree(easyNode->asTreeNode());
            std::cout << "Given graph (from matrix) is an AVLTree:" << '\n';
            avlTree->PrintAVL();
            delete avlTree, avlTree   = 0;
            delete easyNode, easyNode = 0;
            delete graph, graph = 0;
            return;
        }
    }
    std::cout << "Given graph (from matrix) is NOT an AVLTree." << '\n';

    delete graph, graph = 0;
}
