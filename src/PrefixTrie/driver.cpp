
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "TrieNode.h"
#include "Trie.h"

int main() {

    Trie trie;
    trie.insert("Hello");
    trie.insert("World");
    trie.insert("Foo");
    trie.insert("Bar");
    trie.insert("Hell");
    trie.insert("Fool");

    std::cout << "ORIGINAL TRIE:" << std::endl;
    std::cout << "-----------------------------------\n\n\n";

    trie.print();

    std::vector<std::string> words = trie.getWordsWithPrefix("H");
    std::cout << "Words with prefix 'H':" << std::endl;
    for (const std::string& word : words) {
        std::cout << word << std::endl;
    }

    std::cout << "\n\n\n";

    trie.remove("Hell");
    trie.remove("Fool");

    std::cout << "TRIE AFTER REMOVING 'Hell' and 'Fool':" << std::endl;
    std::cout << "-----------------------------------\n\n\n";

    trie.print();
}
