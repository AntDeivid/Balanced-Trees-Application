#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    // atributos
    T *key;
    int height;
    Node<T> *left;
    Node<T> *right;

    // Construtor
    Node (T *key, Node<T> *left = nullptr, Node<T> *right = nullptr, int height = 1)
        : key(key), height(height), left(left), right(right) {}
        
};

#endif // NODE_H