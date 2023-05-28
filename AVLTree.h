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
    /**
     * @brief Construtor da classe AVLTree
     */
    avl_tree() = default;


    /**
     * @brief Construtor de cópia da classe AVLTree
     * @param t Árvore do tipo T passada por referência
     */
    avl_tree(const avl_tree<T>& t);


    /**
     * @brief Destrutor da classe AVLTree
     */
    ~avl_tree() { clear(); }


    /**
     * @brief Sobrecarga do operador de atribuição
     * @param t Árvore do tipo T passada por referência
     * @return avl_tree& 
     */
    avl_tree& operator=(const avl_tree<T>& t) {
        if(this != &t) {
            clear();
            this->root = clone_rec(t.root);
        }
        return *this;
    }


    /**
     * @brief Função que retorna a altura da árvore
     * @return int 
     */
    int height() const { return root->height; }


    /**
     * @brief Função pública que chama a função privada
     * responsável por imprimir a árvore
     */
    void bshow() const { bshow(root, ""); }


    /**
     * @brief Função pública add que chama a função privada
     * e adiciona um nó na árvore
     * @param key Chave dereferenciada do tipo T
     */
    void add(T *key, Pessoa *pessoa) { root = add(root, key, pessoa); }

    /**
     * @brief Função pública clear que chama a função privada
     * responsável por limpar a árvore
     */
    void clear() { root = clear(root); }

    /**
     * @brief Função pública remove que chama a função privada
     * responsável por remover um nó da árvore
     * @param key Chave dereferenciada do tipo T
     */
    void remove(T *key) { root = remove(root, key); }

    /**
     * @brief Função pública search que chama a função privada
     * responsável por buscar um nó na árvore
     * @param key Chave do tipo T
     * @return Node<T>* 
     */
    Node<T>* search(T key) { return search(root, key); }

    //void generalSearch(T busca, int op, avl_tree<T> &arvoreCPF, avl_tree<T> &arvoreNome, avl_tree<T> &arvoreDataNasc);

    /**
     * @brief Função que busca um CPF recebido por parâmetro
     * e o busca na árvore de CPFs. Caso encontre, imprime a chave
     * do nó atual (CPF), e faz um casting de ponteiro para Pessoa
     * para imprimir o nome e a data de nascimento do objeto Pessoa
     * @param arvoreCPF Àrvore de CPFs onde deverá ser feita a busca
     * @param key Chave do tipo T que deve ser buscada
     */
    void searchByCPF(T key) {
        Node<T> *node = search(key);
        // Se o nó não for nulo, imprime o CPF, o nome e a data de nascimento
        if(node != nullptr) {
            print(node, 2);
        }
        else { std::cout << "CPF nao encontrado" << std::endl; }
    }

    /**
     * @brief Função que busca na árvore de nomes, nomes que
     * iniciam com a string passada por parâmetro
     * @param key Chave do tipo T que deve ser buscada
     */
    void searchByName(T key) { searchByName(root, key); }

    /**
     * @brief Função que busca na árvore de datas de nascimento, todas
     * as datas que estão entre as datas passadas por parâmetro
     * @param initialDate Objeto do tipo T que representa a data inicial
     * @param endDate Objeto do tipo T que representa a data final
     */
    void searchByBirthDate(T& initialDate, T& endDate) { searchByBirthDate(root, initialDate, endDate); }

