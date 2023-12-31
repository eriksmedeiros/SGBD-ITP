#include <stdio.h>
#include <stdlib.h>
#include "funcoes/funcoesBanco.h"

int main(int argc, char const *argv[])
{
    carregarArquivo();

    printf("\nBem vindo ao gerenciador de Banco de Dados!\n");
    escolhaMenu();

    return 0;
}
