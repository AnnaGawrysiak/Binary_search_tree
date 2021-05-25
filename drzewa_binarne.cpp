#include <iostream>
#include <vector>
#include "Node.h"
#include "Tree.h"

int main()
{ 

    Tree<int> my_tree;

    std::vector<int> numbers = { 1, 20, 32, -4, 5, 10, 18, -11 };

    for (const auto& item : numbers)
    {
        my_tree.insert(item);
    }

    int value = 5;
   // my_tree.display();
    std::cout << "Min value: " << my_tree.find_min() << std::endl;
    std::cout << "Max value: " << my_tree.find_max() << std::endl;
    std::cout << "Searched value: " << value << " : " << my_tree.search(value) << std::endl;

    std::shared_ptr<Node<int>> found = my_tree.search(value);

    std::cout << "Depth First Search: " << std::endl;
    my_tree.DFS(1);

    return 0;
}

