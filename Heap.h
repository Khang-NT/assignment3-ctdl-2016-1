/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Heap.h
	Purpose: Header file for the Heap class

	@author Kien Huynh
	@version 1.3 24-11-2016
***************************************************/

/**
*\file Heap.h
*/

#ifndef HEAP_H
#define HEAP_H
#include <iostream>
using namespace std;

/**
*\define HEAP_MAX
* Maximum length allowed for any Heap
*/

#define HEAP_MAX 1024

/**
* \class Heap
* \brief Class for Heap data structure
*
* This is implemented accordingly to the book Data Structures: A Pseudocode Approach with C.\n
* Note that in this implementation, we do not allow data duplication.\n
* Although data duplication is common in real-life applications, it is avoided here to ease the workload of this assignment.\n
* Note that in this class, you are not allowed to access all of its member variables
*/
class Heap{
protected:
	/**
	* \cond
	*/
	int *heapPtr;
	int last;
	int size;
	int maxSize;
	void ReHeapDown(int);
	void ReHeapUp(int);
	void swap(int, int);
	void PrintHeapTreeRe(int, int);
	/**
	* \endcond
	*/
public:
	/**
	* \brief Grant access (read-only) to heap members
	* This operator overloading allow you to access elements of the heap array easier. \n
	* Note that you can only access elements, not change them using this operator.
	*/
	int operator[](int);

	/**
	* \brief Default constructor with no argument
	*/
	Heap();

	/**
	* \brief Destructor
	*/
	~Heap();

	/**
	* \brief Create a Heap from an array \c arr with length \c len \n
	* Duplicate data in \c arr will be skipped
	* \param arr integer array of length \c len
	* \param len integer indicates the length of \c arr
	*/
	void ArrayToHeap(int* arr, int len);

	
	/**
	* \brief Check if the Heap is empty or not. \n
	* The name is obvious enough.
	* \return \c true if the Heap is empty
	* \return \c false if it is not
	*/
	bool IsEmpty();

	/**
	* \brief Check if the Heap is full or not (compared to HEAP_MAX). \n
	* The name is obvious enough. Seriously.
	* \return \c true if the Heap is full (size equal HEAP_MAX).
	* \return \c false if it is not
	*/
	bool IsFull();

	/**
	* \brief Check if the Heap already has \c data or not.\n
	* \return \c true if it does.
	* \return \c false if it does not.
	*/
	bool DataExist(int data);

	/**
	* \brief Print Heap like a normal array
	*/
	void PrintHeapLinear();

	/**
	* \brief Print Heap like a binary tree
	*/
	void PrintHeapTree();

	/**
	* \brief Insert new value into the Heap. \n
	* Does not accept duplicate data
	* \return \c true if insert successfully
	* \return \c false if HEAP_MAX is exceeded or \c data already exists in the Heap
	*/
	bool InsertHeap(int data);

	/**
	* \brief Remove the root element out of the Heap and store it in \c dataOut
	* \param dataOut integer variable that stores the value of the root
	* \return \c true if delete successfully
	* \return \c false if Heap is empty
	*/
	bool DeleteHeap(int& dataOut);
	
	/**
	* \brief Return the size of the Heap
	*/
	int GetSize();
};

#endif