#ifndef NODE_H
#define NODE_H
#include "Data.h"
#include "Pessoa.h"

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
    std::vector<Pessoa*> sameKey; // Vetor de ponteiros para chaves iguais
    Pessoa *pessoa; // Ponteiro para a pessoa

    // Construtor
    Node (T *key, Node<T> *left = nullptr, Node<T> *right = nullptr, int height = 1, Pessoa *pessoa = nullptr)
        : key(key), height(height), left(left), right(right), pessoa(pessoa) {}
    
    // Construtor secundário
    Node (T *key, Pessoa *pessoa) : key(key), height(1), left(nullptr), right(nullptr), pessoa(pessoa) {}
        
};

#endif // NODE_H