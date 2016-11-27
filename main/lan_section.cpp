#include "skeleton.h"
#include "math.h"

/**
 * Recursive func: count number of even node in tree.
 * @param t - Root of tree.
 * @return number of even node in given tree.
 */
int EvenNumber(Node* t) {
  int result = 0;
	if (t != NULL) {
		result = EvenNumber(t->left) + EvenNumber(t->right);
		if (t->data % 2 == 0) {
			result++;
		}
	}
	return result;
}

/**
 * Recursive func: count number of odd node in tree.
 * @param t - Root of tree.
 * @return number of odd node in given tree.
 */
int OddNumber(Node* t) {
  int result = 0;
	if (t != NULL) {
		result = OddNumber(t->left) + OddNumber(t->right);
		if (t->data % 2 != 0) {
			result++;
		}
	}
	return result;
}

/**
 * Recursive func: count number of prime node in tree.
 * @param t - Root of tree.
 * @return number of prime node in given tree.
 */
int Prime(Node* t) {
  int result = 0;
	if (t != NULL) {
		result = Prime(t->left) + Prime(t->right);
		if (t->data < 2) return result;
    if (t->data == 2) return result + 1;
		for (int j = 2; j <= sqrt(t->data); j++) {
			if (t->data % j == 0) {
				return result;
			}
		}
		result++;
	}
	return result;
}

void maxHeapify(int *a, int i, int n)
{
	int j, temp;
	temp = a[i];
	j = 2 * i;
	while (j <= n) {
		if (j < n && a[j + 1] > a[j])
			j = j + 1;
		if (temp > a[j])
			break;
		else if (temp <= a[j]) {
			a[j / 2] = a[j];
			j = 2 * j;
		}
	}
	a[j / 2] = temp;
}

void buildMaxheap(int *a, int n)
{
	int i;
	for (i = n / 2; i >= 1; i--) {
		maxHeapify(a, i, n);
	}
}


void e1() {
  int n;
  int* arr;
	cout << "\nNhap so phan tu: ";
	n = getInt();
  arr = new int[n];
	AVLTree avl = AVLTree();
	for (int i = 0; i < n; i++) {
		cout << "arr[" << i + 1 << "]= ";
		arr[i] = getInt();
	}
  for (int i = 0; i < n; i++)
    avl.AVLInsert(arr[i]);
	cout << endl;
  // print AVLTree
	avl.PrintAVL();
}

void e3() {
  AVLTree avl = AVLTree();
	int *a;
	int count;
	ReadArrayInput("input/E3.txt", a, count);
	for (int i = 0; i < count; i++) {
		avl.AVLInsert(a[i]);
	}
	avl.PrintAVL();

	int k = EvenNumber(avl.root);
	cout << "So cac nut chan co tren cay: " << k << endl;

	int h = OddNumber(avl.root);
	cout << "So cac nut le co tren cay: " << h << endl;;

	int m = Prime(avl.root);
	cout << "So cac nut nguyen to co tren cay: " << m << endl;
}

void e10() {
  // wait to fix.

  // Heap heap = Heap();
	// Graph gph = Graph();
	// int *a;
	// int count;
	// ReadArrayInput("input/E10.txt", a, count);
  //
	// a[count] = a[0];
	// buildMaxheap(a, count);
  //
	// for (int i = 1; i <= count; i++) {
  //
	// 	heap.InsertHeap(a[i]);
	// 	gph.InsertVertex(a[i]);
	// }
	// heap.PrintHeapTree();
	// heap.PrintHeapLinear();
	// cout << endl;
  //
	// for (int i = 1; i <= count / 2; i++) {
	// 	int t1 = 2 * i;
	// 	int t2 = 2 * i + 1;
	// 	gph.InsertEdge(a[i], a[t1]);
	// 	gph.InsertEdge(a[i], a[t2]);
	// }
	// for (int i = 2; i <= count; i++) {
	// 	int par = i / 2;
	// 	gph.InsertEdge(a[i], a[par]);
	// }
  //
  //
	// gph.Print();
}

void e11() {
  Graph* gph = graphReader("input/E11.txt");
	gph->Print();

  // table configs
	const int cellWidth = 5;

  // print table header
  printTableCell("", cellWidth);
  Vertex* vertex = gph->gHead;
  while (vertex) {
    printTableCell(vertex->data, cellWidth);
    vertex = vertex->nextVertex;
  }
	cout << "\n";

  vertex = gph->gHead;
  Vertex* vertex2;
  while (vertex) {
    // print table column 0 : vertex data
    printTableCell(vertex->data, cellWidth);

    vertex2 = gph->gHead;
    while (vertex2) {
      Edge* edge = vertex->firstEdge;
      bool found = false;
      while (edge) {
        if (edge->destination->data == vertex2->data) {
          found = true;
          break;
        }
        edge = edge->nextEdge;
      }
      if (found)
        printTableCell("1", cellWidth);
      else
        printTableCell("-", cellWidth);
      vertex2 = vertex2->nextVertex;
    }
    std::cout << "\n";
    vertex = vertex->nextVertex;
  }
	// for (int i = 0; i < vertexCount; i++) {
	// 	printTableCell(vertexDataArr[i], cellWidth);
	// 	for (int j = 0; j < vertexCount; j++) {
	// 		if (gph.GetVertex(vertexDataArr[i])->outDegree >= 1 &&
  //     gph.GetVertex(vertexDataArr[i])->firstEdge->destination->data == vertexDataArr[j])
	// 			printTableCell(1, cellWidth);
	// 		else printTableCell("0", cellWidth);
	// 	}
	// 	cout << "\n";
	// }
}
