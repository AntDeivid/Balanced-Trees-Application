#include <iostream>
#include <vector>
#include "node.h"
#include "AVLTree.h"
using namespace std;

// retorna a altura do nó.
// se a arvore for vazia ela tem altura 0
// caso contrario, retorna o valor que está no campo height
template <typename T>
int avl_tree<T>::height(Node<T> *node) {
    return (node == nullptr) ? 0 : node->height;
}

template <typename T>
int avl_tree<T>::balance(Node<T> *node) {
    return height(node->right) - height(node->left);
}

template <typename T>
Node<T>* avl_tree<T>::rightRotation(Node<T> *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

template <typename T>
Node<T>* avl_tree<T>::leftRotation(Node<T> *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right),height(p->left));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

// função pública que recebe uma chave e a insere
// somente se ela não for repetida
template <typename T>
void avl_tree<T>::add(int key) {
    root = add(root, key);
}

// função recursiva privada que recebe uma raiz de arvore
// e uma chave e insere a chave na tree se e somente se 
// ela nao for repetida. Claro, tem que deixar AVL novamente
template <typename T>
Node<T>* avl_tree<T>::add(Node<T> *p, int key) {
    if(p == nullptr)
        return new Node(key);
    if(key == p->key) 
        return p;
    if(key < p->key)
        p->left = add(p->left, key);
    else 
        p->right = add(p->right, key);
    
    p = fixup_node(p, key);

    return p;
}

template <typename T>
Node<T>* avl_tree<T>::fixup_node(Node<T> *p, int key) {
    // recalcula a altura de p
    p->height = 1 + max(height(p->left),height(p->right));

    // calcula o balanço do p
    int bal = balance(p);

    if(bal >= -1 && bal <= 1) {
        return p;
    }

    if(bal < -1 && key < p->left->key) {
        p = rightRotation(p);
    }
    else if(bal < -1 && key > p->left->key) {
        p->left = leftRotation(p->left);
        p = rightRotation(p);
    }
    else if(bal > 1 && key > p->right->key) {
        p = leftRotation(p);
    }
    else if(bal > 1 && key < p->right->key) {
        p->right = rightRotation(p->right);
        p = leftRotation(p);
    }
    return p;
}

template <typename T>
void avl_tree<T>::clear() {
    root = clear(root);
}

template <typename T>
Node<T> *avl_tree<T>::clear(Node<T> *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

template <typename T>
avl_tree<T>::~avl_tree() {
    clear();
}

template <typename T>
void avl_tree<T>::bshow() const {
    bshow(root, "");
}

template <typename T>
void avl_tree<T>::bshow(Node<T> *node, std::string heranca) const {
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
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

template <typename T>
void avl_tree<T>::remove(int key) {
    root = remove(root, key);
}

template <typename T>
Node<T>* avl_tree<T>::remove(Node<T> *node, int key) {
    if(node == nullptr) // node nao encontrado
        return nullptr; /*L\pauseL*/
    if(key < node->key) 
        node->left = remove(node->left, key);
    else if(key > node->key)
        node->right = remove(node->right, key); /*L\pauseL*/
    // encontramos no node
    else if(node->right == nullptr) { // sem filho direito
        Node *child = node->left;
        delete node;
        return child;
    }
    else // tem filho direito: troca pelo sucessor
        node->right = remove_successor(node, node->right); /*L\pauseL*/
    
    // Atualiza a altura do node e regula o node
    node = fixup_deletion(node); 
    return node;
}

template <typename T>
Node<T>* avl_tree<T>::remove_successor(Node<T> *root, Node<T> *node) {
    if(node->left != nullptr)
        node->left = remove_successor(root, node->left);
    else {
        root->key = node->key;
        Node *aux = node->right;
        delete node;
        return aux;
    }
    // Atualiza a altura do node e regula o node
    node = fixup_deletion(node);
    return node;
}

template <typename T>
Node<T>* avl_tree<T>::fixup_deletion(Node<T> *node) {
    node->height = 1 + max(height(node->left),height(node->right));

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

// Recebe um ponteiro para a raiz de uma arvore
// e retorna o ponteiro para o clone dessa arvore
template <typename T>
Node<T>* clone_rec(Node<T> *node) {
    if(node == nullptr)
        return nullptr;
    else {
        Node *aux = new Node(node->key);
        aux->left = clone_rec(node->left);
        aux->right = clone_rec(node->right);
        return aux;
    }
}

// construtor de copia
// recebe uma avl_tree como parâmetro e cria um clone dessa 
// arvore e faz a minha arvore ser esse clone
template <typename T>
avl_tree<T>::avl_tree(const avl_tree& t) {
    this->root = clone_rec(t.root);
}

// sobrecarga do operador de atribuicao
template <typename T>
avl_tree<T>& avl_tree<T>::operator=(const avl_tree& t)  {
    if(this != &t) {
        clear();
        this->root = clone_rec(t.root);
    }
    return *this;
}

// percurso em ordem simetrica que percorre os nodes
// executando a funcao f nas chaves dos nodes
// f eh um ponteiro para uma funcao
template <typename T>
void inorder_rec(Node<T> *node, void (*f)(int& key)) {
    if(node != nullptr) {
        inorder_rec(node->left, f);
        f(node->key);
        inorder_rec(node->right, f);
    }
}

template <typename T>
int avl_tree<T>::height() const {
    return root->height;
}

// recebe como parametros a raiz de uma arvore e um vetor
// e percorre a arvore em ordem simetrica preenchendo o vetor
// com as chaves encontradas
template <typename T>
void inorder_rec(Node<T> *node, std::vector<int>& v) {
    if(node != nullptr) {
        inorder_rec(node->left, v);
        v.push_back(node->key);
        inorder_rec(node->right, v);
    }
}

// Cria uma arvore binaria de busca completa a partir de um vetor de chaves ordenado.
// Recebe como entrada o vetor, o indice inicial e o indice final do vetor
template <typename T>
Node<T>* build_complete_tree(const vector<int>& v, int l, int r) {
    if(l <= r) {
        int m = (l+r)/2;
        Node *aux = new Node(v[m]);
        aux->left = build_complete_tree(v,l,m-1);
        aux->right = build_complete_tree(v,m+1,r);
        return aux;
    }
    return nullptr;
}

// funcao que recebe o ponteiro para a raiz de uma arvore com K nodes e ajusta o
// campo height de todos os K nodes dessa arvore.
// Complexidade: O(K)
template <typename T>
int height_rec(Node<T> *node) {
    if(node == nullptr)
        return 0;
    else {
        node->height = 1 + std::max(height_rec(node->left), height_rec(node->right));
        return node->height;
    }
}