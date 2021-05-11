#include <iostream>
#include <vector>
#include "Node.h"
#include "Tree.h"

int main()
{ 

    Tree<Node<int>> my_tree;

    std::vector<int> numbers = { 1, 20, 32, -4, 5 };

    for (const auto& item : numbers)
    {
        my_tree.insert(item);
    }

    my_tree.display();

    return 0;
}

