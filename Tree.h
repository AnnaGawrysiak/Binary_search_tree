#pragma once
#include <memory>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include "Node.h"
#include "DefaultValue.h"

template <typename T>
class Tree
{
private:
	std::shared_ptr<Node<T>> root;
	int depth; 
public:
	Tree();
	std::shared_ptr<Node<T>> Create_New_Node(T val);
	void insert(T key);
	std::shared_ptr<Node<T>> search(T key);
	T find_min();
	T find_max();
	void display();
	int getDepth();
	void helper_inserter(std::vector<std::vector<std::string>>& ans, std::shared_ptr<Node<T>> node, int level, int left, int right);
	//void DFS(const Node<T>& source);
	void DFS(T key);
	void BFS(T key);
};

template<typename T>
Tree<T>::Tree()
{
	root = nullptr;
}

template <typename T>
std::shared_ptr<Node<T>> Tree<T>::Create_New_Node(T val)
{
	std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>();

	node->value = val;
	node->child_left = nullptr;
	node->child_right = nullptr;

	return node;
}

template <typename T>
void Tree<T>::insert(T key)
{
	if (root == nullptr)
	{
		root = Create_New_Node(key);
		return;
	}
	
	// start with the root node
	std::shared_ptr<Node<T>> curr = root;
	std::shared_ptr<Node<T>> parent = root; 

	while (curr != nullptr) //traversing the tree to find the insertion point
	{
		parent = curr;

		if (key == curr->value)
			return;

		else if (key < curr->value)
		{
			curr = curr->child_left;
		}
		
		else if(key > curr->value)
		{
			curr = curr->child_right;
		}
	}

	if (key < parent->value) 
		parent->child_left = Create_New_Node(key);
	else 
		parent->child_right = Create_New_Node(key);
}

template <typename T>
std::shared_ptr<Node<T>> Tree<T>::search(T key) // should be recursively: void search(std::shared_ptr<Node<T>> root,int val)?
{
	std::shared_ptr<Node<T>> current = root;

	while (current)
	{
		if (current->value == key)
			return current;
		else if (current->value < key)
		{
			current = current->child_right;
		}
		else
		{
			current = current->child_left;
		}

	}

		return nullptr;
}

template <typename T>
T Tree<T>::find_min()
{
	std::shared_ptr<Node<T>> curr = root;

	while (curr->child_left != nullptr)
	{
		curr = curr->child_left;
	}

	return curr->value;
}

template <typename T>
T Tree<T>::find_max()
{
	std::shared_ptr<Node<T>> curr = root;

	while (curr->child_right != nullptr)
	{
		curr = curr->child_right;
	}

	return curr->value;
}


template<typename T>
void Tree<T>::display()
{
	if (root == nullptr) 
		return;
	
	// create table of empty strings "" based on the tree height/width

	int depth = getDepth();
	
	//int max_nr_of_children = pow(2, (depth - 1)); // root to poziom 1
	//int nr_of_spaces = max_nr_of_children - 1;
	//int width = max_nr_of_children + nr_of_spaces;
	
	int width = pow(2, depth - 1) + pow(2, depth - 1) - 1;

	std::vector<std::string> row(width, "");
	for (auto item : row)
	{
		std::cout << "row: " << item << std::endl;
	}
	std::vector<std::vector<std::string>> ans(depth, row);

	// traverse the tree and fill in table values for non-nullptr nodes
	// always put the value in the middle of the range.

	std::shared_ptr<Node<T>> curr = root;
	helper_inserter(ans, curr, 0, 0, width -1);

	// Displaying the 2D vector
	for (unsigned int i = 0; i < ans.size(); i++) 
	{
		for (unsigned int j = 0; j < ans[i].size(); j++)
		{
			std::cout << std::setw(8) << ans[i][j] << " ";
		}
		std::cout << std::endl;
	}

}
template <typename T>
void Tree<T>::helper_inserter(std::vector<std::vector<std::string>>& ans, std::shared_ptr<Node<T>> node, int level, int left, int right)
{
	if (!node) return;

	int mid = (left + right) / 2;

	if constexpr (std::is_same_v<T, std::string>)
		ans[level][mid] = node->value;
	else
		ans [level][mid] = std::to_string(node->value);


	if (node->child_left)
	{
		helper_inserter(ans, node->child_left, level + 1, left, mid - 1);
	}

	if (node->child_right)
	{
		helper_inserter(ans, node->child_right, level + 1, mid+1, right);
	}

}

// Iterative function to calculate the height of a given binary tree
// by doing level order traversal on the tree

template<typename T>
int Tree<T>::getDepth()
{
	if (root == nullptr) // kod bledu
		return -1;

	std::shared_ptr<Node<T>> source = root;
	std::queue<std::shared_ptr<Node<T>> > myqueue;
	myqueue.push(source);
	// whenever an item touches a queue we mark it as seen
	std::map<std::shared_ptr<Node<T>>, bool> discovered;
	discovered[source] = true;
	int levels = 0;

	while (!myqueue.empty())
	{
		// calculate the total number of nodes at the current level
		int size = myqueue.size();

		while(size--)
		{
			std::shared_ptr<Node<T>> curr = myqueue.front();
			myqueue.pop();

			if (curr->child_left != nullptr && discovered[curr->child_left] == false)
			{
				// mark it as discovered and enqueue it
				discovered[curr->child_left] = true;
				myqueue.push(curr->child_left);
			}

			if (curr->child_right != nullptr && discovered[curr->child_right] == false)
			{
				discovered[curr->child_right] = true;
				myqueue.push(curr->child_right);
			}
		}

		levels++;
	}
	

	return levels;
}

template<typename T>
void Tree<T>::DFS(T key)
{
	std::shared_ptr<Node<T>> source = search(key);
	std::stack<std::shared_ptr<Node<T>> > mystack;
	mystack.push(source);

	std::map<std::shared_ptr<Node<T>>, bool> discovered; // insert default value: false
	//std::map<T, DefaultFalse> discovered;
	
	while (!mystack.empty())
	{
		std::shared_ptr<Node<T>> curr = mystack.top();
		mystack.pop();

		// if the vertex is already discovered yet,
	   // ignore it
		if(discovered[curr])
			continue;

		discovered[curr] = true;
		std::cout << curr->value << " ";
		// add undiscovered children of the curr
		if(curr->child_left != nullptr && discovered[curr->child_left] == false)
			mystack.push(curr->child_left);

		if(curr->child_right != nullptr && discovered[curr->child_right] == false)
			mystack.push(curr->child_right);

	}

}

template<typename T>
void Tree<T>::BFS(T key)
{
	std::shared_ptr<Node<T>> source = search(key);
	std::queue<std::shared_ptr<Node<T>> > myqueue;
	myqueue.push(source);
	// whenever an item touches a queue we mark it as seen
	std::map<std::shared_ptr<Node<T>>, bool> discovered;
	discovered[source] = true;

	while (!myqueue.empty())
	{
		std::shared_ptr<Node<T>> curr = myqueue.front();
		myqueue.pop();
		std::cout << curr->value << " ";

		// add undiscovered children of the curr
		if (curr->child_left != nullptr && discovered[curr->child_left] == false)
		{
			// mark it as discovered and enqueue it
			discovered[curr->child_left] = true;
			myqueue.push(curr->child_left);
		}
			
		if (curr->child_right != nullptr && discovered[curr->child_right] == false)
		{
			discovered[curr->child_right] = true;
			myqueue.push(curr->child_right);
		}	
	}
}