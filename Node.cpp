/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Node.cpp
	Purpose: Implementation of the Node class
	Basic block for AVLTree

	@author Kien Huynh
	@version 1.3 11-25-2016
***************************************************/

#include "Node.h"
using namespace std;

// AVL Implementation
void Node::RotateRight(Node* &root) {
	Node* tmpPtr = root->left;
	root->left = tmpPtr->right;
	tmpPtr->right = root;
	root = tmpPtr;
}

void Node::RotateLeft(Node* &root) {
	Node* tmpPtr = root->right;
	root->right = tmpPtr->left;
	tmpPtr->left = root;
	root = tmpPtr;
}

void Node::LeftBalance(Node*& root, bool& taller) {
	Node* leftTree = root->left;
	if (leftTree->balance == LEFT) {
		root->balance = EQUAL;
		leftTree->balance = EQUAL;
		RotateRight(root);
		taller = false;
	}
	else {
		Node* rightTree = leftTree->right;
		if (rightTree->balance == LEFT) {
			root->balance = RIGHT;
			leftTree->balance = EQUAL;
		}
		else if (rightTree->balance == EQUAL) {
			root->balance = EQUAL;
			leftTree->balance = EQUAL;
		}
		else {
			root->balance = EQUAL;
			leftTree->balance = LEFT;
		}
		rightTree->balance = EQUAL;
		RotateLeft(root->left);
		RotateRight(root);
		taller = false;
	}
}

void Node::RightBalance(Node*& root, bool& taller) {
	Node* rightTree = root->right;
	if (rightTree->balance == RIGHT) {
		root->balance = EQUAL;
		rightTree->balance = EQUAL;
		RotateLeft(root);
		taller = false;
	}
	else {
		Node* leftTree = rightTree->left;
		if (leftTree->balance == RIGHT) {
			root->balance = LEFT;
			rightTree->balance = EQUAL;
		}
		else if (leftTree->balance == EQUAL) {
			root->balance = EQUAL;
			rightTree->balance = EQUAL;
		}
		else {
			root->balance = EQUAL;
			rightTree->balance = RIGHT;
		}
		leftTree->balance = EQUAL;
		RotateRight(root->right);
		RotateLeft(root);
		taller = false;
	}
}

Node* Node::AVLInsert(Node*& root, Node* newNode, bool& taller) {
	if (root == NULL) {
		root = newNode;
		taller = true;
	}
	else if (newNode->data < root->data) {
		root->left = AVLInsert(root->left, newNode, taller);
		//AVLinsert(newNode, taller);
		if (taller) {
			if (root->balance == LEFT) {
				LeftBalance(root, taller);
			}
			else if (root->balance == EQUAL) {
				root->balance = LEFT;
			}
			else {
				root->balance = EQUAL;
				taller = false;
			}
		}
	}
	else {
		root->right = AVLInsert(root->right, newNode, taller);
		if (taller) {
			if (root->balance == LEFT) {
				root->balance = EQUAL;
				taller = false;
			}
			else if (root->balance == EQUAL) {
				root->balance = RIGHT;
			}
			else {
				RightBalance(root, taller);
			}
		}
	}
	return root;
}

void Node::DeleteRightBalance(Node*& root, bool& shorter) {
	if (root->balance == LEFT) {
		root->balance = EQUAL;
	}
	else if (root->balance == EQUAL) {
		root->balance = RIGHT;
		shorter = false;
	}
	else {
		Node* rightTree = root->right;
		if (rightTree->balance == LEFT) {
			Node* leftTree = rightTree->left;
			if (leftTree->balance == LEFT) {
				rightTree->balance = RIGHT;
				root->balance = EQUAL;
			}
			else if (leftTree->balance == EQUAL) {
				root->balance = LEFT;
				rightTree->balance = EQUAL;
			}
			else {
				root->balance = LEFT;
				rightTree->balance = EQUAL;
			}
			leftTree->balance = EQUAL;
			RotateRight(root->right);
			RotateLeft(root);
		}
		else {
			if (rightTree->balance != EQUAL) {
				root->balance = EQUAL;
				rightTree->balance = EQUAL;
			}
			else {
				root->balance = RIGHT;
				rightTree->balance = LEFT;
				shorter = false;
			}
			RotateLeft(root);
		}
	}
}

