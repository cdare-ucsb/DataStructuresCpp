#include "gtest/gtest.h"
#include "../src/PrefixTrie/TrieNode.h"
#include "../src/PrefixTrie/Trie.h"


TEST(PrefixTrieTest, InsertAndFind) {
    Trie trie;
    trie.insert("Hello");
    trie.insert("World");
    trie.insert("Foo");
    trie.insert("Bar");

    EXPECT_TRUE(trie.hasWord("Hello"));
    EXPECT_TRUE(trie.hasWord("World"));
    EXPECT_TRUE(trie.hasWord("Foo"));
    EXPECT_TRUE(trie.hasWord("Bar"));
    EXPECT_FALSE(trie.hasWord("Moo"));

    EXPECT_TRUE(trie.hasPrefix("He"));
    EXPECT_TRUE(trie.hasPrefix("Wor"));
    EXPECT_TRUE(trie.hasPrefix("F"));
    EXPECT_TRUE(trie.hasPrefix("Ba"));
    EXPECT_FALSE(trie.hasPrefix("M"));
}


TEST(PrefixTrieTest, Remove) {
    Trie trie;
    trie.insert("Hello");
    trie.insert("Hell");
    trie.insert("World");
    trie.insert("Foo");
    trie.insert("Fool");
    trie.insert("Bar");

    EXPECT_EQ(trie.countWords(), static_cast<size_t>(6));

    trie.remove("Hell");
    EXPECT_FALSE(trie.hasWord("Hell"));
    EXPECT_TRUE(trie.hasWord("Hello"));
    EXPECT_TRUE(trie.hasWord("World"));
    EXPECT_TRUE(trie.hasWord("Foo"));
    EXPECT_TRUE(trie.hasWord("Fool"));
    EXPECT_TRUE(trie.hasWord("Bar"));
    EXPECT_TRUE(trie.hasPrefix("Hell"));

    EXPECT_EQ(trie.countWords(), static_cast<size_t>(5));

    trie.remove("Fool");
    EXPECT_FALSE(trie.hasWord("Fool"));
    EXPECT_TRUE(trie.hasWord("Hello"));
    EXPECT_TRUE(trie.hasWord("World"));
    EXPECT_TRUE(trie.hasWord("Foo"));
    EXPECT_TRUE(trie.hasWord("Bar"));
    EXPECT_FALSE(trie.hasPrefix("Fool"));
    EXPECT_TRUE(trie.hasPrefix("Foo"));

    EXPECT_EQ(trie.countWords(), static_cast<size_t>(4));
}