#ifndef NODE_H
#define NODE_H
#include "Data.h"

/**
 * @brief Nó template da árvore AVL
 * @tparam T tipo de dado armazenado no nó
 */
template <typename T>
struct Node {
    T *key; // Ponteiro para a chave
    int height; // Altura do nó
    Node<T> *left; // Ponteiro para o filho esquerdo
    Node<T> *right; // Ponteiro para o filho direito
    std::vector<T*> sameKey; // Vetor de ponteiros para chaves iguais

    // Construtor
    Node (T *key, Node<T> *left = nullptr, Node<T> *right = nullptr, int height = 1)
        : key(key), height(height), left(left), right(right) {}
        
};

#endif // NODE_H