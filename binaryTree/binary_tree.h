
#ifndef STRUCTURES_BINARY_TREE
#define STRUCTURES_BINARY_TREE

#include "array_list.h"
// library that allows me to use exceptions
#include <stdexcept>
// library that allows me to use size_t values
#include <cstdint>


namespace structures {
template<typename T>
class BinaryTree {
public:

    BinaryTree();

    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
      /*!
        Constructor
      */
        Node(const T& data_) {
          //data = this->data;
          data_node = data_;
          left = nullptr;
          right = nullptr;

        }
        /*!
          Insert
        */
        void insert(const T& data_) {
          if (data_ > data_node) {
            if (right == nullptr) {
              Node* novo = new Node(data_);
              right = novo;
            } else {
              right->insert(data_);
            }
          } else {
            if(left == nullptr) {
              Node* novo = new Node(data_);
              left = novo;
            } else {
              left->insert(data_);
            }
          }
        }
        /*!
          remove a value
        */
        bool remove(const T& data_) {
          if (data_ == data_node) {
            data_node = T{};
            return true;
          } else if (data_ < data_node) {
            return (left) and left->remove(data_);
          } else {
            return (right) and right->remove(data_);
          }
        }
        /*!
          verify if contains a value
        */
        bool contains(const T& data_) const {
          if (data_ <data_node) {
                  return left  == nullptr ? false : left->contains(data_);
              } else if (data_ > data_node) {
                  return right == nullptr ? false : right->contains(data_);
              } else {
                  return true;
              }
        }

        void pre_order(ArrayList<T>& v) const {
          v.push_back(data_node);
          if (left) {
            left->pre_order(v);
          }

          if (right) {
            right->pre_order(v);
          }
        }

        void in_order(ArrayList<T>& v) const {
          if (left) {
            left->in_order(v);
          }
          v.push_back(data_node);

          if(right) {
            right->in_order(v);
          }
        }

        void post_order(ArrayList<T>& v) const {
          if (left) {
            left->post_order(v);
          }
          if (right) {
            right->post_order(v);
          }
          v.push_back(data_node);
        }

        //T data;
        T data_node;
        Node* left;
        Node* right;
    };

    Node* root;
    std::size_t size_;
};

/*!
  Constructor of my tree
*/
template<typename T>
BinaryTree<T>::BinaryTree() {
  root = nullptr;
  size_ = 0;
}

/*!
  Delete all my tree
*/
template<typename T>
BinaryTree<T>::~BinaryTree() {
  while(!empty()) {
    remove(root->data_node);
  }
}

/*!
  Insert a new value in my tree
*/
template<typename T>
void BinaryTree<T>::insert(const T& data) {
  if (size_ == 0) {
    root = new Node(data);
  } else {
    root->insert(data);
  }

  size_++;
}

/*!
  Remove
*/
template<typename T>
void BinaryTree<T>::remove(const T& data) {
  if (empty()) {
    throw std::out_of_range("Empty tree");
  }
  root->remove(data);
  size_--;
}

template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
  if(empty()) {
    return false;
  }
  return root->contains(data);
}

/*!
  Empty
*/
template<typename T>
bool BinaryTree<T>::empty() const {
  return size_ == 0;
}

/*!
  size
*/
template<typename T>
std::size_t BinaryTree<T>::size() const {
  return size_;
}

template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
  auto vector = ArrayList<T>{};
  if (!empty()) {
    root->pre_order(vector);
  }
  return vector;
}

template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
  auto vector = ArrayList<T>{};
  if (!empty()) {
    root->in_order(vector);
  }
  return vector;
}

template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
  auto vector = ArrayList<T>{};
  if (!empty()) {
    root->post_order(vector);
  }
  return vector;
}

}  // NAMESPACE STRUCTURES

#endif
