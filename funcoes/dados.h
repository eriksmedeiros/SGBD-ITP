#ifndef _DADOS_H
#define _DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char nomeTab[30];
extern char nomeCol[30];

typedef struct
{
    char nome_tabela[30];
    int qtd_colunas;
    int tipos[30];
    char colunas[20][30];
    char linhas[20][20][30];
} Tabela;

struct banco_de_dados
{
    Tabela tabelas[20];
};

extern struct banco_de_dados BD;

void carregarArquivo();
void salvarArquivo();
char *tipoDado(int num);
int detectarVariavel(char *str, int alvo);
void limparTela();

#endif
