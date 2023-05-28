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

        // Leitura e separação dos dados da linha
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

        Pessoa pessoa(cpf, nome + " " + sobrenome, dataDeNascimento, cidade);
        pessoas.push_back(pessoa);

    }

}

// Preenche as árvores
void preencherArvores(avl_tree<string> &arvoreCpf, avl_tree<string> &arvoreNome, avl_tree<Date> &arvoreData, vector<Pessoa> &pessoas) {

    for (int i = 0; i < pessoas.size(); i++) {
        string *cpf = &pessoas[i].getCpf();
        arvoreCpf.add(cpf, &pessoas[i]);
        string *nome = &pessoas[i].getNome();
        arvoreNome.add(nome, &pessoas[i]);
        Date *data = &pessoas[i].getDataDeNascimento();
        arvoreData.add(data, &pessoas[i]);
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

    while(true) {
		string comando, token;
        cout << "Digite o comando desejado: ";
		getline(cin, comando);
        std::cout << "=====================================================================" << std::endl;
        comando.erase(comando.find_last_not_of("\r\n") + 1); // remove \r\n do final da string
		stringstream buffer{ comando };
        buffer >> token;

        cout << "Comando = $" << buffer.str() << endl;
        std::cout << "=====================================================================" << std::endl;

		// exit
		if(token == "exit") {
            arvoreCpf->clear();
			delete arvoreCpf;
            arvoreNome->clear();
            delete arvoreNome;
            arvoreData->clear();
            delete arvoreData;
            cout << "Saindo..." << endl;
            system("cls || clear");
			break;
		}
		// cpf
		else if(token == "cpf") {
            string cpf;
            cout << "Digite o CPF a ser pesquisado: ";
            getline(cin, cpf);
            cout << "Carregando respostas..." << endl;
            cout << "Respostas carregadas com sucesso!" << endl;
            arvoreCpf->searchByCPF(cpf);
		}
		// nome
		else if(token == "nome") {
            string nome;
            cout << "Digite o nome a ser pesquisado: ";
            getline(cin, nome);
            cout << "Carregando respostas..." << endl;
            cout << "Respostas carregadas com sucesso!" << endl;
            arvoreNome->searchByName(nome);
		}
        // data
		else if(token == "data") {
            string dataInicial, dataFinal;

            cout << "Digite a data de início (dd/mm/aaaa): ";
            getline(cin, dataInicial);
            cout << "Digite a data final (dd/mm/aaaa): ";
            getline(cin, dataFinal);

            stringstream ssI(dataInicial);
            int dia, mes, ano;
            ssI >> mes;
            ssI.ignore(1);
            ssI >> dia;
            ssI.ignore(1);
            ssI >> ano;
            Date initialDate(mes, dia, ano);

            stringstream ssF(dataFinal);
            ssF >> mes;
            ssF.ignore(1);
            ssF >> dia;
            ssF.ignore(1);
            ssF >> ano;
            Date endDate(mes, dia, ano);

            cout << "Carregando respostas..." << endl;
            cout << "Respostas carregadas com sucesso!" << endl;
            arvoreData->searchByBirthDate(initialDate, endDate);

		}

        // comando inexistente
		else {
			cout << "comando inexistente" << endl;
		}
        
        std::cout << "=====================================================================" << std::endl;
        cout << "Pressione ENTER para continuar...";
        cin.ignore();
        system("cls || clear");
	}

    return 0;
}