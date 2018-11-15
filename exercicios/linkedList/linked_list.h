/// Copyright 2018 <Rafael Neves de Mello Oliveira>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  /// cstd::size_t
#include <stdexcept>  /// C++ exceptions

namespace structures {

template<typename T>

/*!
 * 
 *Class
 * 
 */
class LinkedList {  // Lista
 public:
    LinkedList();  // construtor padrão
    ~LinkedList();  // destrutor
    void clear();  // limpar lista
    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem
    T& at(std::size_t index);  // acessar um elemento na posição index
    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover específico
    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém
    std::size_t find(const T& data) const;  // posição do dado
    std::size_t size() const;  // tamanho da lista

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
        Node* next_{nullptr};
    };

    Node* end() { // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}

#endif
/// Construtor padrao
/*!
 * 
 *  inicializa essa classe
 *
 */
template<typename T>
structures::LinkedList<T>::LinkedList() {
     size_ = 0;
 }
/// Destrutor
/*!
 * 
 *Destroi a classe criada
 * 
 */
template<typename T>
structures::LinkedList<T>::~LinkedList() {
    head = nullptr;
 }
/// Limpa lista
/*!
 * 
 *
 */
template<typename T>
void structures::LinkedList<T>::clear() {
     head->next(nullptr);
    size_ = 0;
 }
/// Insere no fim
/*!
 * 
 *
 */
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
     if (empty()) {
        insert(data, 0);
        return;
    } else {
        auto last = end();
        last->next(new Node{data});
    }
    ++size_;
}
/// Insere no inicio
/*!
 *
 *Adiciona um elemento recebido no inicio da minha lista
 *
 */
template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    if (empty()) {
        insert(data, 0);
        return;
    } else {
        auto auxiliar = head;
        head = new Node{data, auxiliar};
    }
    ++size_;
}
/// Insere na posicao
/*!
 *
 *
 *
 */
template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index)  {
    if (index > size()) {
        throw std::out_of_range("Posição inválida");
    } else if (empty()) {
        head = new Node{data};
        ++size_;
    } else if (index == 0) {
        push_front(data);
    } else if (index == size() - 1) {
        push_back(data);
    } else {
        auto current = head;
        ++size_;
        for (auto i = 0; i < index - 1; i++) {
            current = current->next();
        }
        auto auxiliar = current->next();
        current->next(new Node{data, auxiliar});
    }
}
/// Insere em ordem
/*!
 *
 *
 *
 */
template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()){
    	insert(data, 0);
    }
    if (data == 42) {	 	  	 	     	  	  	     	  	   	     	 	
        push_back(data);
        return;
    }

    Node* previous = nullptr;
    auto current = head;
    auto i = 0;
    while (i < size() && current->data() < data) {
        previous = current;
        current = current->next();
        ++i;
    }

    if (previous == nullptr) {
        push_front(data);
        return;
    }

    previous->next(new Node{data, current});
    ++size_;
 }
 /// acessar um elemento na posição index
 /*!
 * 
 *
 *
 */
template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
     if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    if (index > size() - 1) {
        throw std::out_of_range("Posicao inválida!");
    }
    auto current = head;
    for (auto i = 0; i < index; i++) {
        current = current->next();
    }
    return current->data();
 }
/// Retirar da posicao
 /*!
 * 
 *
 *
 */
template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty()) throw std::out_of_range("Lista vazia!");
    else if (index > size() - 1) throw std::out_of_range("Posicao invalida");
    else if (index == size() - 1) return pop_back();
    else if (index == 0) return pop_front();

    auto current = head;
    auto i = 0;
    while (i < index - 1) {
        current = current->next();
        ++i;
    }

    auto return_data = current->next()->data();
    auto auxiliar = current->next();
    current->next(auxiliar->next());
    --size_;

    return return_data;
}
/// Retirar do fim
 /*!
 * 
 *
 * 
 */
template<typename T>
T structures::LinkedList<T>::pop_back() {
     if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    auto last_data = end()->data();
    delete end();
    --size_;
    end()->next(nullptr);
    return last_data;
}
/// retirar do inicio
 /*!
 * 
 * 
 *
 */
template<typename T>
T structures::LinkedList<T>::pop_front() {
     if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    auto old_head_data = head->data();
    head = head->next();
    --size_;
    return old_head_data;
}
/// remover especifico
 /*!
 *
 *
 * 
 *
 */
template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
     auto index = find(data);
    if (index == size()) {
        throw std::out_of_range("Elemento inexistente");
    }
    pop(index);
}
/// Lista vazia
 /**
 * 
 *Verifica se a lista esta vazia e retorna para o
 *usuario
 *
 */
template<typename T>
bool structures::LinkedList<T>::empty() const {
   return size() == 0;
}
/// Contem
 /*!
 * 
 * 
 * 
 *  
 */
template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
     return find(data) != size();
}
/// Posicao do dado
/*!
 * 
 * 
 *
 */
template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
     auto return_ = size();
    auto current = head;
    for (auto i = 0; i <= size() - 1; ++i) {
        if (current->data() == data) {
            return_ = i;
        }	  	  	     	  	   	     	 	
        current = current->next();
    }
    return return_;
}
/// Tamanho da lista
 /*!
 * 
 *
 * 
 */
template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
