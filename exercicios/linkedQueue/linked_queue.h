
// Copyright [2018] Rafael Neves de Mello Oliveira
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

// libreary that allows me to use exceptions
#include <stdexcept>
// library that allows me to use std::size_t
#include <cstdint>

namespace structuresQueue {

template<typename T>
// Class LinkedQueue
class LinkedQueue {
public:
    LinkedQueue();

    ~LinkedQueue();

    void clear(); // limpar

    void enqueue(const T& data); // enfilerar

    T dequeue(); // desenfilerar

    T& front() const; // primeiro dado

    T& back() const; // último dado

    bool empty() const; // fila vazia

    std::size_t size() const; // tamanho

private:
    class Node {
    public:
        // construtor
        Node(const T& data){
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

        //getter-constante: info
        const T& data() const {
            return data_;
        }

        // getter: next
        Node* next() {
            return next_;
        }

        // getter-constant: next
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

    Node* head{nullptr}; // nodo-cabeça
    Node* tail{nullptr}; // nodo-fim
    std::size_t size_{0u}; // tamanho
};

template<typename T>
LinkedQueue<T>::LinkedQueue() {

}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void LinkedQueue<T>::clear() {
    Node* previous = head;
    while(size_ > 0) {
        head = head->next();
        delete previous;
        previous = head;
        size_--;
    }

}

template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    Node* novo = new Node(data);
    if (size_ == 0) {
        head = novo;
        tail = novo;
        size_++;
    } else {
        tail->next(novo);
        tail = novo;
        size_++;
    }
}

template<typename T>
T LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Empty queue");
    }
    T data;
    Node* leave = head;
    head = head->next();
    data = leave->data();
    delete leave;
    size_--;
    return data;
}

template<typename T>
T& LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Empty queue");
    }

    return head->data();
}

template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Empty queue");
    }
    return tail->data();
}

template<typename T>
bool LinkedQueue<T>::empty() const{
    return size_ == 0;
}

template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return size_;
}

}
#endif
