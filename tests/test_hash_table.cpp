#include "gtest/gtest.h"
#include "../src/HashTable/Hashable.h"
#include "../src/HashTable/HashTable.h"

TEST(HashTableTest, InsertAndFind) {
    HashTable<std::string> table;
    table.insert("Hello");
    table.insert("World");
    table.insert("Foo");
    table.insert("Bar");

    EXPECT_TRUE(table.contains("Hello"));
    EXPECT_TRUE(table.contains("World"));
    EXPECT_TRUE(table.contains("Foo"));
    EXPECT_TRUE(table.contains("Bar"));
    EXPECT_FALSE(table.contains("Moo"));

    EXPECT_EQ(table.num_buckets(), static_cast<size_t>(10));

    table.insert("Moo");
    table.insert("Cow");
    table.insert("How");
    table.insert("Now");
    table.insert("Brown");

    EXPECT_EQ(table.num_buckets(), static_cast<size_t>(20));
}

TEST(HashTableTest, Remove) {
    HashTable<std::string> table;
    table.insert("Hello");
    table.insert("World");
    table.insert("Foo");
    table.insert("Bar");

    table.remove("Hello");
    EXPECT_FALSE(table.contains("Hello"));
    EXPECT_TRUE(table.contains("World"));
    EXPECT_TRUE(table.contains("Foo"));
    EXPECT_TRUE(table.contains("Bar"));

    table.remove("World");
    EXPECT_FALSE(table.contains("World"));
    EXPECT_TRUE(table.contains("Foo"));
    EXPECT_TRUE(table.contains("Bar"));

    table.remove("Foo");
    EXPECT_FALSE(table.contains("Foo"));
    EXPECT_TRUE(table.contains("Bar"));


    EXPECT_EQ(table.num_buckets(), static_cast<size_t>(5));
}