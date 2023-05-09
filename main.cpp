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

        /*for(int i = 0; i < cpf.size(); i++) {
            if (cpf[i] == '.' || cpf[i] == '-') {
                cpf.erase(i--, 1);
            }
        }*/
        string newCpf = "";
        for (char c : cpf) {
            if (c != '.' && c != '-') {
                newCpf += c;
            }
        }

        //cout << cpf << endl;
        //´╗┐38862473257

        stringstream ss2(data);
        int dia, mes, ano;
        ss2 >> mes;
        ss2.ignore(1);
        ss2 >> dia;
        ss2.ignore(1);
        ss2 >> ano;
        Date dataDeNascimento(mes, dia, ano);

        Pessoa pessoa(stoll(newCpf), nome + " " + sobrenome, dataDeNascimento);
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

    system("chcp 65001 > nul");

    vector<Pessoa> pessoas;
    readFile(pessoas, "data.csv");

    avl_tree<int> *arvoreCpf = new avl_tree<int>;
    avl_tree<string> *arvoreNome = new avl_tree<string>;
    avl_tree<Date> *arvoreData = new avl_tree<Date>;

    preencherArvores(*arvoreCpf, *arvoreNome, *arvoreData, pessoas);

    cout << "Teste de busca por CPF: " << endl;
    arvoreCpf->searchByCPF(*arvoreCpf, 2106664730);
    arvoreCpf->bshow();

    return 0;
}