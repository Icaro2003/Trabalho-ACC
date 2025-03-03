#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "arvore_avl.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao, chave;
    No *raiz = NULL;

    raiz = lerNoArquivo(raiz, "input.txt");
    printf("Nos do arquivo carregados!\n");

    do
    {
        printf("Arvore AVL\n");
        printf("1. Inserir no\n");
        printf("2. Remover no\n");
        printf("3. Imprimir arvore\n");
        printf("4. Buscar no\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor do no a ser inserido na arvore: ");
            scanf("%d", &chave);
            raiz = inserirNo(raiz, chave, NULL);
            break;
        case 2:
            printf("Digite o valor do no a ser removido da arvore: ");
            scanf("%d", &chave);
            raiz = removerNo(raiz, chave);
            break;
        case 3:
            imprimirArvore(raiz, 0);
            printf("Aperte ENTER para entrar no menu");
            getchar();
            getchar();
            break;
        case 4:
            printf("Digite o valor do no a ser buscado na arvore: ");
            scanf("%d", &chave);
            buscarNoPaiFilho(raiz, chave);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (opcao != 0);

    liberarArvore(raiz);

    return 0;
}