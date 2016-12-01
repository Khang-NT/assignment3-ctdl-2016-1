#include "skeleton.h"

struct StackItem {
    Node      *data;
    StackItem *next;
    StackItem(Node *data = NULL, StackItem *next = NULL) {
        this->data = data;
        this->next = next;
    }
};

struct Stack
{
    StackItem *top;
    int        count;
    Stack() {
        top   = 0;
        count = 0;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void push(Node *data) {
        top = new StackItem(data, top);
        count++;
    }

    Node* pop() {
        if (!isEmpty()) {
            StackItem *item = top;
            Node *result    = item->data;
            top = top->next;
            count--;
            delete item;
            return result;
        }
        return NULL;
    }
};

int seach(Heap heap, int& tcout, int data, int count) {
    for (int i = 0; i < count; i++) {
        if (heap[i] == data) {
            tcout = i;
            return tcout;
        }
    }
    return -1;
}

void e7() {
    AVLTree *avl = new AVLTree();
    int     *arr;
    int      count;

    ReadArrayInput("input/E7.txt", arr, count);
    avl->ArrayToAVL(arr, count);

    avl->PrintAVL();

    Stack *stack1 = new Stack();
    stack1->push(avl->root);

    Stack *stack2 = new Stack();

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

void e8() {}
