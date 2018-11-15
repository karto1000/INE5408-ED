#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

// Allows me to use exception
#include <stdexcept>
// Allows me to use size_t values
#include <cstdint>

namespace structures {

template<typename T>
class LinkedStack {
public:
    LinkedStack();

    ~LinkedStack();

    void clear(); // limpa pilha

    void push(const T& data); // empilha

    T pop(); // desempilha

    T& top() const; // dado no topo

    bool empty() const; // pilha vazia

    std::size_t size() const; // tamanho da pilha

private:
    class Node {
    public:
        // constructor
        Node(const T& data) {
            data_ = data;
        }
        // constructor
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        // getter: info
        T& data() {
            return data_;
        }

        // getter-constante: info
        const T& data() const {
            return data_;
        }

        // getter: próximo
        Node* next() {
            return next_;
        }
        // getter-constante: próximo
        const Node* next() const {
            return next_;
        }

        // setter: next
        void next(Node* next) {
            next_ = next;
        }
    private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr}; // nodo-topo
    std::size_t size_{0u}; // tamanho
};

// Constructor
/*!

*/
template<typename T>
LinkedStack<T>::LinkedStack() {
}
// Destructor
/*!
    Call the clear method to remove all the elements
*/
template<typename T>
LinkedStack<T>::~LinkedStack() {
    clear();
}

// Clear method
/*!
    First I check if my linked stack is empty, after that i create a new
    pointer to Node to keep the current top of my stack, then I point my
    top_ to the next element (element that is below my top), delete the
    actual top, move my previus pointer to the same of top and decrease
    the size os my stack.
    I do this until my size is equals to zero, which means my
    linked stack is empty
*/
template<typename T>
void LinkedStack<T>::clear() {
    while(size_ > 0) {
    Node* previous = top_;
    top_ = top_->next();
    delete previous;
    previous = top_;
    size_--;
    }
}

// Push method
/*!
    Insert a new element on the top of my stack. First I allocate a new
    element, then this new element next pointer point to the actual top_
    after that I change my top_ pointer to the new element beacause now this
    new element I inserted is my new top
*/
template<typename T>
void LinkedStack<T>::push(const T& data) {
  Node* novo = new Node(data);
  novo->next(top_);
  top_ = novo;
  size_++;
}

// Pop method
/*!
    Gives back the element that is in the top of my stack. Firsts I check
    if my stack us empty or not, then I allocate a new pointer and point
    to the same element that is my actual top_ is pointing, then I move
    my top_ to the next element (the element that is below my top because
    this is a stack) then set the data to the variable I created to return
    the value I want and delete my 'returno' node, because I already took
    it from my stack
*/
template<typename T>
T LinkedStack<T>::pop() {
    T data;
    if(empty()) {
       throw std::out_of_range("Empty Linked Stack");
    }
    Node* retorno = top_;
    top_ = top_->next();
    data = retorno->data();
    delete retorno;
    size_--;

    return data;
}

// Top method
/*!
    Just give me the 'data' value of my 'top_' but don't delete the node
*/
template<typename T>
T& LinkedStack<T>::top() const {
    static T data;
    if (empty()) {
        throw std::out_of_range("Empty Stack");
    } else {
        data = top_->data();
    }
    return data;
}

// Empty method
/*!
    Check if my linked list is empty and return a boolean value
*/
template<typename T>
bool LinkedStack<T>::empty() const {
    return size_ == 0u;
}

// Size method
/*!
    Return the actual size of my linked stack
*/
template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}
}  // namespace structures

#endif
