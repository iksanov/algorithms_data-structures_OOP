#pragma once
class Stack
{
public:
	Stack(int initial_size = 100);
	Stack(const Stack &stack);
	~Stack();
	void push(int num);
	int pop();
	int top();
	int size() const;
private:
	int* arr;
	int capacity;
	int count;
};