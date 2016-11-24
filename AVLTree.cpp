/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Node.h
	Purpose: Implementation of the AVLTree class

	@author Kien Huynh
	@version 1.2 13-10-2016
***************************************************/

#include "AVLTree.h"


Node* AVLTree::RotateRight() {
	Node* tmpPtr = root->left;
	root->left = tmpPtr->right;
	tmpPtr->right = root;
	root = tmpPtr;
	return root;
}

Node* AVLTree::RotateLeft() {
	Node* tmpPtr = root->right;
	root->right = tmpPtr->left;
	tmpPtr->left = root;
	root = tmpPtr;
	return root;
}

void AVLTree::LeftBalance(bool& taller) {
	Node* leftTree = root->left;
	if (leftTree->balance == LEFT) {
		root->balance = EQUAL;
		leftTree->balance = EQUAL;
		RotateRight();
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
		root->left = AVLTree(root->left).RotateLeft();
		RotateRight();
		taller = false;
	}
}

void AVLTree::RightBalance(bool& taller) {
	Node* rightTree = root->right;
	if (rightTree->balance == RIGHT) {
		root->balance = EQUAL;
		rightTree->balance = EQUAL;
		RotateLeft();
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
		root->right = AVLTree(root->right).RotateRight();
		RotateLeft();
		taller = false;
	}
}

Node* AVLTree::Insert(Node* newNode, bool& taller) {
	if (root == NULL) {
		root = newNode;
		taller = true;
	}
	else if (newNode->data < root->data) {
		root->left = AVLTree(root->left).Insert(newNode, taller);
		//AVLinsert(newNode, taller);
		if (taller) {
			if (root->balance == LEFT) {
				LeftBalance(taller);
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
		root->right = AVLTree(root->right).Insert(newNode, taller);
		if (taller) {
			if (root->balance == LEFT) {
				root->balance = EQUAL;
				taller = false;
			}
			else if (root->balance == EQUAL) {
				root->balance = RIGHT;
			}
			else {
				RightBalance(taller);
			}
		}
	}
	return root;
}

void AVLTree::DeleteRightBalance(bool& shorter) {
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
			root->right = AVLTree(root->right).RotateRight();
			RotateLeft();
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
			RotateLeft();
		}
	}
}

void AVLTree::DeleteLeftBalance(bool& shorter) {
	if (root->balance == RIGHT) {
		root->balance = EQUAL;
	}
	else if (root->balance == EQUAL) {
		root->balance = LEFT;
		shorter = false;
	}
	else {
		Node* leftTree = root->left;
		if ((leftTree->balance = RIGHT)) {
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
			root->left = AVLTree(root->left).RotateLeft();
			RotateRight();
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
			RotateRight();
		}
	}
}

Node* AVLTree::Delete(int delData, bool& shorter, bool& success){
	if (root == NULL) {
		shorter = false;
		success = false;
		return NULL;
	}
	if (delData < root->data) {
		root->left = AVLTree(root->left).Delete(delData, shorter, success);
		if (shorter) {
			DeleteRightBalance(shorter);
		}
	}
	else if (delData > root->data) {
		root->right = AVLTree(root->right).Delete(delData, shorter, success);
		if (shorter) {
			DeleteLeftBalance(shorter);
		}
	}
	else {
		Node* deleteNode = root;
		if (deleteNode->right == NULL) {
			Node* newRoot = root->left;
			success = true;
			shorter = true;
			delete deleteNode;
			root = newRoot;
			return root;
		}
		else if (deleteNode->left == NULL) {
			Node* newRoot = root->right;
			success = true;
			shorter = true;
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
			root->left = AVLTree(root->left).Delete(exchPtr->data, shorter, success);
			if (shorter) {
				DeleteRightBalance(shorter);
			}
		}
	}
	return root;
}

AVLTree::AVLTree() {
	root = NULL;
}

AVLTree::AVLTree(Node* _root) {
	root = _root;
}

AVLTree::~AVLTree() {
	delete root;
	root = NULL;
}

bool AVLTree::AVLInsert(int newData) {
	if (NodeExist(newData)) {
		return false;
	}
	Node* newPtr = new Node(newData);
	bool taller = true;
	Insert(newPtr, taller);
	return true;
}

bool AVLTree::AVLInsert(Node* newPtr)
{
	if (newPtr == NULL) {
		return false;
	}
	if (NodeExist(newPtr->data)) {
		return false;
	}
	bool taller = true;
	Insert(newPtr, taller);
	return true;
}

bool AVLTree::AVLDelete(int delData) {
	bool shorter = true;
	bool success = true;
	Delete(delData, shorter, success);
	return success;
}

void AVLTree::PrintAVL() {
	root->PrintNode();
}

void AVLTree::ArrayToAVL(int arr[], int length) {
	for (int i = 0; i < length; i++) {
		Node* newPtr = new Node(arr[i]);
		AVLInsert(newPtr);
	}
}

bool AVLTree::IsEmpty() {
	if (root == NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool AVLTree::NodeExist(int nodeData) {
	return root->HasNode(nodeData);
}

bool AVLTree::NodeExist(Node* node) {
	return root->HasNode(node->data);
}
