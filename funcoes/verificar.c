#include "verificar.h"

int verificarTabela(char *nome)
{
    for (int i = 0; i < 10; i++)
    {
        if (strcmp(BD.tabelas[i].nome_tabela, nome) == 0)
            return i;
    }
    return -1;
}

int verificarColuna(int id)
{
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(BD.tabelas[id].colunas[i], nomeCol) == 0)
            return 1;
    }
    return 0;
}

int verificarChave(int id, char *valor)
{
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(BD.tabelas[id].linhas[i][0], valor) == 0)
            return 1;
    }
    return 0;
}

int proximoEspacoVazio()
{
    for (int i = 0; i < 10; i++)
    {
        if (BD.tabelas[i].qtd_colunas == 0)
            return i;
    }
    return 0;
}

int proximaLinha(int idTabela)
{
    for (int i = 0; i < 10; i++)
    {
        if (strlen(BD.tabelas[idTabela].linhas[i][0]) == 0)
            return i;
    }
    return 1;
}

void imprimirLinhaSeparadora(int *largura, int numColunas)
{
    printf("+");
    for (int i = 0; i < numColunas; i++)
    {
        for (int j = 0; j < largura[i] + 2; j++)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

void imprimirLinha(int idTabela, int linha)
{
    printf("Linha %d: ", linha + 1);
    for (int j = 1; j < BD.tabelas[idTabela].qtd_colunas; j++)
    {
        printf("%s | ", BD.tabelas[idTabela].linhas[linha][j]);
    }
    printf("\n");
}
