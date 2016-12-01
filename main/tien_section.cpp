#include "skeleton.h"

template<class T>
struct StackItem {
    T          data;
    StackItem *next;
    StackItem(T data = NULL, StackItem<T> *next = NULL) {
        this->data = data;
        this->next = next;
    }
};

template<class T>
struct Stack {
    StackItem<T> *top;
    int           count;
    Stack() {
        top   = 0;
        count = 0;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void push(T data) {
        top = new StackItem<T>(data, top);
        count++;
    }

    T pop() {
        if (!isEmpty()) {
            StackItem<T> *item = top;
            T result           = item->data;
            top = top->next;
            count--;
            delete item;
            return result;
        }
        throw "Stack is empty";
    }
};

void e7() {
    AVLTree *avl = new AVLTree();
    int     *arr;
    int      count;

    ReadArrayInput("input/E7.txt", arr, count);
    avl->ArrayToAVL(arr, count);

    avl->PrintAVL();

    Stack<Node *> *stack1 = new Stack<Node *>();
    stack1->push(avl->root);

    Stack<Node *> *stack2 = new Stack<Node *>();

    int   tong     = 0;
    Node *nodeData = NULL;

    while (!stack1->isEmpty() || !stack2->isEmpty()) {
        if (!stack1->isEmpty()) {
            while (!stack1->isEmpty()) {
                nodeData = stack1->pop();
                tong     = tong + nodeData->data;

                if (nodeData->left) stack2->push(nodeData->left);

                if (nodeData->right) stack2->push(nodeData->right);
            }
            cout << tong << endl;
            tong = 0;
        }

        while (!stack2->isEmpty()) {
            nodeData = stack2->pop();
            tong     = tong + nodeData->data;

            if (nodeData->left) stack1->push(nodeData->left);

            if (nodeData->right) stack1->push(nodeData->right);
        }
        cout << tong << endl;
        tong = 0;
    }

    delete avl;
    delete stack1;
    delete stack2;
}

void e8() {
    Heap *heap = new Heap();
    int  *arr;
    int   count;

    ReadArrayInput("input/E8.txt", arr, count);
    heap->ArrayToHeap(arr, count);

    heap->PrintHeapTree();
    heap->PrintHeapLinear();
    cout << endl;

    Stack<int> *stack1 = new Stack<int>();
    stack1->push(0); // insert index of root

    Stack<int> *stack2 = new Stack<int>();

    while (!stack1->isEmpty() || !stack2->isEmpty()) {
        int tong = 0;

        if (!stack1->isEmpty()) {
            while (!stack1->isEmpty()) {
                int i = stack1->pop();
                tong = tong + (*heap)[i];

                if (i * 2 + 1 < count) stack2->push(i * 2 + 1);

                if (i * 2 + 2 < count) stack2->push(i * 2 + 2);
            }
            cout << tong << endl;
        }

        tong = 0;

        while (!stack2->isEmpty()) {
            int i = stack2->pop();
            tong = tong + (*heap)[i];

            if (i * 2 + 1 < count) stack1->push(i * 2 + 1);

            if (i * 2 + 2 < count) stack1->push(i * 2 + 2);
        }
        cout << tong << endl;
    }

    delete heap;
    delete stack1;
    delete stack2;
}

/**
 * Recursive func: travel in graph, count how many vertex visited
 * @param vertex The vertex to be visited.
 * @param visitedFlag The flag to mark the visited vertex.
 */
int visit(Vertex *vertex, int visitedFlag) {
    int visitedCount = 1;

    vertex->processed = visitedFlag;
    Edge *edge = vertex->firstEdge;

    while (edge) {
        if (edge->destination->processed != visitedFlag) {
            visitedCount += visit(edge->destination, visitedFlag);
        }
        edge = edge->nextEdge;
    }
    return visitedCount;
}

void e16() {
    Graph  *graph = graphReader("input/E16.txt");
    Vertex *vertex;

    graph->Print();

    int vertexCount = 0;

    vertex = graph->gHead;

    while (vertex) {
        vertexCount++;
        vertex = vertex->nextVertex;
    }

    if (vertexCount == 0) {
        std::cout << "Graph is empty" << '\n';
        return;
    }

    vertex = graph->gHead;

    while (vertex) {
        int visitedCount = visit(vertex, vertex->data);

        if (visitedCount < vertexCount) {
            std::cout << visitedCount << '\n';
            std::cout << "The graph is NOT strongly connected." << '\n';
            return;
        }
        vertex = vertex->nextVertex;
    }
    std::cout << "Graph is strongly connected." << '\n';
}
