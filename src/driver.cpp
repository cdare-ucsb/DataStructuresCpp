#include "BinaryTree/Comparable.h"
#include "BinaryTree/TreeNode.h"
#include "BinaryTree/BinaryTree.h"
#include <iostream>
#include <vector>


int main(int argc, char *argv[]) {

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


    std::cout << "ORIGINAL TREE" << std::endl;
    std::cout << "------------------------\n\n\n";

    tree.print();
    std::cout << std::endl;
    
    std::cout << "Height: " << tree.height() << std::endl;
    std::cout << "Size: " << tree.size() << std::endl;



    // tree.remove(5);

    // std::cout << "\n\n\nAFTER REMOVE(5)" << std::endl;
    // std::cout << "------------------------\n\n\n";

    // tree.print();
    // std::cout << std::endl;

    // std::cout << "Height: " << tree.height() << std::endl;
    // std::cout << "Size: " << tree.size() << std::endl;

    // std::cout << std::endl;

    // tree.remove(15);

    // std::cout << "\n\n\nAFTER REMOVE(15)" << std::endl;
    // std::cout << "------------------------\n\n\n";

    // tree.print();
    // std::cout << std::endl;

    // std::cout << "Height: " << tree.height() << std::endl;
    // std::cout << "Size: " << tree.size() << std::endl;

    // std::cout << std::endl;

    // tree.remove(10);

    // std::cout << "\n\n\nAFTER REMOVE(10)" << std::endl;
    // std::cout << "------------------------\n\n\n";

    // tree.print();
    // std::cout << std::endl;

    // std::cout << "Height: " << tree.height() << std::endl;
    // std::cout << "Size: " << tree.size() << std::endl;

    // std::cout << std::endl;

    tree.balance();

    std::cout << "\n\n\nAFTER BALANCE" << std::endl;
    std::cout << "------------------------\n\n\n";

    tree.print();
    std::cout << std::endl;

    std::cout << "Height: " << tree.height() << std::endl;
    std::cout << "Size: " << tree.size() << std::endl;

    return 0;
}