#include "funcoesBanco.h"

char nomeTab[30];
char nomeCol[30];

void menu()
{
    printf("\n --------- MENU PRINCIPAL ---------- \n");
    printf("|                                   |"
           "\n| 1- Criar Tabela                   |"
           "\n| 2- Listar todas as Tabelas        |"
           "\n| 3- Adicionar linhas a tabela      |"
           "\n| 4- Listar Dados da tabela         |"
           "\n| 5- Pesquisar valor na tabela      |"
           "\n| 6- Apagar linhas da tabela        |"
           "\n| 7- Apagar Tabela                  |"
           "\n| 0- Sair                           |");
    printf("\n ----------------------------------- \n\n");
}

void criaTab()
{
    int idTabela = proximoEspacoVazio();
    int variaveis;

    // define o nome da tabela
    printf("Defina um Nome para a Tabela: ");
    scanf("%s", nomeTab);

    while (verificarTabela(nomeTab) != -1)
    {
        printf("Nome da Tabela já Existe!\n");
        printf("Defina um Nome para a Tabela: ");
        scanf("%s", nomeTab);
    }
    strcpy(BD.tabelas[idTabela].nome_tabela, nomeTab);

    // define a quantidade de colunas
    printf("Defina a quantidade de colunas: ");
    scanf("%d", &BD.tabelas[idTabela].qtd_colunas);

    while (BD.tabelas[idTabela].qtd_colunas < 1)
    {
        printf("Quantidade não pode ser menor que 1!\n");
        scanf("%d", &BD.tabelas[idTabela].qtd_colunas);
    }

    // define a chave primaria
    printf("Defina um nome para a Chave Primaria: ");
    scanf("%s", nomeCol);
    strcpy(BD.tabelas[idTabela].colunas[0], nomeCol);
    BD.tabelas[idTabela].tipos[0] = 1;

    fflush(stdin);

    // define caracteristicas das colunas
    for (int i = 1; i < BD.tabelas[idTabela].qtd_colunas; i++)
    {
        printf("Defina o nome da coluna %i: ", i);
        scanf("%s", nomeCol);

        while (verificarColuna(idTabela, nomeCol) == 1)
        {
            printf("Nome de Coluna já existe!\n");
            printf("Defina o nome da coluna %i: ", i);
            scanf("%s", nomeCol);
        }
        strcpy(BD.tabelas[idTabela].colunas[i], nomeCol);

        printf("1-INT\n"
               "2-CHAR\n"
               "3-FLOAT\n"
               "4-DOUBLE\n"
               "5-STRING\n"
               "Digite o número referente ao tipo da coluna: ");
        scanf("%d", &variaveis);
        while (variaveis < 1 || variaveis > 5)
        {
            printf("1-INT\n"
                   "2-CHAR\n"
                   "3-FLOAT\n"
                   "4-DOUBLE\n"
                   "5-STRING\n"
                   "Opção inválida! Digite novamente: ");
            scanf("%d", &variaveis);
        }
        BD.tabelas[idTabela].tipos[i] = variaveis;
    }

    salvarArquivo();
    limparTela();
    printf("Tabela criada com Sucesso!\n");
}

// Lista todas as tabelas do BD
void listarTab()
{
    printf("\n-------- Tabelas --------\n");
    for (int i = 0; i < 10; i++)
    {
        if (strlen(BD.tabelas[i].nome_tabela) != 0)
            printf("\n|%d\t %s \t|\n", i + 1, BD.tabelas[i].nome_tabela);
    }
    salvarArquivo();
}

