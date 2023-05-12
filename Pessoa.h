#ifndef PESSOA_H
#define PESSOA_H
#include <string>
#include "Data.h"

class Pessoa {
    private:
        std::string cpf;
        std::string nome;
        Date dataDeNascimento;
    
    public:
        Pessoa() = default; // Construtor padrão
        // Construtor
        Pessoa(std::string cpf, std::string nome, Date dataDeNascimento) : cpf(cpf), nome(nome), dataDeNascimento(dataDeNascimento) {}

        // Getters e Setters
        std::string& getCpf() { return this->cpf; }
        void setCpf(int novoCpf) { this->cpf = novoCpf; }
        std::string& getNome() { return this->nome; }
        void setNome(std::string novoNome) { this->nome = novoNome; }
        Date& getDataDeNascimento() { return this->dataDeNascimento; }
        void setDataDeNascimento(Date novaData) { this->dataDeNascimento = novaData; }

};

#endif // PESSOA_H