# Balanced-Trees-Application
Primeiro projeto da cadeira de Estrutura de Dados Avançada, que consiste em utilizar uma árvore balanceada (AVL, no caso) em uma aplicação de consulta de dados.

**Instruções de Uso - Programa de Árvore AVL**

O programa "Balanced-Trees-Application" é um aplicativo de linha de comando que permite realizar operações em uma árvore AVL com base em um conjunto de dados de pessoas fornecido em um arquivo CSV. Siga as instruções abaixo para compilar e executar o programa.

**Passo 1: Pré-requisitos**
- Certifique-se de ter um compilador C++ instalado no seu sistema (como o GCC) e um ambiente de desenvolvimento C++ configurado.
- Verifique se você tem os arquivos necessários: `AVLTree.h`, `Pessoa.h`, `Data.h`, `main.cpp` e `data.csv`. Se for baixar deste repositório, tenha certeza que, na hora de executar, todos os arquivos estejam na mesma raíz.

**Passo 2: Compilação**
1. Abra um terminal ou prompt de comando.
2. Navegue até o diretório onde você salvou os arquivos mencionados.
3. Execute o seguinte comando para compilar o programa (usando o GCC como exemplo):
   ```
   g++ Balanced-Trees-Application.cpp -o Consulta
   ```
   Isso irá compilar o programa e gerar um arquivo executável chamado `Consulta` no mesmo diretório.

**Passo 3: Execução**
1. Após a conclusão da compilação, execute o programa com o seguinte comando:
   ```
   ./Consulta
   ```
2. O programa será iniciado e você verá um prompt solicitando que você digite um comando.
3. Os comandos disponíveis são:
   - `cpf`: Pesquisa uma pessoa na árvore pelo CPF.
   - `nome`: Pesquisa uma pessoa na árvore pelo nome (Este nome pode ser um prefixo, daí todas as pessoas que tenham nome inciado com este prefixo serão exibidas).
   - `data`: Pesquisa pessoas na árvore por um intervalo de datas de nascimento.
   - `exit`: Encerra o programa.

**Exemplos de Uso**
- Para pesquisar uma pessoa pelo CPF, digite `cpf` e siga as instruções para inserir o CPF desejado.
- Para pesquisar uma pessoa pelo nome, digite `nome` e siga as instruções para inserir o nome - ou prefixo - desejado.
- Para pesquisar pessoas por um intervalo de datas de nascimento, digite `data` e siga as instruções para inserir a data inicial e a data final.
- Para encerrar o programa, digite `exit`.

**Observações Para o Usuário**
- Certifique-se de que o arquivo `data.csv` esteja presente no mesmo diretório do programa executável.
- Caso queira mudar os dados do arquivo, adicionar ou mesmo colocar um outro arquivos, certifique-se de fornecer os dados no formato correto no arquivo `data.csv` (CPF, Nome, Sobrenome, Data, Cidade), separados por vírgulas.

**Observações Acerca da Implementação**
- O programa conta com as classes `AVLTree.h` (implementação da árvore), `Node.h` (nó da árvore), `Pessoa.h` (representa uma pessoa e seus atributos) e `Data.h` (Data e seus atributos), afim de facilitar o funcionamento e implementação do programa.
- Os dados do arquivo são lidos e armazenados em objetos Pessoa, enquanto todos estes objetos são armazenados em um vector. Todos os dados estão armazenados nos objetos do vector, nem um atributo sequer foi duplicado.
- No nó é armazenado um ponteiro tipo T (nome, cpf ou data de nascimento) como chave. O balanceamento é feito por essa chave. O valor da chave é obtido dereferenciando o ponteiro, os demais atributos são obtidos a partir dos métodos getter da classe Pessoa, a partir do ponteiro para o objeto do nó.

Agora você pode compilar e executar o programa "Balanced-Trees-Application" para interagir com a árvore AVL e realizar pesquisas com base nos dados fornecidos. Divirta-se!