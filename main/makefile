all: app_flow
clean:
	rm -f *.o app_flow.bin
run:
	chmod +x app_flow && ./app_flow.bin

app_flow: app_flow.o AVLTree.o Node.o Graph.o Heap.o InputHeader.o \
		khang_section.o lan_section.o long_section.o tien_section.o kiet_section.o
	g++ app_flow.o AVLTree.o Node.o Graph.o Heap.o InputHeader.o khang_section.o \
		lan_section.o long_section.o tien_section.o kiet_section.o -o app_flow.bin

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

khang_section.o: khang_section.cpp
	g++ -c khang_section.cpp

lan_section.o: lan_section.cpp
	g++ -c lan_section.cpp

long_section.o: long_section.cpp
	g++ -c long_section.cpp

tien_section.o: tien_section.cpp
	g++ -c tien_section.cpp

kiet_section.o: kiet_section.cpp
	g++ -c kiet_section.cpp