private:
    /**
     * @brief Raíz da árvore 
     */
    Node<T> *root {nullptr};

    /**
     * @brief Retorna a altura de um nó
     * @param node Nó que terá sua altura retornada
     * @return int 
     */
    int height(Node<T> *node) { return (node == nullptr) ? 0 : node->height; }

    /**
     * @brief Retorna o balanceamento de um nó
     * @param node Nó que terá seu balanceamento retornado
     * @return int 
     */
    int balance(Node<T> *node) { return height(node->right) - height(node->left); }

    /**
     * @brief Função privada responsável por imprimir a árvore
     * @param node 
     * @param heranca 
     */
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

    /**
     * @brief Realiza uma rotação à direita
     * @param p Nó que será rotacionado	
     * @return Node<T>* 
     */
    Node<T>* rightRotation(Node<T> *p) {
        Node<T> *u = p->left;
        p->left = u->right;
        u->right = p;
        // recalcular as alturas de p e de u
        p->height = 1 + std::max(height(p->left),height(p->right));
        u->height = 1 + std::max(height(u->left),height(u->right));
        return u;
    }

    /**
     * @brief Realiza uma rotação à esquerda
     * @param p Nó que será rotacionado	
     * @return Node<T>* 
     */
    Node<T>* leftRotation(Node<T> *p) {
        Node<T> *u = p->right;
        p->right = u->left;
        u->left = p;
        // recalcular as alturas de p e de u
        p->height = 1 + std::max(height(p->right),height(p->left));
        u->height = 1 + std::max(height(u->left),height(u->right));
        return u;
    }

    /**
     * @brief Função que adiciona um nó na árvore. A chave é um ponteiro, por natureza,
     * no entanto, nas comparações para saber em qual lado da árvore o nó será adicionado,
     * é feito um dereferenciamento da chave
     * @param p Raíz da árvore a qual o nó será adicionado
     * @param key Chave do tipo T que será adicionada
     * @return Node<T>* 
     */
    Node<T>* add(Node<T> *p, T *key, Pessoa *pessoa) {
        if(p == nullptr)
            return new Node<T>(key, pessoa);

        if(*key < *(p->key))
            p->left = add(p->left, key, pessoa);

        else if(*key > *(p->key))
            p->right = add(p->right, key, pessoa);
            
        else
            // Diferente da função tradicional de inserção, aqui, caso a chave já exista,
            // um ponteiro para a pessoa é adicionado na lista de nós com a mesma chave
            p->sameKey.push_back(pessoa);
        
        p = fixup_node(p, key);  

        return p;
    }

    /**
     * @brief Função que ajusta o nó após sua inserção
     * @param p Nó que será ajustado
     * @param key Chamve do tipo T
     * @return Node<T>* 
     */
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

    /**
     * @brief Função que limpa a árvore excluindo todos os nós
     * @param node Raíz da árvore
     * @return Node<T>* 
     */
    Node<T>* clear(Node<T> *node) {
        if(node != nullptr) {
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }
        return nullptr;
    }

    /**
     * @brief Realiza uma busca na árvore pelo nó com a chave key
     * @param node Raíz da árvore
     * @param key Chamve do tipo T a ser buscada
     * @return Node<T>* 
     */
    Node<T>* search(Node<T> *node, T key) {
        if(node == nullptr || *(node->key) == key) { return node; }

        else if(key < *(node->key)) { return search(node->left, key); }

        else { return search(node->right, key); }
    }

    /**
     * @brief Função responsável por imprimir as informações da pessoa
     * 
     * @param node Nó que será impresso
     * @param op Operaçao que será realizada: 1 -> imprimir nó com chave key = nome |
     *                                        2 -> imprimir nó com chave key = cpf |
     *                                        3 -> imprimir nó com chave key = data de nascimento
     */
    void print(Node<T> *node, int op) {
        // op = 1 -> printar nó com chave key = nome
        if (op == 1) {
            std::cout << "=====================================================================" << std::endl;
            std::cout << "Nome: " << *(node->key) << std::endl;
            std::cout << "CPF: " << node->pessoa->getCpf() << std::endl;
            std::cout << "Data de nascimento: " << node->pessoa->getDataDeNascimento() << std::endl;
            if (node->sameKey.size() > 0) { // se existirem nós com a mesma chave
                for (int i = 0; i < node->sameKey.size(); i++) {
                    std::cout << "=====================================================================" << std::endl;
                    std::cout << "Nome: " << node->sameKey[i]->getNome() << std::endl;
                    std::cout << "CPF: " << node->sameKey[i]->getCpf() << std::endl;
                    std::cout << "Data de nascimento: " << node->sameKey[i]->getDataDeNascimento() << std::endl;
                }
            }
        }

        // op = 2 -> printar nó com chave key = cpf
        else if (op == 2) {
            std::cout << "=====================================================================" << std::endl;
            std::cout << "Nome: " << node->pessoa->getNome() << std::endl;
            std::cout << "CPF: " << *(node->key) << std::endl;
            std::cout << "Data de nascimento: " << node->pessoa->getDataDeNascimento() << std::endl;
            if (node->sameKey.size() > 0) { // se existirem nós com a mesma chave
                for (int i = 0; i < node->sameKey.size(); i++) {
                    std::cout << "=====================================================================" << std::endl;
                    std::cout << "Nome: " << node->sameKey[i]->getNome() << std::endl;
                    std::cout << "CPF: " << node->sameKey[i]->getCpf() << std::endl;
                    std::cout << "Data de nascimento: " << node->sameKey[i]->getDataDeNascimento() << std::endl;
                }
            }
        }

        // op = 3 -> printar nó com chave key = data de nascimento
        else if (op == 3) {
            std::cout << "=====================================================================" << std::endl;
            std::cout << "Nome: " << node->pessoa->getNome() << std::endl;
            std::cout << "CPF: " << node->pessoa->getCpf() << std::endl;
            std::cout << "Data de nascimento: " << *(node->key) << std::endl;
            if (node->sameKey.size() > 0) { // se existirem nós com a mesma chave
                for (int i = 0; i < node->sameKey.size(); i++) {
                    std::cout << "=====================================================================" << std::endl;
                    std::cout << "Nome: " << node->sameKey[i]->getNome() << std::endl;
                    std::cout << "CPF: " << node->sameKey[i]->getCpf() << std::endl;
                    std::cout << "Data de nascimento: " << node->sameKey[i]->getDataDeNascimento() << std::endl;
                }
            }
        }
    }

    /**
     * @brief Recebe uma T key como um prefixo e busca na árvore todos os nós que possuem esse prefixo
     * @param node Raíz da árvore
     * @param key Prefixo a ser comparado
     */
    void searchByName(Node<T> *node, T key) {
        if (node == nullptr) { return; }

        if (node->key->compare(0, key.length(), key) == 0) { // se o prefixo for igual a chave
            print(node, 1);
        }

        // se o primeiro caractere da chave for menor que o primeiro caractere da chave do nó atual
        // então deve ser procurado à esquerda da árvore
        if (key[0] < (*(node->key))[0]) { searchByName(node->left, key); }

        // se o primeiro caractere da chave for maior que o primeiro caractere da chave do nó atual
        // então deve ser procurado à direita da árvore
        else if (key[0] > (*(node->key))[0]) { searchByName(node->right, key); }

        // se o primeiro caractere da chave for igual ao primeiro caractere da chave do nó atual
        // então deve ser procurado à esquerda e à direita da árvore
        else {
            searchByName(node->left, key);
            searchByName(node->right, key);
        }
    }

    /**
     * @brief Retorna o maior elemento da árvore
     * Quanto maior o elemento, mais à direita ele está
     * @param node Raíz da árvore
     * @return Node<T>*
    */
    Node<T>* max(Node<T> *node) {
        if(node == nullptr) { return nullptr; }
        if(node->right == nullptr) { return node; }
        return max(node->right);
    }

    /**
     * @brief Retorna o menor elemento da árvore
     * Quanto menor o elemento, mais à esquerda ele está
     * @param node Raíz da árvore
     * @return Node<T>*
    */
    Node<T>* min(Node<T> *node) {
        if(node == nullptr) { return nullptr; }
        if(node->left == nullptr) { return node; }
        return min(node->left);
    }

    /**
     * @brief Recebe uma data inicial e uma data final e busca na árvore todos os nós que
     * possuem uma data de nascimento entre essas datas
     * @param node Raíz da árvore
     * @param initialDate Data inicial
     * @param endDate Data final
     */
    void searchByBirthDate(Node<T> *node, T& initialDate, T& endDate) {

        Node<T> *currentNode = node;
        if (node == nullptr || *(currentNode->key) > endDate) {
            return; 
        }
        // Aqui, deve ser verificado de o maior elemento da subárvore à esquerda é 
        // maior ou igual à data inicial, se for, então deve ser procurado à esquerda
        if (currentNode->left != nullptr && *(max(currentNode->left)->key) >= initialDate) {
            searchByBirthDate(currentNode->left, initialDate, endDate);
        }

        // Aqui, deve ser verificado se a data do nó atual está entre as datas inicial e final
        // se estiver, então deve ser printado
        if (*(currentNode->key) >= initialDate && *(currentNode->key) <= endDate) {
            print(currentNode, 3);
        }
        // Aqui, deve ser verificado de o menor elemento da subárvore à direita é
        // menor ou igual à data final, se for, então deve ser procurado à direita
        if (currentNode->right != nullptr && *(min(currentNode->right)->key) <= endDate) {
            searchByBirthDate(currentNode->right, initialDate, endDate);
        }
    }
};

#endif