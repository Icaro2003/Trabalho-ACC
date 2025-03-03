#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "fila_prioridade.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    FilaPrioridade *fp = NULL;
    int opcao, prioridade, capacidade;
    char nome[MAX_STRING];

    lerArquivo(&fp, &capacidade, "input.txt");
    printf("Dados carregados com sucesso!\n");

    do
    {
        printf("\nFila de Prioridades\n");
        printf("1. Inserir elemento\n");
        printf("2. Extrair elemento de maior prioridade\n");
        printf("3. Imprimir fila de prioridade\n");
        printf("4. Alterar prioridade de um elemento\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o nome do elemento: ");
            scanf("%s", nome);

            printf("Digite a prioridade do elemento: ");
            scanf("%d", &prioridade);

            if (inserirElemento(fp, nome, prioridade))
            {
                printf("Elemento \"%s\" com prioridade %d inserido com sucesso!\n", nome, prioridade);
            }
            else
            {
                printf("Erro ao inserir elemento!\n");
            }
            break;
        case 2:
            if (fp->tamanho > 0)
            {
                ElementoFilaPrioridade maior = maiorElemento(fp);

                printf("Maior elemento: \"%s\"\nPrioridade: %d\n", maior.nome, maior.prioridade);
            }
            else
            {
                printf("Fila vazia!\n");
            }
            break;
        case 3:
            imprimirFilaPrioridade(fp);
            printf("Aperte ENTER para entrar no menu");
            getchar();
            getchar();
            break;
        case 4:
            printf("Digite o nome do elemento: ");
            scanf(" %[^\n]", nome);

            printf("Digite a prioridade do elemento: ");
            scanf("%d", &prioridade);

            if (alterarPrioridade(fp, nome, prioridade))
            {
                printf("Prioridade do elemento \"%s\" alterada para %d com sucesso!\n", nome, prioridade);
            }
            else
            {
                printf("Elemento nao encontrado!\n");
            }
            break;
        case 5:
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao incorreta!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}