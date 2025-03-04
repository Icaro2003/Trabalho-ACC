#include <stdio.h>
#include <stdlib.h>
#include "fila_prioridade.h"

int main()
{
    FilaPrioridade *fp = NULL;
    int opcao, prioridade, capacidade;
    char nome[MAX_STRING];

    do
    {
        printf("\nFila de Prioridades\n");
        printf("1. Inserir elementos por arquivo\n");
        printf("2. Inserir elemento\n");
        printf("3. Extrair elemento de maior prioridade\n");
        printf("4. Imprimir fila de prioridade\n");
        printf("5. Alterar prioridade de um elemento\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            lerArquivo(&fp, &capacidade, "input.txt");
            printf("Dados carregados com sucesso!\n");
            break;
        case 2:
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
        case 3:
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
        case 4:
            imprimirFilaPrioridade(fp);
            printf("Aperte ENTER para entrar no menu");
            getchar();
            getchar();
            break;
        case 5:
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
        case 6:
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