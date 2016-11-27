/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Node.h
	Purpose: Implementation of the AVLTree class

	@author Kien Huynh
	@version 1.2 13-10-2016
***************************************************/

#include "AVLTree.h"

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
	root = Node::AVLInsert(root, newPtr, taller);
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
	root = Node::AVLInsert(root, newPtr, taller);
	return true;
}

bool AVLTree::AVLDelete(int delData) {
	bool shorter = true;
	bool success = true;
	root = Node::AVLDelete(root, delData, shorter, success);
	//Delete(delData, shorter, success);
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
	return root && root->HasNode(nodeData);
}

bool AVLTree::NodeExist(Node* node) {
	return root && root->HasNode(node->data);
}
