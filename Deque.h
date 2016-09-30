#pragma once
#include <vector>
#include <iostream>
template <typename T> class Deque{
public:

	std::vector<T> myvector;

//default constructor
	Deque();

//desctructor
	~Deque();

/*
Method: assign
Parameters: int i, T value
Description: Sets the value at index i of the Double Ended Queue.
Returns: void
*/
	void assign(int i, T value);

/*
Method: push_back
Parameters: template T value
Description: adds T variable value to the back of the deque.
Returns: void
*/
	void push_back(T value);

/*
Method: push_front()
Parameters: template T value
Description: adds T variable value to the front of the deque.
Returns: void
*/

	void push_front(T value);

/*
Method: pop_back()
Parameters: void
Description: removes the back most element in the deque.
Returns: void
*/
	void pop_back();

/*
Method: pop_front()
Parameters: void
Description: removes the front most element in the deque.
Returns: void
*/
	void pop_front();


/*
Method: size()
Parameters: void
Description: calls vector's size method. 
Returns: returns the size of the deque.
*/
	int size();

/*
Method: test()
Parameters: void
Description: public method used for testing purposes only. iterates
	through the Deque from the front to back and prints the element.
Returns: void
*/
	void test();


private:
	T temp;
	

};
