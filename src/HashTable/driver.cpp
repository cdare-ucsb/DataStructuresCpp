#include "Hashable.h"
#include "HashTable.h"


#include <iostream>
#include <vector>
#include <string>
#include <concepts>
#include <functional> // for std::hash

int main() {


    HashTable<std::string> table;
    table.insert("Hello");
    table.insert("World");
    table.insert("Foo");
    table.insert("Bar");

    std::cout << "ORIGINAL TABLE:" << std::endl;
    std::cout << "-----------------------------------\n\n\n";

    table.print();



    table.insert("Moo");
    table.insert("Cow");
    table.insert("How");
    table.insert("Now");
    table.insert("Brown");
    table.insert("Cow");

    std::cout << "\n\n\nAFTER ADDITION OF 6 ELEMENTS:" << std::endl;
    std::cout << "-----------------------------------\n\n\n";

    table.print();


    HashTable<std::string> table2;
    table2.insert("Hello");
    table2.insert("World");
    table2.insert("Foo");
    table2.insert("Bar");

    table2.remove("Hello");
    table2.remove("World");
    table2.remove("Foo");

    std::cout << "\n\n\nAFTER REMOVAL OF 2 ELEMENTS:" << std::endl;
    std::cout << "-----------------------------------\n\n\n";

    table2.print();



    return 0;
}