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
