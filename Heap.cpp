/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	Heap.cpp
	Purpose: Implementation for the Heap class

	@author Kien Huynh
	@version 1.3 24-11-2016
***************************************************/

#include "Heap.h"
Heap::Heap() {
	heapPtr = NULL;
	last = -1;
	maxSize = HEAP_MAX;
	size = 0;
}

Heap::~Heap(){
	delete heapPtr;
	heapPtr = NULL;
}

void Heap::swap(int a, int b) {
	int tempVal = heapPtr[a];
	heapPtr[a] = heapPtr[b];
	heapPtr[b] = tempVal;
}

void Heap::ReHeapUp(int position) {
	if (position > 0) {
		int parent = (position - 1) / 2;
		if (heapPtr[position] > heapPtr[parent]) {
			swap(position, parent);
			ReHeapUp(parent);
		}
	}
}

void Heap::ReHeapDown(int position) {
	int leftChild = position * 2 + 1;
	int rightChild = position * 2 + 2;
	int largeChild = 0;
	if (leftChild <= last) {
		if (rightChild <= last && heapPtr[rightChild] > heapPtr[leftChild]) {
			largeChild = rightChild;
		}
		else {
			largeChild = leftChild;
		}
		if (heapPtr[largeChild] > heapPtr[position]) {
			swap(largeChild, position);
			ReHeapDown(largeChild);
		}
	}
}

void Heap::ArrayToHeap(int* arr, int length){
	size = 0;
	last = -1;
	heapPtr = new int[HEAP_MAX];
	for (int i = 0; i < length; i++) {
		if (!DataExist(arr[i])) {
			size++;
			heapPtr[size - 1] = arr[i];
			if (size == HEAP_MAX) {
				break;
			}
		}
	}

	for (int i = 0; i < size; i++) {
		ReHeapUp(i);
		last++;
	}
}

int Heap::operator [](const int i){
	if (i < size && i >= 0) {
		return heapPtr[i];
	}
	else {
		cout << "Heap index out of bound, returning -1.";
		return -1;
	}
};

bool Heap::IsEmpty() {
	if (heapPtr == NULL || size == 0) {
		return true;
	}
	return false;
}

bool Heap::IsFull() {
	if (size == HEAP_MAX) {
		return true;
	}
	return false;
}

void Heap::PrintHeapLinear() {
	for (int i = 0; i < size; i++) {
		cout << heapPtr[i] << " ";
	}
	cout << endl;
}

void Heap::PrintHeapTreeRe(int position, int indent) {
	if (position * 2 + 2 < size) {
		PrintHeapTreeRe(position * 2 + 2, indent+1);
	}
	for (int i = 0; i < indent; i++) {
		cout << "\t";
	}
	cout << heapPtr[position] << endl;
	if (position * 2 + 1 < size) {
		PrintHeapTreeRe(position * 2 + 1, indent + 1);
	}
}

bool Heap::DataExist(int data) {
	for (int i = 0; i < size; i++) {
		if (heapPtr[i] == data) {
			return true;
		}
	}
	return false;
}

void Heap::PrintHeapTree() {
	if (size > 0) PrintHeapTreeRe(0, 0);
}

bool Heap::InsertHeap(int data) {
	if (IsFull() || DataExist(data)) {
		return false;
	}
	if (heapPtr == NULL) {
		heapPtr = new int[HEAP_MAX];
	}
	last++;
	size++;
	heapPtr[last] = data;
	ReHeapUp(last);
	return true;
}

bool Heap::DeleteHeap(int &dataOut) {
	if (IsEmpty()) {
		return false;
	}
	dataOut = heapPtr[0];
	heapPtr[0] = heapPtr[last];
	last--;
	size--;
	if (size == 0) {
		delete heapPtr;
		heapPtr = NULL;
	}
	else {
		ReHeapDown(0);
	}
	return true;
}

int Heap::GetSize() {
	return size;
}