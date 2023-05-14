#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Node.h"
#include "Data.h"
#include "Pessoa.h"

template <typename T>
class avl_tree { 


public:
    avl_tree() = default;
    avl_tree(const avl_tree<T>& t); 

    avl_tree& operator=(const avl_tree<T>& t) {
        if(this != &t) {
            clear();
            this->root = clone_rec(t.root);
        }
        return *this;
    }

    int height() const { return root->height; }

    void bshow() const { bshow(root, ""); }

    ~avl_tree() { clear(); }

    void add(T *key) { root = add(root, key); }

    void clear() { root = clear(root); }

    void remove(T *key) { root = remove(root, key); }

    Node<T>* search(T key) { return search(root, key); }

    void generalSearch(T busca, int op, avl_tree<T> &arvoreCPF, avl_tree<T> &arvoreNome, avl_tree<T> &arvoreDataNasc);

    void searchByCPF(const avl_tree<T> &arvoreCPF, T key) {
        Node<T> *node = search(key);
        if(node != nullptr) {
            std::cout << "CPF: " << *(node->key) << std::endl;
            std::cout << "Nome: " << (*(Pessoa*)node->key).getNome() << std::endl;
            std::cout << "Data de Nascimento: " << (*(Pessoa*)node->key).getDataDeNascimento() << std::endl;
        }
        else { std::cout << "CPF nao encontrado" << std::endl; }
    }

    void searchByName(T key) { searchByName(root, key); }

    void searchByBirthDate(T& initialDate, T& endDate) { searchByBirthDate(root, initialDate, endDate); }

private:
    Node<T> *root {nullptr};

    int height(Node<T> *node) { return (node == nullptr) ? 0 : node->height; }

    int balance(Node<T> *node) { return height(node->right) - height(node->left); }

