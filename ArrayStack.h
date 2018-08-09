/// Copyright 2018 <Rafael Neves de Mello Oliveira>

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
/**
* Class ArrayStack
*/
class ArrayStack {
 public:
	ArrayStack();  /// constructor
	explicit ArrayStack(std::size_t max);  /// constructor with parameters
	~ArrayStack();  /// destructor
	void clear();  /// the ArrayStack
	bool full();  /// verify if the ArrayStack is full
	bool empty();  /// verify if the ArrayStack is empty
	void push(const T& data);  // insert a new data to the ArrayStack
	T pop();  /// get a data from the top of the stack
	T& top();  /// get data top by reference
	std::size_t size();  /// gives the actual size of the ArrayStack
	std::size_t max_size();  /// gives the maximum size of the ArrayStack

 private:
	static const auto DEFAULT_SIZE = 10u;
	T* contents;
	int top_;  // variable that mark the top value
	std::size_t max_size_;
};


/// constructor
template<typename T>
ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}
template <typename T>
ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template <typename T>
ArrayStack<T>::~ArrayStack() {
	delete[] contents;
}

template <typename T>
void ArrayStack<T>::clear() {
	top_ = -1;
}

template <typename T>
bool ArrayStack<T>::full() {
	return (top_ == max_size_ - 1);
}

template <typename T>
bool ArrayStack<T>::empty() {
    return (top_ == -1);
}

template <typename T>
void ArrayStack<T>::push(const T& data) {
	if (full()) {
	    throw(std::out_of_range("Stack is full"));
	} else {
		top_ = top_ +1;
		contents[top_] = data;
	}
}
/**
 *  class pop 
 */
template <typename T>
T ArrayStack<T>::pop() {
	if (empty()) {
	    throw(std::out_of_range("Stack is empty"));
	} else {
		top_ = top_ -1;
	}
	return contents[top_ + 1];
}

template <typename T>
T& ArrayStack<T>::top() {
    return contents[top_];
}

template <typename T>
std::size_t ArrayStack<T>::size() {
	return top_ + 1;
}

template <typename T>
std::size_t ArrayStack<T>::max_size() {
	return max_size_;
}

}  // namespace structures
#endif
