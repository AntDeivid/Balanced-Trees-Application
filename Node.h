#ifndef NODE_H
#define NODE_H
#include "Data.h"

template <typename T>
struct Node {
    // Atributos do nó
    T *key;
    int height;
    Node<T> *left;
    Node<T> *right;
    std::vector<T*> sameKey;

    // Construtor
    Node (T *key, Node<T> *left = nullptr, Node<T> *right = nullptr, int height = 1)
        : key(key), height(height), left(left), right(right) {}
        
};

#endif // NODE_H