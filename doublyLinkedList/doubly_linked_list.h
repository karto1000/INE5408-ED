// Copyright [2018] Rafael Neves de Mello Oliveira
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

// library that allows me to use exceptions
#include <stdexcept>
// library that allows me to use size_t values
#include <cstdint>

namespace structures {

template<typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data); // insere no fim
    void push_front(const T& data); // insere no início
    void insert(const T& data, std::size_t index); // insere na posição
    void insert_sorted(const T& data); // insere em ordem

    T pop(std::size_t index); // retira da posição
    T pop_back(); // retira do fim
    T pop_front(); // retira do início
    void remove(const T& data); // retira específico

    bool empty() const; // lista vazia
    bool contains(const T& data) const; // contém

    T& at(std::size_t index); // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const; // getter constante a um elemento

    std::size_t find(const T& data) const; // posição de um dado
    std::size_t size() const; // tamanho
    void printList(T data);
private:
    class Node {
    public:
        Node(const T& data) {
            data_ = data;
        }
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }
        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            prev_ = prev;
            next = next_;
        }

        // getter: info
        T& data() {
            return data_;
        }

        // getter constant: info 
        const T& data() const {
            return data_;
        }

        // getter prev
        Node* prev() {
            return prev_;
        }
        // getter constant prev
        const Node* prev() const {
            return prev_;
        }

        // setter prev
        void prev(Node* node) {
            prev_ = node;
        }

        // getter next
        Node* next() {
            return next_;
        }
        // getter cosntant next
        const Node* next() const {
            return next_;
        }

        // setter next
        void next(Node* node) {
            next_ = node;
        }
    private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};  // primeiro da lista
    Node* tail{nullptr};  // ultimo da lista
    std::size_t size_{0u};
};

// Cosntructor
/*!
    I dont do anything here because I inicialized the 'head', 'tail' and
    'size_' inside the class 
*/
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {

}

// destructor
/*!

*/
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}
// Clear method
/*!
    Clear my list by deleting every node exitent
*/
template <typename T>
void DoublyLinkedList<T>::clear() {
    Node* previous = head;
    while(size_ != 0) {
        head = head->next();
        delete previous;
        previous = head;
        size_--;
    }
    tail = nullptr;
}

// Push back method
/*!
    Insert an element at the end of my linked list
*/
template <typename T>
void DoublyLinkedList<T>::push_back(const T& data) {
    Node* novo = new Node(data);
    if (size_ == 0) {
        head = novo;
        tail = novo;
        size_++;
    } else {
        tail->next(novo);
        novo->prev(tail);
        tail = novo;
        size_++;
    }
}
// push front method
/*!
    Insert an element at the begining of my linked list
*/
template <typename T>
void DoublyLinkedList<T>::push_front(const T& data) {
    Node* novo = new Node(data);
    if(size_ == 0u) {
        head = novo;
        tail = novo;
        size_++;
    } else {
        head->prev(novo);
        novo->next(head);
        head = novo;
        size_++;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    
    if (index > size_) {
        throw std::out_of_range("Invalid index");
    }
    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* novo = new Node(data);
        Node* previous = head;
        std::size_t counter = 0u;

        while (counter < index - 1) {
            previous = previous->next();
            counter++;
        }

        novo->prev(previous);
        novo->next(previous->next());
        previous->next()->prev(novo);
        previous->next(novo);
        size_++;
    }

}

template <typename T>
void DoublyLinkedList<T>::insert_sorted(const T& data) { 
    Node* novo = new Node(data);
    if (size_ == 0u) {
        head = novo;
        tail = novo;
        size_++;
    } else {
        Node* previous = head;
        std::size_t counter = 0u;
        while(counter < size_-1) {
            if (data < previous->data()) {
                break;
            } else {
                previous = previous->next();
                counter++;
            }
        }

        if (counter == 0u) {
            push_front(data);
        } else if (counter == size_-1){
            push_back(data);
        } else {
            novo->next(previous);
            novo->prev(previous->prev());
            previous->prev()->next(novo);
            previous->prev(novo);
            size_++;
        }
    }
}

template <typename T>
T DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Empty list");
    }

    if (index >= size_) {
        throw std::out_of_range("Invalid index"); 
    }
    
    T data;

    if (index == 0) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    } else {
        Node* leave = head;
        std::size_t counter = 0u;
        while (counter < index) {
            leave = leave->next();
            counter++;
        }

        data = leave->data();
        leave->prev()->next(leave->next());
        leave->next()->prev(leave->prev());
        size_--;
        delete leave;
    }

    return data;
}

// Pop back
/*!
    Get an element from the end of my list
*/
template <typename T>
T DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Empty list");
    }

    T data;
    Node* leave = tail;
    if (size_ == 1) {
        tail = tail->prev();
        head = head->next();
        data = leave->data();
        delete leave;
        size_--;
    } else {
        tail = tail->prev();
        data = leave->data();
        delete leave;
        tail->next(nullptr);
        size_--;
    }

    return data;
}

template <typename T>
T DoublyLinkedList<T>::pop_front() {
    if(empty()) {
        throw std::out_of_range("Empty list");
    }

    T data;
    Node* leave = head;

    if (size_ == 1) {
        head = head->next();
        tail = tail->prev();
        data = leave->data();
        delete leave;
        size_--;
    } else {    
        head = head->next();
        data = leave->data();
        delete leave;
        head->prev(nullptr);
        size_--;
    }

    return data;
}

template <typename T>
void DoublyLinkedList<T>::remove(const T& data) {
    pop(find(data));
}


// empty method
/*!
    verify if my list is empty or not
*/
template <typename T>
bool DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

// At method
/*!
    Return the value of an index by its reference, It means this gives back the 
    value of 'data' but a copy of data is not made to compute it
*/
template <typename T>
bool DoublyLinkedList<T>::contains(const T& data) const {
    return find(data) != size_; 
}

template <typename T>
T& DoublyLinkedList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Empty List");
    }
    if (index >= size_) {
        throw std::out_of_range("Invalid index");
    }

    Node* retorno = head;
    /*! Goes walking with my retorno variable throughout the list until I find the
        index I want to return
    */
    std::size_t counter = 0u;    
    while(counter < index) {
        retorno  = retorno->next();
        counter++;
    }
    return retorno->data();
}

// At method
/*!
    Return the value of an index by its reference, It means this gives back the 
    value of 'data' but a copy of data is not made to compute it
*/
template <typename T>
const T& DoublyLinkedList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("Empty List");
    }
    if (index >= size_) {
        throw std::out_of_range("Invalid index");
    }

    Node* retorno = head;
    /*! Goes walking with my retorno variable throughout the list until I find the
        index I want to return
    */
    std::size_t counter = 0u;    
    while(counter < index) {
        retorno  = retorno->next();
        counter++;
    }
    return retorno->data();
}

//
template <typename T>
std::size_t DoublyLinkedList<T>::find(const T& data) const {
    std::size_t indexCounter = 0u;

    if (empty()) {
        throw std::out_of_range("Empty list");
    }

    Node* elementFounded = head;

    while(indexCounter < size_) {
        if (data == elementFounded->data()) {
            return indexCounter;
        } else {
            elementFounded = elementFounded->next();
            indexCounter++; 
        }
    }
    return indexCounter;
}

// size method
/*!
    Gives me the actual size of my list
*/
template <typename T>
std::size_t DoublyLinkedList<T>::size() const {
    return size_;
}

template <typename T>
void DoublyLinkedList<T>::printList(T data) {
    printf("%d \n", data);
}

}

#endif