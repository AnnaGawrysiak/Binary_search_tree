#pragma once
# include <memory>
# include <sstream>
#include <iostream>
#include "Node.h"

template <typename T>
class Node
{
public:
	T value;
	std::shared_ptr<Node<T>> child_left;
	std::shared_ptr<Node<T>>child_right;
	Node(T const& data) : child_left(nullptr), child_right(nullptr), value(data) {};
	bool operator < (const Node& rhs)
	{
		return value < rhs.value; // read access violation. rhs was nullptr.

	}
	
	bool operator==(const Node& rhs)
	{
		if (value == rhs.value)
			return true;

		return false;
	}

	Node() {};

	friend std::ostream& operator<<(std::ostream& os, const Node<T>& shade);
};

