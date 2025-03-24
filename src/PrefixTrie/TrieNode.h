#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>

class TrieNode {

    private:
        std::vector<std::shared_ptr<TrieNode>> children;
        bool is_end_of_word;

    public:
        TrieNode() : children(26, nullptr), is_end_of_word(false) {}

        bool has_child(char c) const {
            return children[c - 'a'] != nullptr;
        }

        bool is_empty() {
            return std::all_of(children.begin(), children.end(),
                                [](const std::shared_ptr<TrieNode>& child) {  // Lambda function
                                    return child == nullptr;
                                }
                            ); 
        }

        std::shared_ptr<TrieNode> get_child(char c) const {
            return children[c - 'a'];
        }

        void set_child(char c, std::shared_ptr<TrieNode> node) {
            children[c - 'a'] = node;
        }

        void remove_child(char c) {
            int idx = c - 'a';
            children[idx] = nullptr;
        }

        size_t count_end_word_children() {
            size_t sum = (is_end_of_word) ? 1 : 0;

            for (auto& child : children) {
                if (child) {
                    sum += child->count_end_word_children();
                }
            }

            return sum;
        }

        bool is_end() const {
            return is_end_of_word;
        }

        void set_end() {
            is_end_of_word = true;
        }

        void unset_end() {
            is_end_of_word = false;
        }

        

        void print_from_level(int level=0, char ch='*') {
            for (int i = 25; i >= 0; --i) {
                if (this->children[i]) {
                    children[i]->print_from_level(level + 1, 'a' + i);
                }
            }

            // Print current node
            for (int i = 0; i < level; ++i) std::cout << "    ";
            std::cout << ch;
            if (this->is_end_of_word) std::cout << "*";
            std::cout << "\n";
        }

        


};

#endif // TRIE_NODE_H