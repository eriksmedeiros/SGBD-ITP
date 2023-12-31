#ifndef _VERIFICAR_H
#define _VERIFICAR_H

#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificarTabela(char *nome);
int verificarColuna(int id, char *nome);
int verificarChave(int id, char *valor);
int proximoEspacoVazio();
int proximaLinha(int idTabela);
void imprimirLinhaSeparadora(int *largura, int numColunas);
void imprimirLinha(int idTabela, int linha);

#endif