
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <concepts>
#include "Comparable.h"
#include "MaxHeap.h"


int main() {

    std::vector<int> v = {10, 20, 15, 40, 12, 25, 18, 50};

    MaxHeap<int> heap;

    for (int i : v) {
        heap.push(i);
    }

    heap.print();

    std::vector<int> reverse_sorted;
    while (!heap.empty()) {
        int to_add = heap.peek();
        heap.pop();
        reverse_sorted.push_back(to_add);
    }

    std::cout << "Reverse sorted: ";
    for (int i : reverse_sorted) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
