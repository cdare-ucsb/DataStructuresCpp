
#include "BPlusTree.h"
#include "BPlusNode.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <cassert>


int main() {
    BPlusTree<int> tree(6);

    for (int i = 0; i < 10; i++) {
        tree.insert(i);
    }

    std::cout << "Level Order:\n-------------------------\n\n\n";

    tree.printLevelOrder();

    std::cout << "\n\n\nLeaves:\n-------------------------\n\n\n";

    tree.printLeaves();

    return 0;
}