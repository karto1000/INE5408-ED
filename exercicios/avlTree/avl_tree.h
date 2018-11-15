// Copyright [2018] <Rafael Neves de Mello Oliveira>
#ifndef STRUCTURES_AVL_TREE
#define STRUCTURES_AVL_TREE

/*!
  NOTES: fb = AE - AD
          |   |    |
          |   |    |
          |   |    Arvore direita
          |   |
          |  Arvore esquerda
          |
    fator de balanceamento

    h = max(h(left), h(right))+1
*/

#include <cstdint>              /*size_t*/
#include <stdexcept>            /*exceptions*/
#include <stdlib.h>             /*abs*/
//#include <algorithm>
#include "array_list.h"         /*ArrayList*/

namespace structures {
template <typename T>
/*!
  Class binary tree
*/
class AVLTree {
public:
    AVLTree();
    /*!destructor*/
    ~AVLTree();
    /*!insert*/
    void insert(const T& data);
    /*!remove*/
    void remove(const T& data);
    /*!contains*/
    bool contains(const T& data) const;
    /*!empty*/
    bool empty() const;
    /*!size*/
    std::size_t size() const;
    /*!pre order*/
    ArrayList<T> pre_order() const;
    /*!in order*/
    ArrayList<T> in_order() const;
    /*!post order*/
    ArrayList<T> post_order() const;

private:
    struct Node {
        T data_node;
        int height;
        Node* left;
        Node* right;
        /*!
          Constructor
        */
        explicit Node(const T& data) {
          data_node = data;
          left = nullptr;
          right = nullptr;
          height = -1;
        }
        /*!
          insert a new element to my tree
        */
        void insert(const T& data_) {

            if (data_ < data_node) {
              if (left == nullptr) {
                left = new Node(data_);
              } else {
                left->insert(data_);
              }
            } else {
              if (right == nullptr) {
                right = new Node(data_);
              } else {
                right->insert(data_);
              }
            }

        }


        bool remove(const T& data_) {
          bool retorno = false;
          if (data_ > data_node) {
            retorno = right->remove(data_);
          } else if (data_ < data_node) {
            retorno = left->remove(data_);
          } else {


            retorno = true;
          }

          return retorno;

        }

        // verify if my tree has an element given by reference as parameters
        bool contains(const T& data_) const {
          bool retorno = false;

          if (data_ > data_node) {
            if (right!=nullptr) {
              retorno = right->contains(data_);
            }
          } else if (data_ < data_node) {
            if (left != nullptr) {
              retorno = left->contains(data_);
            }
          } else {
            retorno = true;
          }

          return retorno;
        }

        /*!
          Calc the height of a node. If my node is a null pointer the height is
          -1. (it is used when i have a node with no child or just one child)
        */
        int heightNode(struct Node* no) {
          if (no == nullptr) {
            return -1;
          } else {
            return no->height;
          }
        }

        /*!
            Calc the balance factor of a node based on:
            FB = left tree height - right Tree height

            to be balanced my balance factor needs to be: |FB| < 1
        */
        int balanceFactorNode (struct Node* no) {
          return abs(heightNode(no->left) - heightNode(no->dir));
        }

        /*!
          set the value of the height of my node based on:
          height = max(left tree and  right tree) + 1;
        */
        void updateHeight() {
          height = std::max(heightNode(left), right->heightNode(right)) + 1;
        }

        Node* simpleLeft() {
          Node* temp = right;
          right = temp->left;
          temp->left = this;
          height = std::max(heightNode(left), heightNode(right)) + 1;

          temp->height = std::max(heightNode(temp->left), heightNode(temp->right)) + 1;

        }

        Node* simpleRight() {
          Node* temp = left;
          left = temp->right;
          temp->right = this;
          height = std::max(heightNode(left), heightNode(right)) + 1;

          temp->height = std::max(heightNode(temp->left), heightNode(temp->right)) + 1;

          return temp;

        }

        Node* doubleLeft() {

        }

        Node* doubleRight() {

        }

        // insert all the values of my tree in a list in a pre order
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_node);

            if(left != nullptr) {
              left->pre_order(v);
            }

            if(right != nullptr) {
              right->pre_order(v);
            }

        }

        // insert all the values of my tree in a list in order
        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
              left->in_order(v);
            }

            v.push_back(data_node);

            if(right != nullptr) {
              right->in_order(v);
            }


        }

        // insert all the values of my tree in a list in a post order
        void post_order(ArrayList<T>& v) const {

            if (left!=nullptr) {
              left->post_order(v);
            }

            if (right != nullptr) {
              right->post_order(v);
            }
            v.push_back(data_node);

        }
        /*!
          funcao auxiliar para o destrutor
        */
        void destruct() const {
          if (left!=nullptr) {
            left->destruct();
          }
          if (right!=nullptr) {
            right->destruct();
          }

          delete this;
        }
    };

    Node* root;
    std::size_t size_;
};

/*!
  Constructor
*/
template <typename T>
AVLTree<T>::AVLTree() {
  root = nullptr;
  size_ = 0;
}
/*!
  Destructor
*/
template <typename T>
AVLTree<T>::~AVLTree() {
  if (!empty()) {
    root->destruct();
  }
}

/*!
  Insert
*/
template<typename T>
void AVLTree<T>::insert(const T& data) {
  if (root == nullptr) {
    root = new Node(data);
    if (root == nullptr) {
      throw std::out_of_range("Alocation error!");
    }
  } else {
    root->insert(data);
  }

  size_++;

}
/*!
  Remove
*/
template<typename T>
void AVLTree<T>::remove(const T& data) {
  if (empty()) {
    throw std::out_of_range("Empty tree");
  }
    root->remove(data);
}
/*!
  Contains
*/
template<typename T>
bool AVLTree<T>::contains(const T& data) const{
  bool retorno;
  if (empty()) {
    retorno = false;
  } else {
    retorno = root->contains(data);
  }


  return retorno;
}
/*!
  Empty
*/
template<typename T>
bool AVLTree<T>::empty() const {
  return size_ == 0;
}
/*!
  size
*/
template<typename T>
std::size_t AVLTree<T>::size() const{
  return size_;
}

/*!
  Pre order
*/
template<typename T>
ArrayList<T> AVLTree<T>::pre_order() const {
  ArrayList<T> vector;
   if (!empty()) {
     root->pre_order(vector);
   }

  return vector;
}
/*!
  In order
*/
template<typename T>
ArrayList<T> AVLTree<T>::in_order() const {
  ArrayList<T> vector;
   if (!empty()) {
    root->in_order(vector);
   }

  return vector;
}
/*!
  post order
*/
template<typename T>
ArrayList<T> AVLTree<T>::post_order() const {
  ArrayList<T> vector;
   if (!empty()) {
     root->post_order(vector);
   }

  return vector;
}

}  // namespace structures

#endif
