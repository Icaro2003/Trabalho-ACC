#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "tabela_hash.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao, tamanhoTabela, metodoColisao, funcaoHash, chave;

    TabelaHash *tabelaHash;

    printf("\nEscolha a função de hash:\n");
    printf("1 - Divisão\n2 - Multiplicação\n");
    scanf("%d", &funcaoHash);

    printf("\nEscolha o método de colisão:\n");
    printf("1 - Encadeado\n2 - Endereçamento aberto\n");
    scanf("%d", &metodoColisao);

    lerArquivo(&tabelaHash, &tamanhoTabela, funcaoHash, metodoColisao);
    printf("Dados do arquivo carregados!\n");

    printf("\n");

    do
    {
        printf("Tabela Hash\n");
        printf("1. Inserir Manualmente\n");
        printf("2. Remover\n");
        printf("3. Exibir Tabela Hash\n");
        printf("4. Buscar Chave\n");
        printf("5. Exibir Fator de Carga\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite a chave para inserir na tabela: ");
            scanf("%d", &chave);

            if (metodoColisao == 1)
            {
                inserirEncademento(tabelaHash, chave, funcaoHash);
            }
            else
            {
                inserirEnderecamentoAberto(tabelaHash, chave, funcaoHash);
            }
            break;
        case 2:
            printf("Digite a chave para remover da tabela: ");
            scanf("%d", &chave);
            removerChave(tabelaHash, chave, funcaoHash, metodoColisao);
            break;
        case 3:
            imprimirTabelaHash(tabelaHash, metodoColisao);
            printf("Aperte ENTER para entrar no menu");
            getchar();
            getchar();
            break;
        case 4:
            printf("Digite a chave para buscar na tabela: ");
            scanf("%d", &chave);
            buscarChave(tabelaHash, chave, funcaoHash, metodoColisao);
            break;
        case 5:
            printf("Fator de carga da tabela: %g\n", fatorCarga(tabelaHash));
            break;
        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!");
            break;
        }
    } while (opcao != 0);

    return 0;
}