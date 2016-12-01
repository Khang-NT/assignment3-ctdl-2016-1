#ifndef SKELETION_H
#define SKELETION_H
#include <iostream>
#include <iomanip>
#include "../InputReader.h"
#include "../Graph.h"
#include "../Heap.h"
#include "../Node.h"
#include "../AVLTree.h"

/* Define entrance funcs foreach missions */

void e1();
void e2();
void e3();
void e4();
void e5();
void e6();
void e7();
void e8();
void e9();
void e10();
void e11();
void e12();
void e13();
void e14();
void e15();
void e16();
void e17();

// Helper methods

/**
 * Get int value from standard input, handle error and retry if any.
 * @return An integer value read from standard input.
 */
int      getInt();

/**
 * Reusable func: Parse AVL tree from file, using {@link ReadArrayInput}.
 * @param fileName The relative path to file contain graph data
 *("input/E16.txt", e.g).
 * @return The (pointer of) AVL tree which has data given in input file.
 */
AVLTree* avlReader(string filename);

/**
 * Reusable func: Parse graph from file, using {@link ReadArrayInputOfGraph}.
 * @param fileName The relative path to file contain graph data
 *("input/E13.txt", e.g).
 * @return The (pointer of) graph which has data given in input file.
 */
Graph  * graphReader(string fileName);

/**
 * Reusable func: Print content in space with fixed width and align to left.
 * @param content The content to be printed.
 * @param cellWidth The width of cell contain the content.
 *
 * Generic type T - any type has operator "<<".
 */
template<typename T>
void printTableCell(T   content,
                    int cellWidth);

#endif // ifndef SKELETION_H
