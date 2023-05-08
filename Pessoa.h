#ifndef PESSOA_H
#define PESSOA_H
#include <string>
#include "Data.h"

class Pessoa {
    private:
        int cpf;
        std::string nome;
        Date dataDeNascimento;
    
    public:
        Pessoa() = default;
        Pessoa(int cpf, std::string nome, Date dataDeNascimento) : cpf(cpf), nome(nome), dataDeNascimento(dataDeNascimento) {}

        int getCpf() const { return cpf; }
        void setCpf(int novoCpf) { this->cpf = novoCpf; }
        std::string getNome() const { return nome; }
        void setNome(std::string novoNome) { this->nome = novoNome; }
        Date getDataDeNascimento() const { return dataDeNascimento; }
        void setDataDeNascimento(Date novaData) { this->dataDeNascimento = novaData; }

};

#endif // PESSOA_H