void inserirLinhas()
{
    salvarArquivo();

    char *conteudo = malloc(20);
    int idTabela = -1;
    int qtd_Linhas = 1;

    // verifica se a tabela existe
    while (idTabela == -1)
    {
        printf("\nDigite o nome da Tabela: ");
        scanf("%s", nomeTab);
        idTabela = verificarTabela(nomeTab);
    }

    int linhaVazia = proximaLinha(idTabela); // Obtem a primeira linha vazia disponível

    printf("Quantidade de linhas que deseja inserir: ");
    scanf("%d", &qtd_Linhas);

    while (qtd_Linhas < 1)
    {
        printf("A quantidade de linhas não pode ser menor que 1!\n");
        printf("Insira novamente: ");
        scanf("%d", &qtd_Linhas);
    }

    // insere dados nas linhas de acordo com o tipo
    for (int i = linhaVazia; i < qtd_Linhas + linhaVazia; i++) // Ex.: Linha vazia = 6 Qtd_linhas = 4, o loop percorrerá da linha 6 até a décima (6+4).
    {
        printf("**** Linha %i ****\n", i + 1);
        for (int j = 0; j < BD.tabelas[idTabela].qtd_colunas; j++)
        {
            printf("Digite os dados da coluna %s (%s)- ", BD.tabelas[idTabela].colunas[j], tipoDado(BD.tabelas[idTabela].tipos[j])); // De acordo com o número do tipo, a função tipoDado exibirá o nome do tipo
            scanf("%s", conteudo);
            while (detectarVariavel(conteudo, BD.tabelas[idTabela].tipos[j]) != 1) // se o usuário digitar um tipo diferente do da coluna
            {
                printf("Tipo inválido! Digite novamente: ");
                scanf("%s", conteudo);
            }
            if (j == 0)
            {
                while (verificarChave(idTabela, conteudo) == 1) // verifica se a chave primária já existe
                {
                    printf("Chave primária já existe! Insira outro valor: ");
                    scanf("%s", conteudo);
                }
            }
            strcpy(BD.tabelas[idTabela].linhas[i][j], conteudo);
        }
    }

    limparTela();
    printf("Conteúdo da Linha inserido com sucesso!\n");
}

void listarValores()
{
    int idTabela = -1;

    printf("\n== Listando valores ==\n");

    while (idTabela == -1)
    {
        printf("Digite a tabela que deseja visualizar: ");
        scanf("%s", nomeTab);
        idTabela = verificarTabela(nomeTab);
    }

    int numColunas = BD.tabelas[idTabela].qtd_colunas;
    int larguras[numColunas];

    // Inicializa larguras com o tamanho dos cabeçalhos
    for (int i = 0; i < numColunas; i++)
    {
        larguras[i] = strlen(BD.tabelas[idTabela].colunas[i]);
    }

    // Encontra as larguras máximas para cada coluna
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < numColunas; j++)
        {
            int comprimento = strlen(BD.tabelas[idTabela].linhas[i][j]);
            if (comprimento > larguras[j])
            {
                larguras[j] = comprimento;
            }
        }
    }

    // Imprime linha de cabeçalho
    imprimirLinhaSeparadora(larguras, numColunas);
    printf("|");
    for (int i = 0; i < numColunas; i++)
    {
        printf(" %-*s |", larguras[i], BD.tabelas[idTabela].colunas[i]);
    }
    printf("\n");
    imprimirLinhaSeparadora(larguras, numColunas);

    // Imprime dados da tabela
    for (int i = 0; i < 20; i++)
    {
        if (strlen(BD.tabelas[idTabela].linhas[i][0]) != 0)
        {
            printf("|");
            for (int j = 0; j < numColunas; j++)
            {
                printf(" %-*s |", larguras[j], BD.tabelas[idTabela].linhas[i][j]);
            }
            printf("\n");
        }
    }

    imprimirLinhaSeparadora(larguras, numColunas);
}

void apagarLinha()
{
    salvarArquivo();

    int idTabela = -1;
    char *chave = malloc(20);

    while (idTabela == -1)
    {
        printf("\nDigite o nome da tabela que deseja apagar: ");
        scanf("%s", nomeTab);

        while (verificarTabela(nomeTab) == -1)
        {
            printf("Tabela não encontrada!\n");
            printf("Digite novamente: ");
            scanf("%s", nomeTab);
        }
        idTabela = verificarTabela(nomeTab);
    }

    // pesquisa pela chave primária
    printf("Digite o valor de %s que deseja apagar: ", BD.tabelas[idTabela].colunas[0]);
    scanf("%s", chave);

    for (int i = 0; i < 20; i++)
    {
        if (strcmp(BD.tabelas[idTabela].linhas[i][0], chave) == 0)
        {
            memset(&BD.tabelas[idTabela].linhas[i], 0, sizeof(20 * 20 * 30));
            break;
        }
    }
}

void apagarTab()
{
    salvarArquivo();

    Tabela tabelaNull;
    int idTabela = -1;

    while (idTabela == -1)
    {
        printf("Digite o nome da Tabela: ");
        scanf("%s", nomeTab);

        while (verificarTabela(nomeTab) == -1)
        {
            printf("Nome de Tabela não existe!\n");
            printf("Digite o nome da Tabela: ");
            scanf("%s", nomeTab);
        }
        idTabela = verificarTabela(nomeTab);
    }
    memset(&BD.tabelas[idTabela], 0, sizeof(tabelaNull));
    limparTela();
    printf("Tabela apagada com sucesso!\n");
}

