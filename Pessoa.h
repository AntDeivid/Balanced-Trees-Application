#ifndef PESSOA_H
#define PESSOA_H
#include <string>
#include "Data.h"

/**
 * @brief Classe que representa uma pessoa
 */
class Pessoa {
    private:
        std::string cpf; // CPF do objeto Pessoa
        std::string nome; // Nome do objeto Pessoa
        Date dataDeNascimento; // Data de nascimento do objeto Pessoa
    
    public:
        Pessoa() = default; //Construtor padrão
        // Construtor
        Pessoa(std::string cpf, std::string nome, Date dataDeNascimento) : cpf(cpf), nome(nome), dataDeNascimento(dataDeNascimento) {}

        // Getters e Setters
        std::string& getCpf() { return this->cpf; } // Retorna o CPF do objeto Pessoa
        void setCpf(std::string novoCpf) { this->cpf = novoCpf; } // Altera o CPF do objeto Pessoa
        std::string& getNome() { return this->nome; } // Retorna o nome do objeto Pessoa
        void setNome(std::string novoNome) { this->nome = novoNome; } // Altera o nome do objeto Pessoa
        Date& getDataDeNascimento() { return this->dataDeNascimento; } // Retorna a data de nascimento do objeto Pessoa
        void setDataDeNascimento(Date novaData) { this->dataDeNascimento = novaData; } // Altera a data de nascimento do objeto Pessoa

};

#endif // PESSOA_H