#ifndef MAX_HEAP_H
#define MAX_HEAP_H


#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <concepts>
#include "Comparable.h"


template<Comparable T>
class MaxHeap {

    private:
        std::vector<T> heap;

        void heapifyUp(size_t index) {
            size_t parent = (index - 1) / 2;

            while (index > 0 && heap[index] > heap[parent]) {
                std::swap(heap[index], heap[parent]);
                index = parent;
                parent = (index - 1) / 2;
            }
        }

        void heapifyDown(size_t index) {
            size_t size = heap.size();
            while (index < size) {
                size_t left = 2*index + 1;
                size_t right = 2*index + 2;
                size_t largest = index;

                if (left < size && heap[left] > heap[largest]) {
                    largest = left;
                }
                if (right < size && heap[right] > heap[largest]) {
                    largest = right;
                }

                if (largest != index ) {
                    std::swap(heap[index], heap[largest]);
                    index = largest;
                } else {
                    break;
                }
            }
        }

        void printHeapSideways(size_t index = 0, int level = 0) const {
            if (index >= heap.size()) return;
        
            size_t right = 2 * index + 2;
            size_t left = 2 * index + 1;
        
            // Print right child first (on top)
            printHeapSideways(right, level + 1);
        
            // Print current node with indentation
            for (int i = 0; i < level; ++i) std::cout << "    ";
            std::cout << heap[index] << "\n";
        
            // Then print left child (on bottom)
            printHeapSideways(left, level + 1);
        }
    

    public:

        MaxHeap() : heap() {}
        ~MaxHeap() = default;

        void push(const T& value) {
            heap.push_back(value);
            heapifyUp(heap.size() - 1);
        }

        T peek() {
            if (heap.empty()) {
                throw std::out_of_range("Heap is empty");
            }
            return heap[0];
        }

        void pop() {
            if (heap.empty()) {
                throw std::out_of_range("Heap is empty");
            }

            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);      
        }

        size_t size() {
            return heap.size();
        }   

        bool empty() {
            return heap.empty();
        }

        void print() {
            printHeapSideways(0,0);
        }


};


#endif //MAX_HEAP_H