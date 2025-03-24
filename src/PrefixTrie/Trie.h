#ifndef TRIE_H
#define TRIE_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "TrieNode.h"

class Trie {

    private:
        std::shared_ptr<TrieNode> root;


        std::string toLower(const std::string& word) {
            std::string lower = word;
            std::transform(lower.begin(), lower.end(), lower.begin(),
                            [](unsigned char c) { 
                                return std::tolower(c);
                            }
                        );

            return lower;
        }

        bool removeHelper(std::shared_ptr<TrieNode> node, const std::string& word, size_t depth) {

            if (!node) {
                return false;
            }

            if (depth == word.size()) {
                if (!node->is_end() ) return false; // Word not in trie

                node->unset_end(); // Since we no longer want this word in our trie, there should not be an end of word marker here.

                return node->is_empty(); // If the node doesnt have any children, we can remove it.
            }

            // if we are not at the last character of the word, we need to keep
            // traversing the trie.
            std::shared_ptr<TrieNode> child = node->get_child(word[depth]);

            if (!child) {
                return false; // The word is not in the trie.
            }
            
            bool should_delete_child = removeHelper(child, word, depth + 1);

            if (should_delete_child) {
                node->remove_child(word[depth]); // Remove the child node from the trie.
                return node->is_empty() && !node->is_end(); // If the node has no children and not the end of another word, we can remove it.
            }

            return false;

        }


        std::shared_ptr<TrieNode> findNodeForPrefix(const std::string& prefix) const {
            std::shared_ptr<TrieNode> current = root;

            for (char c : prefix) {
                if (!current->has_child(c)) {
                    return nullptr;
                }
                current = current->get_child(c);
            }

            return current;
        }

        void getWordsStartingFromNode(std::shared_ptr<TrieNode> node, std::vector<std::string> &words, std::string current_word) const {
            if (!node) {
                return;
            }

            if (node->is_end()) {
                words.push_back(current_word);
            }

            for (char c = 'a'; c <= 'z'; c++) {
                std::shared_ptr<TrieNode> child = node->get_child(c);
                if (child) {
                    getWordsStartingFromNode(child, words, current_word + c);
                }
            }
        }



    public:

        Trie() : root(std::make_shared<TrieNode>()) {}
        ~Trie() = default;

        void insert(const std::string& word) {

            std::string lower = toLower(word);

            // When inserting a word into the trie, always start at the root
            // node. 
            std::shared_ptr<TrieNode> current = root;

            // For each character in the word, check if the current node has a
            // child node with that character. 
            for (char c : lower) {
                if (!current->has_child(c) ) {
                    current->set_child(c, std::make_shared<TrieNode>());
                    
                } 
                current = current->get_child(c);
            }

            current->set_end();
        }

        bool hasWord(const std::string& word) {

            std::string lower = toLower(word);

            std::shared_ptr<TrieNode> current = root;

            for (char c : lower) {
                if (!current->has_child(c)) {
                    return false;
                }
                current = current->get_child(c);
            }

            return current->is_end();
        }

        bool hasPrefix(const std::string& prefix) {

            std::string lower = toLower(prefix);

            std::shared_ptr<TrieNode> current = root;

            for (char c : lower) {
                if (!current->has_child(c)) {
                    return false;
                }
                current = current->get_child(c);
            }

            return true;
        }

        size_t countWords() {
            return root->count_end_word_children();
        }

        std::vector<std::string> getWordsWithPrefix(const std::string& prefix){

            std::string lower = toLower(prefix);

            std::vector<std::string> words;
            std::shared_ptr<TrieNode> node = findNodeForPrefix(lower);

            if (node) {
                getWordsStartingFromNode(node, words, lower);
            }

            return words;
        }


        bool remove(const std::string& word) {
            std::string lower = toLower(word);

            return removeHelper(root, lower, 0);
        }

        void print() {
            root->print_from_level();
        }

};

#endif // TRIE_H