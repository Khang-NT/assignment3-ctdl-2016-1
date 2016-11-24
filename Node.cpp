/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Node.cpp
	Purpose: Implementation of the Node class
	Basic block for AVLTree

	@author Kien Huynh
	@version 1.0 03-10-2016
***************************************************/

#include "Node.h"
using namespace std;

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
	delete left;
	left = NULL;
	delete right;
	right = NULL;
}

void Node::PrintNode(int indent) {
	// always evaluate to false
	// if (this == NULL) {
	// 	return;
	// }
	right->PrintNode(indent + 1);
	for (int i = 0; i < indent; i++) {
		cout << "\t";
	}
	cout << data << endl;
	left->PrintNode(indent + 1);
}

bool Node::HasNode(int nodeData) {
	// always evaluate to false
	// if (this == NULL) {
	// 	return;
	// }
	if (data == nodeData) {
		return true;
	}
	return (right->HasNode(nodeData) ||
		left->HasNode(nodeData));
}
