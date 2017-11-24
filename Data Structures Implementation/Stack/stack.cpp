#include "stack.h"
#include <new>
#include <stdexcept>
#include <iostream>
using std::runtime_error;
using std::cout;
using std::endl;
Stack::Stack(int init_size)
{
	cout << "I'm inside the constructor\n";
	arr = new int[init_size];
	capacity = init_size;
	count = 0;
}
Stack::Stack(const Stack &stack)
{
	cout << "I'm inside the copy-constructor\n";
	arr = new int[stack.capacity];
	memcpy(arr, stack.arr, sizeof(int) * stack.size());
	count = stack.count;
	capacity = stack.capacity;
}
Stack::~Stack()
{
	cout << "I'm inside the destructor" << endl;
	delete[] arr;
}
void Stack::push(int number)
{
	if (count < capacity)
	{
		arr[count] = number;
		++count;
	}
	else
		throw runtime_error("Stack::push - no memory");
}
int Stack::top()
{
	if (count > 0)
		return arr[count - 1];
	else
		throw runtime_error("Stack::top - no elements");
}
int Stack::pop()
{
	if (count > 0){
		int tmp = top();
		arr[--count] = 0;
		return tmp;
	}
	else
		throw runtime_error("Stack::pop - no elements");
}
int Stack::size() const
{
	return count;
}