/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Node.h
	Purpose: Header file for the AVLTree class

	@author Kien Huynh
	@version 1.2 13-10-2016
***************************************************/

/**
*\file AVLTree.h
*/

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Node.h"
using namespace std;

/**
* \class AVLTree
* \brief Class for AVLTree data structure.
*
* This is implemented accordingly to the book Data Structures: A Pseudocode Approach with C.\n
* Note that in this implementation, we do not allow data duplication.\n
* Although data duplication is common in real-life applications, it is avoided here to ease the workload of this assignment.\n
*/
class AVLTree {
protected:
	/**
	* \cond
	*/
	Node* RotateRight();

	Node* RotateLeft();

	void LeftBalance(bool& taller);

	void RightBalance(bool& taller);

	Node* Insert(Node* newNode, bool& taller);

	void DeleteRightBalance(bool& shorter);

	void DeleteLeftBalance(bool& shorter);

	Node* Delete(int delData, bool& shorter, bool& success);
	/**
	* \endcond
	*/

public:
	/**
	* \var root
	* \brief Root of the AVLTree, can be NULL
	*/
	Node* root;

	/**
	* \brief Default constructor. \n Create an AVLTree with a NULL Node as root.
	*/
	AVLTree();

	/**
	* \brief Destructor
	*/
	~AVLTree();

	/**
	* \brief Constructor that takes a Node* pointer as a root
	*/
	AVLTree(Node* _root);

	/**
	* \brief Check if a Node exists in an AVLTree using \c nodeData
	* \return \c true if tree has nodeData
	* \return \c false if it doesn't
	*/
	bool NodeExist(int nodeData);

	/**
	* \brief Check if a Node exists in an AVLTree using \c node
	* \return \c true if tree has a Node with the same data as \c node
	* \return \c false if it doesn't
	*/
	bool NodeExist(Node* node);

	/**
	* \brief Insert new Node into the AVL using \c int newData
	* \return \c true if insert successfully
	* \return \c false if \c newData already exists in the tree
	*/
	bool AVLInsert(int newData);

	/**
	* \brief Insert new Node into the AVL using Node *newPtr
	* \return \c true if insert successfully
	* \return \c false if \c newPtr->data already exists in the tree or \c newPtr=NULL
	*/
	bool AVLInsert(Node* newPtr);

	/**
	* \brief Delete a Node with data equal to \b delData
	* \return \c true if succeeded in deleting a Node
	* \return \c false if the \b delData could not be found in the tree
	*/
	bool AVLDelete(int delData);

	/**
	* \brief Print the AVL Tree using LNR order
	*/
	void PrintAVL();

	/**
	* \brief Convert an int array to AVL
	* </tt>
	*/
	void ArrayToAVL(int arr[], int length);

	/**
	* \brief Check if the tree is empty
	* \return \c true if the tree is empty
	* \return \c false if the tree has at least one Node
	*/
	bool IsEmpty();
};

#endif
