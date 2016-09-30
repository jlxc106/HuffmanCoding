/*
Written by Jay Lim
Last Edited: September 30, 2016
File: Deque.cpp
Note: implement additional constructors to set the initial size
	and content of the deque.
*/
#include "Deque.h"

template <typename T> 
Deque<T>::Deque(){
	
}

template <typename T> 
Deque<T>::~Deque(){

}

template <typename T> 
void Deque<T>::assign(int i, T value){
	myvector.at(i) = value;
}

template <typename T> 
void Deque<T>::push_back(T obj){
	myvector.push_back(obj);
//	std::cout<< obj<< std::endl;
}

template <typename T> 
void Deque<T>::push_front(T obj){
	myvector.insert(myvector.begin(), obj);
}

template <typename T> 
void Deque<T>::pop_back(){
//	std::cout<< myvector.back() << std::endl;
	myvector.pop_back();
}

template <typename T> 
void Deque<T>::pop_front(){
	myvector.erase(myvector.begin());
}

template <typename T> 
int Deque<T>::size(){
	return myvector.size();
}

template <typename T> 
void Deque<T>::test(){

}


int main(){

Deque<int> D;
D.push_back(11);
D.push_back(12);
D.push_front(123);
D.push_front(9);
for(int i=9; i >= 0; i--)
	D.push_front(i);
D.push_back(1111);

std::cout << "size is: "<<D.size() << std::endl;
std::cout << "popping...." <<std::endl;
while(D.size() > 0)
	D.pop_back();
return 0;

}