    void bshow(Node<T> *node, std::string heranca) const {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << *(node->key) << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr)) {
            bshow(node->left, heranca + "l");
        }
    }

    Node<T>* rightRotation(Node<T> *p) {
        Node<T> *u = p->left;
        p->left = u->right;
        u->right = p;
        // recalcular as alturas de p e de u
        p->height = 1 + std::max(height(p->left),height(p->right));
        u->height = 1 + std::max(height(u->left),height(u->right));
        return u;
    }

    Node<T>* leftRotation(Node<T> *p) {
        Node<T> *u = p->right;
        p->right = u->left;
        u->left = p;
        // recalcular as alturas de p e de u
        p->height = 1 + std::max(height(p->right),height(p->left));
        u->height = 1 + std::max(height(u->left),height(u->right));
        return u;
    }

    Node<T>* add(Node<T> *p, T *key) {
        if(p == nullptr)
            return new Node<T>(key);

        if(*key < *(p->key))
            p->left = add(p->left, key);

        else if(*key > *(p->key))
            p->right = add(p->right, key);
            
        else 
            p->sameKey.push_back(key);
        
        p = fixup_node(p, key);  

        return p;
    }

    Node<T>* fixup_node(Node<T> *p, T *key) {
        // recalcula a altura de p
        p->height = 1 + std::max(height(p->left),height(p->right));

        // calcula o balanço do p
        int bal = balance(p);

        if(bal >= -1 && bal <= 1) {
            return p;
        }

        if(bal < -1 && *key < *(p->left->key)) {
            p = rightRotation(p);
        }
        else if(bal < -1 && *key > *(p->left->key)) {
            p->left = leftRotation(p->left);
            p = rightRotation(p);
        }
        else if(bal > 1 && *key > *(p->right->key)) {
            p = leftRotation(p);
        }
        else if(bal > 1 && *key < *(p->right->key)) {
            p->right = rightRotation(p->right);
            p = leftRotation(p);
        }
        return p;
    }

    Node<T>* clear(Node<T> *node) {
        if(node != nullptr) {
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }
        return nullptr;
    }

    Node<T>* remove(Node<T> *node, T *key) {
        if(node == nullptr) // node nao encontrado
            return nullptr; /*L\pauseL*/
        if(key < node->key) 
            node->left = remove(node->left, key);
        else if(key > node->key)
            node->right = remove(node->right, key); /*L\pauseL*/
        // encontramos no node
        else if(node->right == nullptr) { // sem filho direito
            Node<T> *child = node->left;
            delete node;
            return child;
        }
        else // tem filho direito: troca pelo sucessor
            node->right = remove_successor(node, node->right); /*L\pauseL*/
        
        // Atualiza a altura do node e regula o node
        node = fixup_deletion(node); 
        return node;
        
    }

    Node<T>* remove_successor(Node<T> *root, Node<T> *node) {
        if(node->left != nullptr)
            node->left = remove_successor(root, node->left);
        else {
            root->key = node->key;
            Node<T> *aux = node->right;
            delete node;
            return aux;
        }
        // Atualiza a altura do node e regula o node
        node = fixup_deletion(node);
        return node;
    }

    Node<T>* fixup_deletion(Node<T> *node) {
        node->height = 1 + std::max(height(node->left),height(node->right));

        int bal = balance(node);

        // node pode estar desregulado, ha 4 casos a considerar
        if(bal > 1 && balance(node->right) >= 0) {
            return leftRotation(node);
        }
        else if(bal > 1 && balance(node->right) < 0) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }
        else if(bal < -1 && balance(node->left) <= 0) {
            return rightRotation(node);
        }
        else if(bal < -1 && balance(node->left) > 0) { 
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }
        return node;
    }

    Node<T>* search(Node<T> *node, T key) {
        if(node == nullptr || *(node->key) == key) { return node; }

        else if(key < *(node->key)) { return search(node->left, key); }

        else { return search(node->right, key); }
    }

    void searchByName(Node<T> *node, T key) {
        if (node == NULL) { return; }

        if (node->key->compare(0, key.length(), key) == 0) {
            std::cout << *(node->key) << std::endl;
            if (node->sameKey.size() > 0) {
                for (int i = 0; i < node->sameKey.size(); i++) {
                    std::cout << *(node->sameKey[i]) << std::endl;
                }
            }
        }

        if (key[0] < (*(node->key))[0]) { searchByName(node->left, key); }

        else if (key[0] > (*(node->key))[0]) { searchByName(node->right, key); }

        else {
            searchByName(node->left, key);
            searchByName(node->right, key);
        }
    }

    Node<T>* max(Node<T> *node) {
        if(node == nullptr) { return nullptr; }
        if(node->right == nullptr) { return node; }
        return max(node->right);
    }

    Node<T>* min(Node<T> *node) {
        if(node == nullptr) { return nullptr; }
        if(node->left == nullptr) { return node; }
        return min(node->left);
    }

    void searchByBirthDate(Node<T> *node, T& initialDate, T& endDate) {
        
        if (node == nullptr) {
            return;
        }
        Node<T> *currentNode = node;
        if (*(currentNode->key) > endDate) { 
            return; 
        }
        if (currentNode->left != nullptr && *(max(currentNode->left)->key) >= initialDate) {
            searchByBirthDate(currentNode->left, initialDate, endDate);
        }
        // posso chamar recursivamente o currentNode->left->right? Pois o currentNode->left pode
        // ser menor que o initialDate, mas o currentNode->left->right pode ser maior que o initialDate

        if (*(currentNode->key) >= initialDate && *(currentNode->key) <= endDate) {
            std::cout << *(currentNode->key) << std::endl;
            if (currentNode->sameKey.size() > 0) {
                for (int i = 0; i < currentNode->sameKey.size(); i++) {
                    std::cout << *(currentNode->sameKey[i]) << std::endl;
                }
            }
        }
        if (currentNode->right != nullptr && *(min(currentNode->right)->key) <= endDate) {
            searchByBirthDate(currentNode->right, initialDate, endDate);
        }
    }
};

#endif