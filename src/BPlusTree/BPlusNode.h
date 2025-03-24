#ifndef B_PLUS_NODE_H
#define B_PLUS_NODE_H

#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
#include <utility>
#include <cassert>

#include "../Comparable.h"

template <Comparable T>
class BPlusNode {

    private:
        
        size_t order;
    
    public:

        std::vector<T> keys;
        std::vector<std::shared_ptr<BPlusNode<T>>> children;
        std::shared_ptr<BPlusNode<T>> parent;
        std::shared_ptr<BPlusNode<T>> next;
        bool is_leaf;

        BPlusNode(size_t order, bool is_leaf) : order(order), is_leaf(is_leaf) {
            keys.reserve(order);
            children.reserve(order + 1);
        }

        BPlusNode(size_t order, bool is_leaf, std::shared_ptr<BPlusNode<T>> parent) : order(order), is_leaf(is_leaf), parent(parent) {
            keys.reserve(order);
            children.reserve(order + 1);
        }

        bool is_full() {
            return keys.size() == order;
        }


        void insert_key(T key) {
            keys.push_back(key);
            std::sort(keys.begin(), keys.end());
        }

        void insert_child(std::shared_ptr<BPlusNode<T>> child) {
            children.push_back(child);
            std::sort(children.begin(), children.end());
        }

        void remove_key(T key) {
            auto it = std::find(keys.begin(), keys.end(), key);
            if (it != keys.end()) {
                keys.erase(it);
            }
        }

        void remove_child(std::shared_ptr<BPlusNode<T>> child) {
            auto it = std::find(children.begin(), children.end(), child);
            if (it != children.end()) {
                children.erase(it);
            }
        }

        void set_parent(std::shared_ptr<BPlusNode<T>> parent) {
            this->parent = parent;
        }

        void print_node() {
            std::cout << "Keys: ";
            for (auto key : keys) {
                std::cout << key << " ";
            }
            std::cout << std::endl;
        }

        void print_children() {
            std::cout << "Children: ";
            for (auto child : children) {
                std::cout << child << " ";
            }
            std::cout << std::endl;
        }

        void print_node_children() {
            print_node();
            print_children();
        }

        std::shared_ptr<BPlusNode<T>> find_child(T key) {
            auto index = std::upper_bound(keys.begin(), keys.end(), key) - keys.begin();
            if (index == 0) {
                return children[0];
            } else {
                return children[index];
            }
        }

};


#endif // B_PLUS_NODE_H