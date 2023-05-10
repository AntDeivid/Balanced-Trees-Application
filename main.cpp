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

        stringstream ss2(data);
        int dia, mes, ano;
        ss2 >> mes;
        ss2.ignore(1);
        ss2 >> dia;
        ss2.ignore(1);
        ss2 >> ano;
        Date dataDeNascimento(mes, dia, ano);

        Pessoa pessoa(cpf, nome + " " + sobrenome, dataDeNascimento);
        pessoas.push_back(pessoa);

    }

}

void preencherArvores(avl_tree<string> &arvoreCpf, avl_tree<string> &arvoreNome, avl_tree<Date> &arvoreData, vector<Pessoa> &pessoas) {

    for (int i = 0; i < pessoas.size(); i++) {
        arvoreCpf.add(&pessoas[i].getCpf());
        arvoreNome.add(&pessoas[i].getNome());
        arvoreData.add(&pessoas[i].getDataDeNascimento());
    }

}

int main() {

    system("chcp 65001 > nul");

    vector<Pessoa> pessoas;
    readFile(pessoas, "data.csv");

    avl_tree<string> *arvoreCpf = new avl_tree<string>;
    avl_tree<string> *arvoreNome = new avl_tree<string>;
    avl_tree<Date> *arvoreData = new avl_tree<Date>;

    preencherArvores(*arvoreCpf, *arvoreNome, *arvoreData, pessoas);

    cout << "Teste de busca por CPF: " << endl;
    arvoreCpf->searchByCPF(*arvoreCpf, "388.624.732-57");
    //arvoreNome->bshow();

    return 0;
}