void Node::DeleteLeftBalance(Node*& root, bool& shorter) {
	if (root->balance == RIGHT) {
		root->balance = EQUAL;
	}
	else if (root->balance == EQUAL) {
		root->balance = LEFT;
		shorter = false;
	}
	else {
		Node* leftTree = root->left;
		if (leftTree->balance == RIGHT) {
			Node* rightTree = leftTree->right;
			if (rightTree->balance == RIGHT) {
				leftTree->balance = LEFT;
				root->balance = EQUAL;
			}
			else if (rightTree->balance == EQUAL) {
				root->balance = RIGHT;
				leftTree->balance = EQUAL;
			}
			else {
				root->balance = RIGHT;
				leftTree->balance = EQUAL;
			}
			rightTree->balance = EQUAL;
			RotateLeft(root->left);
			RotateRight(root);
		}
		else {
			if (leftTree->balance != EQUAL) {
				root->balance = EQUAL;
				leftTree->balance = EQUAL;
			}
			else {
				root->balance = LEFT;
				leftTree->balance = RIGHT;
				shorter = false;
			}
			RotateRight(root);
		}
	}
}

Node* Node::AVLDelete(Node*& root, int delData, bool& shorter, bool& success){
	if (root == NULL) {
		shorter = false;
		success = false;
		return NULL;
	}
	if (delData < root->data) {
		root->left = AVLDelete(root->left, delData, shorter, success);
		if (shorter) {
			DeleteRightBalance(root, shorter);
		}
	}
	else if (delData > root->data) {
		AVLDelete(root->right, delData, shorter, success);
		if (shorter) {
			DeleteLeftBalance(root, shorter);
		}
	}
	else {
		Node* deleteNode = root;

		if (deleteNode->right == NULL) {
			Node* newRoot = root->left;
			success = true;
			shorter = true;
			deleteNode->right = NULL;
			deleteNode->left = NULL;
			delete deleteNode;
			root = newRoot;
			return root;
		}
		else if (deleteNode->left == NULL) {
			Node* newRoot = root->right;
			success = true;
			shorter = true;
			deleteNode->right = NULL;
			deleteNode->left = NULL;
			delete deleteNode;
			root = newRoot;
			return root;
		}
		else {
			Node* exchPtr = root->left;
			while (exchPtr->right != NULL) {
				exchPtr = exchPtr->right;
			}
			root->data = exchPtr->data;
			AVLDelete(root->left, exchPtr->data, shorter, success);
			if (shorter) {
				DeleteRightBalance(root, shorter);
			}
		}
	}
	return root;
}

Node::Node(){
	data = 0;
	left = NULL;
	right = NULL;
	balance = EQUAL;
}

Node::Node(int _data) {
	data = _data;
	left = NULL;
	right = NULL;
	balance = EQUAL;
}

Node::~Node() {
    if (left)
        delete left, left = NULL;
    if (right)
        delete right, right = NULL;
}

void Node::PrintNode(int indent) {
	if (this == NULL) {
		return;
	}
	if (right)
		right->PrintNode(indent + 1);
	for (int i = 0; i < indent; i++) {
		cout << "\t";
	}
	cout << data << endl;
	if (left)
		left->PrintNode(indent + 1);
}

bool Node::HasNode(int nodeData) {
	if (this == NULL) {
		return false;
	}
	if (data == nodeData) {
		return true;
	}
	return ((right && right->HasNode(nodeData)) ||
		(left && left->HasNode(nodeData)));
}
