#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <memory>
#include <concepts>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <algorithm>
#include "TreeNode.h"
#include "Comparable.h"


template<Comparable T>
class BinaryTree
{
    public:

        BinaryTree() : root(nullptr) {}
        ~BinaryTree() = default;

        void insert(T value) {
            if (!root) {
                root = std::make_unique<TreeNode<T>>(value);
            } else {
                root->insert(value);
            }
        }

        TreeNode<T>* find(T value) {
            if (root) {
                return root->find(value);
            }
            return nullptr;
        }

        void remove(T value) {
            if (root) {
                root->remove(value, root);
            }
        }

        void printInOrder() {
            if (root) {
                root->printInOrder();
            }
        }

        void printPreOrder() {
            if (root) {
                root->printPreOrder();
            }
        }

        void printPostOrder() {
            if (root) {
                root->printPostOrder();
            }
        }

        void printLevelOrder() {
            if (root) {
                root->printLevelOrder();
            }
        }

        std::vector<T> collectInOrder() {
            std::vector<T> values;
            if (root) {
                root->collectInOrder(values);
            }
            return values;
        }

        std::vector<T> collectPreOrder() {
            std::vector<T> values;
            if (root) {
                root->collectPreOrder(values);
            }
            return values;
        }

        std::vector<T> collectPostOrder() {
            std::vector<T> values;
            if (root) {
                root->collectPostOrder(values);
            }
            return values;
        }

        std::vector<T> collectLevelOrder() {
            std::vector<T> values;
            if (root) {
                root->collectLevelOrder(values);
            }
            return values;
        }

        size_t height() {
            if (root) {
                return root->height();
            }
            return 0;
        }

        size_t size() {
            if (root) {
                return root->size();
            }
            return 0;
        }

        void balance() {
            // Collect all values in order
            std::vector<T> values = collectInOrder();

            // Clear the tree
            this->clear();
            
            // Rebuid the tree with the values using a helper method to
            // reinsert the values in a similar way to binary search
            this->balance_helper(values, 0, values.size() - 1);
        }

        void clear() {
            root.reset();
        }

        void print() {
            printSideways(root.get());
        }
        
        
        
        


    private:

        std::unique_ptr<TreeNode<T>> root;


        void balance_helper(std::vector<T>& values, int start, int end) {
            if (start > end) {
                return;
            }
            int mid = (start + end) / 2;

            // Do a 'preorder' insert of the middle value
            this->insert(values[mid]);

            // Recursively insert the left and right halves
            this->balance_helper(values, start, mid - 1);
            this->balance_helper(values, mid + 1, end);
        }

        void printSideways(TreeNode<T>* node, int depth = 0) {
            if (!node) return;
        
            printSideways(node->right.get(), depth + 1);
        
            std::cout << std::string(depth * 4, ' ') << node->data << "\n";
        
            printSideways(node->left.get(), depth + 1);
        }

};


#endif // BINARYTREE_H