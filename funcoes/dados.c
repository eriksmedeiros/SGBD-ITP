#include "dados.h"

struct banco_de_dados BD;

void carregarArquivo()
{
    FILE *arquivo = fopen("arquivos/bancoDados.txt", "r");
    if (arquivo == NULL)
        return;

    fread(&BD, sizeof(struct banco_de_dados), 1, arquivo);
    fclose(arquivo);
}

void salvarArquivo()
{
    FILE *arquivo = fopen("arquivos/bancoDados.txt", "w");
    if (arquivo == NULL)
    {
        printf("O Banco de Dados não pôde ser aberto.\n");
        exit(1);
    }

    fwrite(&BD, sizeof(struct banco_de_dados), 1, arquivo);

    if (fwrite(&BD, sizeof(struct banco_de_dados), 1, arquivo) == 0)
        printf("Erro ao salvar o arquivo.\n");
    fclose(arquivo);
}

char *tipoDado(int num)
{
    char *var[] = {"INT", "CHAR", "FLOAT", "DOUBLE", "STRING"};
    if (var[num - 1])
        return var[num - 1];
    else
        return "Desconhecido";
}

int detectarVariavel(char *str, int alvo)
{
    int marcadores[5];
    marcadores[4] = 1;

    if (strlen(str) == 1)
        marcadores[1] = 1;
    if (strtof(str, NULL) != 0 && strchr(str, '.'))
        marcadores[2] = 1;
    if (strtod(str, NULL) != 0 && strchr(str, '.'))
        marcadores[3] = 1;
    if (strtol(str, NULL, 10) != 0 && marcadores[2] != 1 && marcadores[3] != 1)
        marcadores[0] = 1;

    return marcadores[alvo - 1];
}

void limparTela()
{
    printf("\033[H\033[J");
}
