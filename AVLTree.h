#ifndef AVL_H
#define AVL_H
#include <vector>
#include <string>
#include "Node.h"


class avl_tree { 
public:
    avl_tree() = default;
    avl_tree(const avl_tree& t); 
    avl_tree& operator=(const avl_tree& t); 
    int height() const;
    void bshow() const;
    ~avl_tree();

    avl_tree* intercala(const avl_tree& t);

    virtual void add(int key);
    virtual void clear();
    virtual void remove(int key);
    virtual void access_keys_inorder(void (*f)(int& key)); 
    virtual void keys_as_vector(std::vector<int>& v) const;

private:
    Node *root {nullptr};

    int height(Node *node);
    int balance(Node *node);
    void bshow(Node *node, std::string heranca) const;
    Node* rightRotation(Node *p);
    Node* leftRotation(Node *p);
    Node* add(Node *p, int key);
    Node* fixup_node(Node *p, int key);
    Node* clear(Node *node);
    Node* remove(Node *node, int key);
    Node* remove_successor(Node *root, Node *node);
    Node* fixup_deletion(Node *node);
};

#endif