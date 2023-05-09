#ifndef AVL_H
#define AVL_H
#include <vector>
#include <string>
#include "Node.h"

template <typename T>
class avl_tree { 
public:
    avl_tree() = default;
    avl_tree(const avl_tree<T>& t); 
    avl_tree& operator=(const avl_tree<T>& t); 
    int height() const;
    void bshow() const;
    ~avl_tree();
    void add(T *key);
    void clear();
    void remove(T *key);

private:
    Node<T> *root {nullptr};

    int height(Node<T> *node);
    int balance(Node<T> *node);
    void bshow(Node<T> *node, std::string heranca) const;
    Node<T>* rightRotation(Node<T> *p);
    Node<T>* leftRotation(Node<T> *p);
    Node<T>* add(Node<T> *p, T *key);
    Node<T>* fixup_node(Node<T> *p, T *key);
    Node<T>* clear(Node<T> *node);
    Node<T>* remove(Node<T> *node, T *key);
    Node<T>* remove_successor(Node<T> *root, Node<T> *node);
    Node<T>* fixup_deletion(Node<T> *node);
};

#endif