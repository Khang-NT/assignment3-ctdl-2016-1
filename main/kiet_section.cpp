#include "skeleton.h"

template<class T>
struct LinkedList {
    T             *data;
    LinkedList<T> *next;
    LinkedList(T *data, LinkedList<T> *next = 0) : data(data), next(next) {}

    virtual ~LinkedList() {
        data = 0;
        delete next;
        next = 0;
    }
};

void e2() {
    int m;
    AVLTree *avlTree = avlReader("input/E2.txt");

    avlTree->PrintAVL();

    do  {
        cout << "Nhap vao nut can xoa (hoac -1 de thoat): ";
        m = getInt();
        avlTree->AVLDelete(m);
        avlTree->PrintAVL();
    } while (m != -1);

    delete avlTree;
    avlTree = 0;
}

void e4() {
    int  n;
    Heap heap;

    cout << "So phan tu cua mang la : ";
    n = getInt();

    for (int i = 0; i < n; i++)    {
        cout << "arr[" << i << "] = ";
        heap.InsertHeap(getInt());
    }
    cout << "Ket qua cuoi cung dang cay theo thu tu LNR la : " << endl;
    heap.PrintHeapTree();
}

void e15() {
    Graph *graph = readGraphFromMatrix("input/E15.txt");

    graph->Print();
    delete graph;
}

void e12() {
    AVLTree *avlTree = avlReader("input/E12.txt");

    avlTree->PrintAVL();

    Node *node                   = avlTree->root;
    LinkedList<Node> *linkedList = new LinkedList<Node>(node);
    LinkedList<Node> *cursor1    = linkedList;
    LinkedList<Node> *cursor2    = linkedList;

    // BFS
    while (cursor1) {
        if (cursor1->data->left) {
            cursor2->next = new LinkedList<Node>(cursor1->data->left);
            cursor2       = cursor2->next;
        }

        if (cursor1->data->right) {
            cursor2->next = new LinkedList<Node>(cursor1->data->right);
            cursor2       = cursor2->next;
        }
        cursor1 = cursor1->next;
    }

    // reset
    cursor1 = cursor2 = 0;

    // table configs
    const int cellWidth = 5;

    // print table header
    cout << "Ma tran ke : " << endl;
    printTableCell("", cellWidth);
    cursor1 = linkedList;

    while (cursor1) {
        printTableCell(cursor1->data->data, cellWidth);
        cursor1 = cursor1->next;
    }
    std::cout << '\n';

    // print table content
    cursor1 = linkedList;

    while (cursor1) {
        printTableCell(cursor1->data->data, cellWidth);

        cursor2 = linkedList;

        while (cursor2) {
            if ((cursor2->data == cursor1->data->left) ||
                (cursor2->data == cursor1->data->right)) {
                printTableCell("1", cellWidth);
            } else {
                printTableCell("-", cellWidth);
            }
            cursor2 = cursor2->next;
        }
        cursor1 = cursor1->next;

        std::cout << '\n';
    }

    // collect garbage
    delete linkedList;
    delete avlTree;
}
