#include "gtest/gtest.h"
#include "../src/BinaryTree/TreeNode.h"
#include "../src/BinaryTree/BinaryTree.h"


TEST(BinaryTreeTest, InsertAndFind) {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(15);

    EXPECT_NE(tree.find(5), nullptr);
    EXPECT_NE(tree.find(15), nullptr);
    EXPECT_EQ(tree.find(42), nullptr);
}

TEST(BinaryTreeTest, Remove) {


    /*
    * Tree should have following structure:
    *
    *    5
    *      \  
    *       \
    *        \
    *        15
    *       /  \
    *      10  20
    *            \
    *             25
    *               \
    *               30
    *                \
    *                 .
    *                  . 
    *                   .
    *                    \
    *                    100
    */
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(15);
    tree.insert(10);
    tree.insert(20);
    tree.insert(25);
    tree.insert(30);
    tree.insert(35);
    tree.insert(40);
    tree.insert(45);
    tree.insert(50);
    tree.insert(55);
    tree.insert(60);
    tree.insert(65);
    tree.insert(70);
    tree.insert(75);
    tree.insert(80);
    tree.insert(85);
    tree.insert(90);
    tree.insert(95);
    tree.insert(100);


    // Remove root; this is the case where there is only one child, so the
    // root should just be replace with the right branch
    tree.remove(5);

    /*
    * Tree should now have following structure:
    *
    *        15
    *       /  \
    *      10  20
    *            \
    *             25
    *               \
    *               30
    *                \
    *                 .
    *                  . 
    *                   .
    *                    \
    *                    100
    */


    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_EQ(tree.find(10), tree.find(15)->left.get());
    EXPECT_EQ(tree.find(20), tree.find(15)->right.get());


    // Remove a node with two children; in this case, the root should be replaced
    // with the smallest value in the right subtree
    tree.remove(15);

    /*
    * Tree should now have following structure:
    *
    *        20
    *       /  \
    *      10  25
    *            \
    *             20
    *               \
    *               35
    *                \
    *                 .
    *                  . 
    *                   .
    *                    \
    *                    100
    */

    EXPECT_EQ(tree.find(15), nullptr);
    EXPECT_EQ(tree.find(10), tree.find(20)->left.get());
    EXPECT_EQ(tree.find(25), tree.find(20)->right.get());


    // Remove a leaf node
    tree.remove(10);
    EXPECT_EQ(tree.find(10), nullptr);
    // Tree should now be completely degenerate; i.e. a linked list
    EXPECT_EQ(tree.height(), tree.size());
}

TEST(BinaryTreeTest, Balance) {


    /*
    * Tree should have following structure:
    *
    *    5
    *      \  
    *       \
    *        \
    *        15
    *       /  \
    *      10  20
    *            \
    *             25
    *               \
    *               30
    *                \
    *                 .
    *                  . 
    *                   .
    *                    \
    *                    100
    */
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(15);
    tree.insert(10);
    tree.insert(20);
    tree.insert(25);
    tree.insert(30);
    tree.insert(35);
    tree.insert(40);
    tree.insert(45);
    tree.insert(50);
    tree.insert(55);
    tree.insert(60);
    tree.insert(65);
    tree.insert(70);
    tree.insert(75);
    tree.insert(80);
    tree.insert(85);
    tree.insert(90);
    tree.insert(95);
    tree.insert(100);

    EXPECT_EQ(tree.height(), static_cast<size_t>(19));
    EXPECT_EQ(tree.size(), static_cast<size_t>(20));

    tree.balance();

    EXPECT_EQ(tree.height(), static_cast<size_t>(5));
    EXPECT_EQ(tree.size(), static_cast<size_t>(20));
    EXPECT_EQ(tree.find(75), tree.find(50)->right.get());
    EXPECT_EQ(tree.find(25), tree.find(50)->left.get());
    EXPECT_EQ(tree.find(90), tree.find(75)->right.get());
    EXPECT_EQ(tree.find(60), tree.find(75)->left.get());
    EXPECT_EQ(tree.find(35), tree.find(25)->right.get());
}
