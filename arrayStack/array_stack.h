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


/**
 * Constructor with no parameters
 */
template<typename T>
ArrayStack<T>::ArrayStack() {	 	  	 	      	     	   	      	 	     	   	 	
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}
/**
 * Constructor with parameters
 */
template <typename T>
ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}
/**
 * Destruct the arrayStack
 */
template <typename T>
ArrayStack<T>::~ArrayStack() {
	delete[] contents;
}
/**
 * Clear the ArrayStack by setting the top to -1 value
 */
template <typename T>
void ArrayStack<T>::clear() {
	top_ = -1;
}
/**
 * Verify if the ArrayStack is full or not by testing 
 */
template <typename T>
bool ArrayStack<T>::full() {
	return (top_ == max_size_ - 1);
}
/**
 * Verify if the ArrayStack is empty by testing if the top is -1
 */
template <typename T>
bool ArrayStack<T>::empty() {	 	  	 	      	     	   	      	 	     	   	 	
    return (top_ == -1);
}
/**
 * Insert a value to the ArrayStack but first verify if the stack is full or not
 */
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
 *  Remove the value of the top from the ArrayStack
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

/**
 * Show the value from the top by reference
 */
template <typename T>
T& ArrayStack<T>::top() {
    return contents[top_];
}
/**
 * Gives the size of the ArrayStack
 */
template <typename T>
std::size_t ArrayStack<T>::size() {	 	  	 	      	     	   	      	 	     	   	 	
	return top_ + 1;
}

/**
 * Gives the maximum value from my current ArrayStack
 */
template <typename T>
std::size_t ArrayStack<T>::max_size() {
	return max_size_;
}

}  // namespace structures
#endif
