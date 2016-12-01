#include "skeleton.h"

struct StackItem {
    Node      *Nodedata;
    int        data;
    StackItem *next;
};

struct Stack
{
    StackItem *top;
    int        count;
};

bool isEmpty(Stack *s) {
    if (!s) return 1;

    if ((s->top == NULL) || (s->count == 0)) return 1;
    else return 0;
}

void pushStack(int& d, Stack *& s, Node *& nodeData) {
    if (!s) return;

    StackItem *pNew = new StackItem;
    pNew->data     = d;
    pNew->Nodedata = nodeData;
    pNew->next     = NULL;

    if (isEmpty(s)) {
        s->top   = pNew;
        s->count = s->count + 1;
    }
    else {
        pNew->next = s->top;
        s->top     = pNew;
        s->count   = s->count + 1;
    }
}

void popStack(Stack *& s, int& data, Node *& nodeData) {
    if (!(isEmpty(s))) {
        StackItem *pDel = s->top;
        data     = pDel->data;
        nodeData = pDel->Nodedata;

        s->top = s->top->next;
        s->count--;

        delete pDel, pDel = NULL;
    }
}

void e7() {
    AVLTree avl7 = AVLTree();
    int    *a;
    int     count;

    ReadArrayInput("input/E7.txt", a, count);

    for (int i = 0; i < count; i++) {
        avl7.AVLInsert(a[i]);
    }
    avl7.PrintAVL();
    Node *root7 = avl7.root;

    StackItem *head = new StackItem;
    head->data     = root7->data;
    head->next     = NULL;
    head->Nodedata = root7;

    Stack *stack1 = new Stack;
    stack1->count = 1;
    stack1->top   = head;
    Stack *stack2 = new Stack;
    stack2->count = 0;
    stack2->top   = NULL;
    int tong = 0;
    int data = 0;

    while (stack1->top != NULL || stack2->top != NULL) {
        data = 0;
        Node *nodeData = NULL;

        if (stack1->top != NULL) {
            while (stack1->top != NULL) {
                if (stack1->top != NULL) {
                    popStack(stack1, data, nodeData);
                    tong = tong + data;

                    if (nodeData->left != NULL) {
                        pushStack(nodeData->left->data, stack2, nodeData->left);

                        // cout << "Kqstack2->top" << stack2->top->data;
                    }

                    if (nodeData->right != NULL) {
                        pushStack(nodeData->right->data, stack2,
                                  nodeData->right);

                        // cout << "Kqstack22->top" << stack2->top->data;
                    }
                }
            }
        }
        else {
            if (stack2->top != NULL) {
                while (stack2->top != NULL) {
                    if (stack2->top != NULL) {
                        popStack(stack2, data, nodeData);
                        tong = tong + data;

                        if (nodeData->left != NULL) {
                            pushStack(nodeData->left->data,
                                      stack1,
                                      nodeData->left);

                            // cout << "Kqstack1->top" << stack1->top->data;
                        }

                        if (nodeData->right != NULL) {
                            pushStack(nodeData->right->data,
                                      stack1,
                                      nodeData->right);

                            // cout << "Kqstack12->top" << stack1->top->data;
                        }
                    }
                }
            }
        }
        cout << tong << endl;
        tong = 0;
    }
}
