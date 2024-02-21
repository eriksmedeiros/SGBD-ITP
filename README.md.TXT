# Sistema de Gerenciamento de Banco de Dados

## Visão Geral
Este projeto é um Sistema Simples de Gerenciamento de Banco de Dados implementado em C para a disciplina de Introdução às Técnicas de Programação. Permite aos usuários criar tabelas, inserir dados, listar tabelas, excluir linhas e realizar operações básicas de recuperação de dados.

## Estrutura do Projeto
O projeto está estruturado em vários arquivos fonte. Aqui está uma visão geral da estrutura do projeto:

- `dados.h` - Arquivo de cabeçalho contendo estruturas de dados e declarações de funções para o gerenciamento de dados.
- `dados.c` - Arquivo de implementação para funções de gerenciamento de dados.
- `verificar.h` - Arquivo de cabeçalho para funções relacionadas à verificação e checagem de dados.
- `verificar.c` - Arquivo de implementação para funções de verificação de dados.
- `funcoesBanco.h` - Arquivo de cabeçalho contendo declarações de funções para operações de banco de dados.
- `funcoesBanco.c` - Arquivo de implementação para funções de operação de banco de dados.
- `main.c` - Ponto de entrada principal para o programa.

## Dependências
O projeto está fundamentado nas seguintes bibliotecas da linguagem C:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```
Além dos arquivos de cabeçalho a seguir:
```c
#include "dados.h"
#include "verificar.h"
#include "funcoesBanco.h"
```

## Estrutura de dados
O projeto foi construído com base na struct abaixo que simula um banco de dados.
```c
typedef struct
{
    char nome_tabela[30];
    int qtd_colunas;
    int tipos[30];
    char colunas[20][30];
    char linhas[20][20][30];
} Tabela;
```
- **Descrição:**
  - `nome_tabela`: Nome da tabela.
  - `qtd_colunas`: Número de colunas na tabela.
  - `tipos`: Array de inteiros representando os tipos de dados das colunas.
  - `colunas`: Array de strings contendo os nomes das colunas.
  - `linhas`: Array bidimensional de strings para armazenar os valores das linhas da tabela.

- **Definição:**
```c
struct banco_de_dados
{
    Tabela tabelas[20];
};
```
- `banco_de_dados:` Estrutura que representa o banco de dados completo.
  - `tabelas:` Array de estruturas 'Tabela', permite que o banco de dados contenha até 20 tabelas.
- **Variável Externa:**
```c
extern struct banco_de_dados BD;
```
- `BD:` É uma variável externa que representa a instância do banco de dados. Pode ser acessada em diferentes partes do programa.

## Principais Funções

O arquivo `funcoesBanco.c` contém implementações das funções principais responsáveis por interações do usuário e operações no banco de dados.

## 1. `void menu()`
```c
void menu();
```
- **Descrição:**
  - Exibe o menu principal do sistema, apresentando opções para o usuário.

## 2. `void criaTab()`
```c
void criaTab();
```
- **Descrição:**
  - Permite ao usuário criar uma nova tabela no banco de dados, especificando o nome, a quantidade de colunas e as características de cada coluna.

## 3. `void listarTab()`
```c
void listarTab();
```
- **Descrição:**
  - Lista todas as tabelas existentes no banco de dados.

## 4. `void inserirLinhas()`
```c
void inserirLinhas();
```
- **Descrição:**
  - Permite ao usuário inserir uma ou mais linhas de dados em uma tabela existente no banco de dados.

## 5. `void listarValores()`
```c
void listarValores();
```
- **Descrição:**
  - Lista os valores de todas as linhas em uma tabela específica, formatando a saída de maneira organizada.

## 6. `void apagarLinha()`
```c
void apagarLinha();
```
- **Descrição:**
  - Permite ao usuário apagar uma linha específica em uma tabela, fornecendo o valor da chave primária.

## 7. `void apagarTab()`
```c
void apagarTab();
```
- **Descrição:**
  - Permite ao usuário apagar uma tabela existente no banco de dados.

## 8. `void pesquisarValor()`
```c
void pesquisarValor();
```
- **Descrição:**
  - Permite ao usuário pesquisar valores em uma coluna específica de uma tabela, aplicando filtros como maior, menor, igual, etc.

## 9. `void escolhaMenu()`
```c
void escolhaMenu();
```
- **Descrição:**
  - Função principal que conduz o usuário pelo sistema, recebendo e processando suas escolhas de operações no menu.

## Como Compilar
Para compilar o projeto, utilize o `Terminal Linux`. Por exemplo:
```bash
gcc main.c funcoes/dados.c funcoes/verificar.c funcoes/funcoesBanco.c -o exe
```

## Como Executar
Após a compilação, execute o programa:
```bash
./exe
```

## Contribuição
Projeto desenvolvido pelo aluno Erik Silva de Medeiros do Bacharelado em Tecnologia da Informação - IMD/UFRN.

## Melhorias
Possíveis melhorias poderiam ser implementadas, como: organização das funções em arquivos específicos, melhor controlhe de erros.
