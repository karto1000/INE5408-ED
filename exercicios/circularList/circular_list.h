#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class CircularList {
public:
    CircularList();
    ~CircularList();

    void clear(); // limpar lista

    void push_back(const T& data); // inserir no fim
    void push_front(const T& data); // inserir no início
    void insert(const T& data, std::size_t index); // inserir na posição
    void insert_sorted(const T& data); // inserir em ordem

    T& at(std::size_t index); // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const; // versão const do acesso ao indice

    T pop(std::size_t index); // retirar da posição
    T pop_back(); // retirar do fim
    T pop_front(); // retirar do início
    void remove(const T& data); // remover dado específico

    bool empty() const; // lista vazia
    bool contains(const T& data) const; // lista contém determinado dado?
    std::size_t find(const T& data) const; // posição de um item na lista

    std::size_t size() const; // tamanho da lista
private:
   class Node {  // Elemento
    public:
       Node (const T& data):
           data_{data}
       {}

       Node(const T& data, Node* next):
           data_{data},
           next_{next}
       {}

       T& data() { // getter: dado
           return data_;
       }

       const T& data() const { // getter const: dado
           return data_;
       }

       Node* next() { // getter: próximo
           return next_;
       }

       const Node* next() const { // getter const: próximo
           return next_;
       }

       void next(Node* node) { // setter: próximo
           next_ = node;
       }
    private:
       T data_;
       Node* next_ = nullptr;
    };

    Node* head = nullptr;
    std::size_t size_ = 0u;
};


template <typename T>
CircularList<T>::CircularList() {
  size_ = 0u;
}

template <typename T>
CircularList<T>::~CircularList() {
  head = nullptr;
}

template <typename T>
void CircularList<T>::clear() {

}

template <typename T>
void CircularList<T>::push_back(const T& data) {

}

template <typename T>
void CircularList<T>::push_front(const T& data) {

}

template <typename T>
void CircularList<T>::insert(const T& data, std::size_t index) {

}

template <typename T>
void CircularList<T>::insert_sorted(const T& data) {

}

template <typename T>
T& CircularList<T>::at(std::size_t index) {

}

template <typename T>
const T& CircularList<T>::at(std::size_t index) const {

}

template <typename T>
T CircularList<T>::pop(std::size_t index) {

}

template <typename T>
T CircularList<T>::pop_back () {

}

template <typename T>
T CircularList<T>::pop_front () {

}

template <typename T>
void CircularList<T>::remove(const T& data) {

}

template <typename T>
bool CircularList<T>::empty() const {

}

template <typename T>
bool CircularList<T>::contains(const T& data) const {

}

template <typename T>
std::size_t CircularList<T>::find(const T& data) const {

}

template <typename T>
std::size_t CircularList<T>::size() const {

}

}

#endif
