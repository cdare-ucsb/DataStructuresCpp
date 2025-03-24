#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <cassert>
#include "BPlusNode.h"



template <Comparable T>
class BPlusTree {
    private:

        static constexpr size_t DEFAULT_ORDER = 4;
        size_t order;
        std::shared_ptr<BPlusNode<T>> root;

        void insertHelper(std::shared_ptr<BPlusNode<T>> node, T key) {
            if (node->is_leaf) {
                /*
                *    Case 1: The node is a leaf node. We can simply insert the key into the node.
                *            If the node is full after the insertion, we need to split the node.
                */
                node->insert_key(key);
                if (node->is_full()) {
                    split(node);
                }
            } else {
                /*
                *    Case 2: The node is not a leaf node. We need to find the child node
                *            that the key should be inserted into, and then recursively
                *            insert the key into that child node.
                * 
                *            Recall the keys act as partitions of the children; the lower 
                *            bound function returns the first key element that is greater
                *            than or equal to the key we are inserting.
                * 
                *            For example, when inserting key=5 into the following node:
                * 
                *              keys= [10, 20, 30], children=[A, B, C, D]
                *           
                *           The lower_bound function will return the index corresponding to
                *           the key 10, so we know that the key 5 should be inserted into the
                *            child at index 0.
                */

                size_t index = std::lower_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin();
                insertHelper(node->children[index], key);            
            }
        }


        void split(std::shared_ptr<BPlusNode<T>> node) {

            size_t mid = node->keys.size() / 2;
            

            if (node->is_leaf) {

                std::shared_ptr<BPlusNode<T>> new_leaf = std::make_shared<BPlusNode<T>>(this->order, true);
                // Copy the keys from the middle to the end of the node to the new node
                new_leaf->keys.assign(node->keys.begin() + mid, node->keys.end());
                // Remove the keys from the middle to the end of the node (by resizing the vector)
                node->keys.resize(mid); 

                // The new node should be inserted after the current node
                new_leaf->next = node->next;
                node->next = new_leaf;

                new_leaf->parent = node->parent;

                // The first key of the new leaf is promoted to the parent (duplicated)
                T separator = new_leaf->keys.front();
                insertIntoParent(node, separator, new_leaf);
            } else {
                // Internal node

                std::shared_ptr<BPlusNode<T>> new_internal = std::make_shared<BPlusNode<T>>(this->order, false);
                T mid_key = node->keys[mid];
                // Move keys AFTER the promoted middle key (i.e., from mid+1 to end)
                new_internal->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
                node->keys.resize(mid);  // Retain keys before the promoted one

                // Move children corresponding to those keys
                new_internal->children.assign(node->children.begin() + mid + 1, node->children.end());
                node->children.resize(mid + 1); // Retain children for keys before and including mid

                new_internal->parent = node->parent;
                for (auto& child : new_internal->children) {
                    child->parent = new_internal;
                }

                insertIntoParent(node, mid_key, new_internal);
            }

        }

        void insertIntoParent(std::shared_ptr<BPlusNode<T>> node, T key, std::shared_ptr<BPlusNode<T>> new_node) {
            if (!node->parent) {
                // Make new root

                std::shared_ptr<BPlusNode<T>> new_root = std::make_shared<BPlusNode<T>>(this->order, false);
                new_root->keys.push_back(key);
                new_root->children.push_back(node);
                new_root->children.push_back(new_node);
                root = new_root;

                node->parent = root;
                new_node->parent = root;
                return;
            } else {
                // Insert key into parent node
                std::shared_ptr<BPlusNode<T>> parent = node->parent;
                size_t index = std::lower_bound(parent->keys.begin(), parent->keys.end(), key) - parent->keys.begin();

                parent->keys.insert(parent->keys.begin() + index, key);
                parent->children.insert(parent->children.begin() + index + 1, new_node);

                new_node->parent = parent;

                if (parent->is_full()) {
                    split(parent);
                }
            }

        }


    public:

        BPlusTree(size_t order = DEFAULT_ORDER) : order(order) {
            root = std::make_shared<BPlusNode<T>>(order, true);
        }

        void insert(T key) {
            insertHelper(root, key);
        }

        void printLevelOrder() const {
            if (!root) return;
        
            std::queue<std::shared_ptr<BPlusNode<T>>> q;
            q.push(root);
            int level = 0;
        
            while (!q.empty()) {
                int size = q.size();
                std::cout << "Level " << level++ << ": ";
        
                for (int i = 0; i < size; ++i) {
                    auto node = q.front(); q.pop();
        
                    std::cout << "[";
                    for (size_t j = 0; j < node->keys.size(); ++j) {
                        std::cout << node->keys[j];
                        if (j < node->keys.size() - 1) std::cout << ",";
                    }
                    std::cout << "] ";
        
                    if (!node->is_leaf) {
                        for (const auto& child : node->children) {
                            q.push(child);
                        }
                    }
                }
                std::cout << "\n";
            }
        }

        void printLeaves() const {
            // Go to leftmost leaf
            auto node = root;
            while (node && !node->is_leaf) {
                node = node->children.front();
            }
        
            std::cout << "Leaf Level: ";
            while (node) {
                std::cout << "[";
                for (size_t i = 0; i < node->keys.size(); ++i) {
                    std::cout << node->keys[i];
                    if (i < node->keys.size() - 1) std::cout << ",";
                }
                std::cout << "] ";
                node = node->next;
            }
            std::cout << "\n";
        }

};


#endif // B_PLUS_TREE_H