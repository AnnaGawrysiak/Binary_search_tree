#include "Node.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& shade)
{
	os << shade.value;
	return os;
}