#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

int main()
{
    int opcao, chave;
    No *raiz = NULL;

    do
    {
        printf("Arvore AVL\n");
        printf("1. Carregar nos de arquivo\n");
        printf("2. Inserir no\n");
        printf("3. Remover no\n");
        printf("4. Imprimir arvore\n");
        printf("5. Buscar no\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            raiz = lerNoArquivo(raiz, "input.txt");
            printf("Nos do arquivo carregados!\n");
            break;
        case 2:
            printf("Digite o valor do no a ser inserido na arvore: ");
            scanf("%d", &chave);
            raiz = inserirNo(raiz, chave, NULL);
            break;
        case 3:
            printf("Digite o valor do no a ser removido da arvore: ");
            scanf("%d", &chave);
            raiz = removerNo(raiz, chave);
            break;
        case 4:
            imprimirArvore(raiz, 0);
            printf("Aperte ENTER para entrar no menu");
            getchar();
            getchar();
            break;
        case 5:
            printf("Digite o valor do no a ser buscado na arvore: ");
            scanf("%d", &chave);
            buscarNoPaiFilho(raiz, chave);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção invalida!\n");
            break;
        }
    } while (opcao != 0);

    liberarArvore(raiz);

    return 0;
}