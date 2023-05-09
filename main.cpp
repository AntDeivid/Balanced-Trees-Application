#include "AVLTree.h"
#include "Pessoa.h"
#include "Data.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

void readFile(vector<Pessoa> &pessoas, string filename) {

    ifstream file(filename);
    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string cpf, nome, sobrenome, data, cidade;
        getline(ss, cpf, ',');
        getline(ss, nome, ',');
        getline(ss, sobrenome, ',');
        getline(ss, data, ',');
        getline(ss, cidade, ',');

        for(int i = 0; i < cpf.size(); i++) {
            if (cpf[i] == '.' || cpf[i] == '-') {
                cpf.erase(i--, 1);
            }
        }

        cout << cpf << endl;

        stringstream ss2(data);
        int dia, mes, ano;
        ss2 >> mes;
        ss2.ignore(1);
        ss2 >> dia;
        ss2.ignore(1);
        ss2 >> ano;
        Date dataDeNascimento(mes, dia, ano);

        Pessoa pessoa(stoi(cpf), nome + " " + sobrenome, dataDeNascimento);
        pessoas.push_back(pessoa);

    }

}

void preencherArvores(avl_tree<int> &arvoreCpf, avl_tree<string> &arvoreNome, avl_tree<Date> &arvoreData, vector<Pessoa> &pessoas) {

    for (int i = 0; i < pessoas.size(); i++) {
        arvoreCpf.add(&pessoas[i].getCpf());
        arvoreNome.add(&pessoas[i].getNome());
        arvoreData.add(&pessoas[i].getDataDeNascimento());
    }

}

int main() {
    vector<Pessoa> pessoas;
    readFile(pessoas, "data.csv");

    avl_tree<int> *arvoreCpf = new avl_tree<int>;
    avl_tree<string> *arvoreNome = new avl_tree<string>;
    avl_tree<Date> *arvoreData = new avl_tree<Date>;

    preencherArvores(*arvoreCpf, *arvoreNome, *arvoreData, pessoas);

    cout << "Arvore de CPFs:" << endl;
    arvoreCpf->bshow();

    cout << "Arvore de nomes:" << endl;
    arvoreNome->bshow();

    cout << "Arvore de datas de nascimento:" << endl;
    arvoreData->bshow();

    for(int i = 0; i < pessoas.size(); i++) {
        cout << "Pessoa " << i + 1 << ":" << endl;
        cout << "CPF: " << pessoas[i].getCpf() << endl;
        cout << "Nome: " << pessoas[i].getNome() << endl;
        cout << "Data de nascimento: " << pessoas[i].getDataDeNascimento().getDia() << "/" << pessoas[i].getDataDeNascimento().getMes() << "/" << pessoas[i].getDataDeNascimento().getAno() << endl;
        cout << endl;
    }

    cout << pessoas.size() << endl;

    return 0;
}