void pesquisarValor()
{
    salvarArquivo();

    int idTabela = -1;
    char valorPesquisa[30];

    while (idTabela == -1)
    {
        printf("Em qual Tabela deseja pesquisar: ");
        scanf("%s", nomeTab);

        while (verificarTabela(nomeTab) == -1)
        {
            printf("Nome de Tabela inexistente!\n");
            printf("\nDigite o nome da Tabela: ");
            scanf("%s", nomeTab);
        }

        idTabela = verificarTabela(nomeTab);
    }

    printf("Colunas disponíveis na tabela %s:\n", nomeTab);
    for (int i = 0; i < BD.tabelas[idTabela].qtd_colunas; i++)
    {
        printf("%d - %s\n", i + 1, BD.tabelas[idTabela].colunas[i]);
    }

    int colunaSelecionada;
    printf("\nSelecione o número da coluna para pesquisa: ");
    scanf("%d", &colunaSelecionada);

    while (colunaSelecionada < 1 || colunaSelecionada > BD.tabelas[idTabela].qtd_colunas)
    {
        printf("Seleção inválida!\n Digite novamente o número da coluna para pesquisar: ");
        scanf("%d", &colunaSelecionada);
    }

    printf("Digite o valor a ser pesquisado na coluna %s: ", BD.tabelas[idTabela].colunas[colunaSelecionada - 1]);
    scanf("%s", valorPesquisa);

    int filtro;
    printf("Escolha o filtro para a pesquisa:\n");
    printf("1 - Valores maiores que %s\n", valorPesquisa);
    printf("2 - Valores maiores ou iguais a %s\n", valorPesquisa);
    printf("3 - Valores iguais a %s\n", valorPesquisa);
    printf("4 - Valores menores que %s\n", valorPesquisa);
    printf("5 - Valores menores ou iguais a %s\n", valorPesquisa);
    printf("6 - Valores próximos a %s (apenas para colunas do tipo string)\n", valorPesquisa);
    scanf("%d", &filtro);

    printf("\nResultados da pesquisa:\n");

    for (int i = 0; i < 20; i++)
    {
        if (strlen(BD.tabelas[idTabela].linhas[i][0]) != 0)
        {
            int comparacao = strcmp(BD.tabelas[idTabela].linhas[i][colunaSelecionada - 1], valorPesquisa);

            switch (filtro)
            {
            case 1:
                if (comparacao > 0)
                    imprimirLinha(idTabela, i);
                break;
            case 2:
                if (comparacao >= 0)
                    imprimirLinha(idTabela, i);
                break;
            case 3:
                if (comparacao == 0)
                    imprimirLinha(idTabela, i);
                break;
            case 4:
                if (comparacao < 0)
                    imprimirLinha(idTabela, i);
                break;
            case 5:
                if (comparacao <= 0)
                    imprimirLinha(idTabela, i);
                break;
            case 6:
                // Filtrar valores próximos (apenas para colunas do tipo string)
                if (BD.tabelas[idTabela].tipos[colunaSelecionada - 1] == 5)
                {
                    int distancia = abs(comparacao);
                    if (distancia <= 2)
                    { // Tolerância
                        imprimirLinha(idTabela, i);
                    }
                }
                break;
            default:
                printf("Opção de filtro inválida!\n");
            }
        }
    }
}

void escolhaMenu()
{
    int aux = 1;
    while (aux != 0)
    {
        fflush(stdin);

        menu();

        printf("\nEscolha: ");
        scanf("%d", &aux);
        limparTela();

        fflush(stdin);
        switch (aux)
        {
        case 1:
            criaTab();
            break;
        case 2:
            listarTab();
            break;
        case 3:
            inserirLinhas();
            break;
        case 4:
            listarValores();
            break;
        case 5:
            pesquisarValor();
            break;
        case 6:
            apagarLinha();
            break;
        case 7:
            apagarTab();
            break;
        case 0:
            printf("Até logo!\n");
            break;
        default:
            printf("Opçăo inválida! Selecione uma das opçőes:\n");
            menu();
            break;
        }
    }
}
