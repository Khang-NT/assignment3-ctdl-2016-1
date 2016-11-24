#include <iostream>
#include "skeleton.h"

void echoMenu() {
  std::cout << "========================================================" << '\n';
  std::cout << "                          MENU                          " << '\n';
  std::cout << "1. Basic section" << '\n';
  std::cout << "2. AVL tree delete" << '\n';
  std::cout << "3. Count odd number, even number, prime number nodes" << '\n';
  std::cout << "4. Heap tree insert" << '\n';
  std::cout << "5. Print Graph" << '\n';
  std::cout << "6. Delete a vertex in Graph" << '\n';
  std::cout << "7. Measure the height of AVL tree" << '\n';
  std::cout << "8. Measure the height of Heap tree" << '\n';
  std::cout << "9. Convert an AVL tree into a Graph" << '\n';
  std::cout << "10. Convert a Heap tree into a Graph" << '\n';
  std::cout << "11. Convert an Adjacency Matrix into a Graph" << '\n';
  std::cout << "12. Convert an AVL tree into an Adjacency Matrix" << '\n';
  std::cout << "13. Convert a Heap tree into an Adjacency Matrix" << '\n';
  std::cout << "14. Count the number of circuits in a Graph" << '\n';
  std::cout << "15. Convert a Graph into an Adjacency Matrix" << '\n';
  std::cout << "16. Check if a Graph is strongly connected" << '\n';
  std::cout << "17. Check if an Adjacency Matrix is AVL tree" << '\n';
  std::cout << "========================================================" << '\n';
}

int getInt() {
  int value;
  while (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }
  return value;
}

int getSelection() {
  std::cout << "Enter your selection: ";
  int selection = 0;
  selection = getInt();
  return selection;
}

void echoStopMenu() {
  std::cout << "========================================================" << '\n';
  std::cout << "                  Do you want to stop?                  " << '\n';
  std::cout << "0. No" << '\n';
  std::cout << "1. Yes" << '\n';
  std::cout << "========================================================" << '\n';
}

int main() {
  bool stop = false;
  while (!stop) {
    echoMenu();
    int selection = getSelection();
    // navigate to sub section or print invalid selection
    switch (selection) {
      case 5:
        e5();
        break;
      case 14:
        e14();
        break;
      default:
        std::cout << "Invalid selection" << '\n';
    }

    echoStopMenu();
    do {
      selection = getSelection();
    } while(selection < 0 || selection > 1);

    stop = selection == 1;
  }
  return 0;
}
