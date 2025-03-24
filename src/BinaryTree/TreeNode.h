#ifndef TREENODE_H
#define TREENODE_H

#include <memory>
#include <concepts>
#include <vector>
#include <queue>
#include <iostream>
#include "../Comparable.h"



template<Comparable T>
class TreeNode
{
    public:

        T data;
        std::unique_ptr<TreeNode<T>> left;
        std::unique_ptr<TreeNode<T>> right; 

        
        TreeNode(T data) : data(data), left(nullptr), right(nullptr) {}
        ~TreeNode() = default;

        

        void insert(T value) {
            if (this->data < value) {
                if (this->right) {
                    this->right->insert(value);
                } else {
                    this->right = std::make_unique<TreeNode<T>>(value);
                }
            } else {
                if (this->left) {
                    this->left->insert(value);
                } else {
                    this->left = std::make_unique<TreeNode<T>>(value);
                }
            }
        }


        TreeNode<T>* find(T value) {
            if (this->data == value ) {
                return this;
            }
            else if (this->data < value) {
                if (this->right) {
                    return this->right->find(value);
                }
                else return nullptr;
            }
            else {
                if (this->left) {
                    return this->left->find(value);
                }
                else return nullptr;
            }
        }

        void printInOrder() {
            if (this->left) {
                this->left->printInOrder();
            }
            std::cout << this->data << " ";
            if (this->right) {
                this->right->printInOrder();
            }
        }
        void printPreOrder() {
            if (this->left) {
                this->left->printPreOrder();
            }
            if (this->right) {
                this->right->printPreOrder();
            }
            std::cout << this->data << " ";
        }
        void printPostOrder() {
            std::cout << this->data << " ";
            if (this->left) {
                this->left->printPostOrder();
            }
            if (this->right) {
                this->right->printPostOrder();
            }
        }
        void printLevelOrder() {
            std::queue<TreeNode<T>*> q;
            q.push(this);

            while (!q.empty()) {
                TreeNode<T>* current = q.front();
                q.pop();
                std::cout << current->data << " ";
                if (current->left) {
                    q.push(current->left.get());
                }
                if (current->right) {
                    q.push(current->right.get());
                }
            }
        }
        void collectInOrder(std::vector<T>& values) {
            if (this->left) {
                this->left->collectInOrder(values);
            }
            values.push_back(this->data);
            if (this->right) {
                this->right->collectInOrder(values);
            }
        }
        void collectPreOrder(std::vector<T>& values) {
            values.push_back(this->data);
            if (this->left) {
                this->left->collectPreOrder(values);
            }
            if (this->right) {
                this->right->collectPreOrder(values);
            }
        }
        void collectPostOrder(std::vector<T>& values) {
            if (this->left) {
                this->left->collectPostOrder(values);
            }
            if (this->right) {
                this->right->collectPostOrder(values);
            }
            values.push_back(this->data);
        }
        void collectLevelOrder(std::vector<T>& values) {
            std::queue<TreeNode<T>*> q;
            q.push(this);

            while (!q.empty()) {
                TreeNode<T>* current = q.front();
                q.pop();
                values.push_back(current->data);
                if (current->left) {
                    q.push(current->left.get());
                }
                if (current->right) {
                    q.push(current->right.get());
                }
            }
        }

        size_t height() {
            size_t leftHeight = 0;
            size_t rightHeight = 0;
            if (this->left) {
                leftHeight = this->left->height();
            }
            if (this->right) {
                rightHeight = this->right->height();
            }
            return 1 + std::max(leftHeight, rightHeight);
        }
        size_t size() {
            size_t leftSize = 0;
            size_t rightSize = 0;
            if (this->left) {
                leftSize = this->left->size();
            }
            if (this->right) {
                rightSize = this->right->size();
            }
            return 1 + leftSize + rightSize;
        }

        void remove(T value, std::unique_ptr<TreeNode<T>>& self) {
            if (this->data < value) {
                /*
                *    Case 1: The value we want to remove is larger than the current node;
                *            Use recursion to remove the value from the right subtree
                */
                if (this->right) {
                    this->right->remove(value, this->right);
                }
            }
            if (this->data > value) {
                /*
                *    Case 2: The value we want to remove is smaller than the current node;
                *            Use recursion to remove the value from the left subtree
                */
                if (this->left) {
                    this->left->remove(value, this->left);
                }
            }
            else {
                /*
                *    Case 3: The value we want to remove is equal to the current node;
                *            Somehow remve the current node — the implementation will vary 
                *            depending on the number of children the current node has.
                */



                if (this->left && this->right) {
                    /*
                    *    Case 3(a): The node has two children. This is the most difficult case.
                    *                We need to find the smallest value in the right subtree and
                    *                replace the current node's value with it, and then remove the
                    *                node with the smallest value in the right subtree.
                    */

                    // Find the smallest value in the right subtree
                    TreeNode<T>* successor_parent = this;
                    std::unique_ptr<TreeNode<T>>* successor = &this->right;
                    while ((*successor)->left) {
                        // Traverse the right subtree to find the smallest value
                        successor_parent = successor->get();
                        successor = &(*successor)->left;
                    }

                    // Swap the data of the current node with the successor
                    this->data = (*successor)->data;

                    // Remove the successor node. Since we know the successor has no left child,
                    // we can simply replace the successor with its
                    // right child (if it exists) or nullptr (if it doesn't).
                    if ((*successor)->right) {
                        // The successor has a right child
                        (*successor) = std::move((*successor)->right);
                    } else {
                        // The successor has no right child
                        successor_parent->left = nullptr;
                    }
                }
                else if (this->left) {
                    /*
                    *    Case 3(b): The node has only a left child. In this case, we can simply
                    *                replace the current node with its left child.
                    */
                    self = std::move(this->left);
                }
                else if (this->right) {
                    /*
                    *   Case 3(c): The node has only a right child. In this case, we can simply
                    *               replace the current node with its right child.
                    */
                    self = std::move(this->right);
                }
                else {
                    /*
                    *   Case 3(d): The node has no children. In this case, we can simply remove
                    *               the current node by setting the pointer to it to nullptr.
                    */
                    self.reset();
                }
                

            }
        }


};

#endif // TREENODE_H
