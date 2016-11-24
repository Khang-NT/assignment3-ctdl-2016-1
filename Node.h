/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Node.h
	Purpose: Header file for the Node class

	@author Kien Huynh
	@version 1.0 03-10-2016
***************************************************/

#ifndef NODE_H
#define NODE_H
#include <iostream>

/**
*\file Node.h
*/

/**
* \enum Balance
* \brief Helper enum for member \c balance of Class Node
*/
enum Balance { LEFT, EQUAL, RIGHT };

/**
* \class Node
* \brief Class for Node of a Tree
*
* This is implemented accordingly to the book Data Structures: A Pseudocode Approach with C.\n
* Building class for the AVLTree class.\n
*/
class Node {
public:

	/**
	* \var data
	* \brief Node data.
	*/
	int data;

	/**
	* \var left
	* \brief Left child.
	*/
	Node* left;

	/**
	* \var right
	* \brief Right child.
	*/
	Node* right;

	/**
	* \var balance
	* \brief Balance at this particular Node, use BALANCE enum.
	*/
	Balance balance;
	
	
	/**
	* \brief Default constructor. \n Create a Node with \c data=0.
	*/
	Node();

	/**
	* \brief Constructor that takes an integer as node data
	*/
	Node(int);

	/**
	* \brief Destructor
	*/
	~Node();

	/**
	* \brief Print this Node and every of its children in LNR order.
	*/
	void PrintNode(int indent = 0);

	/**
	* \brief Check if this Node or its children has \c nodeData.
	*/
	bool HasNode(int nodeData);

};

#endif