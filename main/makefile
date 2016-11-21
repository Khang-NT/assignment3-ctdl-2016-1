all: app_flow

app_flow: app_flow.o AVLTree.o Node.o Graph.o Heap.o InputHeader.o
	g++ app_flow.o AVLTree.o Node.o Graph.o Heap.o InputHeader.o -o app_flow

app_flow.o: app_flow.cpp
	g++ -c app_flow.cpp

AVLTree.o: ../AVLTree.cpp
	g++ -c ../AVLTree.cpp

Node.o: ../Node.cpp
	g++ -c ../Node.cpp

Graph.o: ../Graph.cpp
	g++ -c ../Graph.cpp

Heap.o: ../Heap.cpp
	g++ -c ../Heap.cpp

InputHeader.o: ../InputHeader.cpp
	g++ -c ../InputHeader.cpp
