/// Copyright 2018 <Rafael Neves de Mello Oliveira>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  /// std::size_t
#include <stdexcept>  /// C++ Exceptions

namespace structures {

template <typename T>
/**
 * Class ArrayQueue
 */
class ArrayQueue {
 public:
    ArrayQueue();  /// constructor
    explicit ArrayQueue(std::size_t max);  /// constructor with parameters
    ~ArrayQueue();  /// destructor
    void enqueue(const T& data);  /// insert a value in the queue
    T dequeue();  /// get a value from the queue
    T& back();  /// get the value of the queue by reference
    void clear();  /// clear the queue
    std::size_t size();  /// get the actual size of the queue
    std::size_t max_size();  /// get the maximum value for the queue
    bool empty();  /// verify if the queue is empty
    bool full();  /// verify if the queue is full

 private:
    T* contents;
    std::size_t size_;  /// the indice value
    std::size_t max_size_;  /// the maximum size for my queue
    static const auto DEFAULT_SIZE = 10u;  /// default size
};
/**
 * Constructor with default size
 */
template <typename T>
ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    size_ = -1;
}

/**
 * Constructor with parameters
 */
template <typename T>
ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max];
    size_ = -1;
}

/**
 * Destruct the ArrayQueue by deleting contents
 */
template <typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}
/**
 * Enqueue a value in my queue but first verify if the queue is full or not
 */ 
template <typename T>
void ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw(std::out_of_range("Queue is full"));
    } else {
        size_++;
        contents[size_] = data;
    }
}
/**
 * First verify if my queue is empty, Dequeue a value then moves all the values
 * down (not the best implementation)
 */
template <typename T>
T ArrayQueue<T>::dequeue() {
    T data;
    if (empty()) {
        throw(std::out_of_range("The queue is empty"));
    } else {
        data = contents[0];
         --size_;
        for (int i = 0; i < size_+1; i++) {
            contents[i] = contents[i+1];
        }
    }
    return data;
}
/**
 * Gives the first element from my queue
 */
template <typename T>
T& ArrayQueue<T>::back() {
    if (empty()) {
        throw(std::out_of_range("Queue is empty"));
    } else {
        return (contents[size_]);
    }
}
/**
 * Clear my queue by putting -1 in my variable size_
 */
template <typename T>
void ArrayQueue<T>::clear() {
    size_ = -1;
}
/**
 * Gives the actual size from my queue
 */
template <typename T>
std::size_t ArrayQueue<T>::size() {
    return size_+1;
}
/**
 * Gives the maximum size to my ArrayQueue
 */
template <typename T>
std::size_t ArrayQueue<T>::max_size() {
    return max_size_;
}
/**
 * Verify if my queue is empty by checking if size_ is equal to -1 or not
 */
template <typename T>
bool ArrayQueue<T>::empty() {
    return (size_ == -1);
}
/**
 * Verify if my queue is ful by checking if my size_ is equals to my maximum 
 * size possible (here i have to add 1 to my size_ because size_ mark the last 
 * position)
 */
template <typename T>
bool ArrayQueue<T>::full() {
    return ((size_ + 1) == max_size_);
}
}  // namespace structures
#endif
