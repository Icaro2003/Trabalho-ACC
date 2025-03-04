#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_avl.h"

No *criarNo(int chave)
{
    No *novoNo = (No *)malloc(sizeof(No));

    if (novoNo == NULL)
    {
        printf("Erro ao alocar memoria para o no!\n");
        exit(1);
    }

    novoNo->chave = chave;
    novoNo->altura = 1;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->pai = NULL;

    return novoNo;
}

int alturaNo(No *no)
{
    if (no == NULL)
    {
        return 0;
    }

    return no->altura;
}

int fatorBalanceamentoNo(No *no)
{
    if (no == NULL)
    {
        return 0;
    }

    return alturaNo(no->esquerda) - alturaNo(no->direita);
}

int valorMaximo(int v1, int v2)
{
    return (v1 > v2) ? v1 : v2;
}

No *rotacaoDireita(No *y)
{
    No *x = y->esquerda;
    No *a2 = x->direita;

    x->pai = y->pai;

    if (a2 != NULL)
    {
        a2->pai = y;
    }

    y->pai = x;

    x->direita = y;
    y->esquerda = a2;

    y->altura = 1 + valorMaximo(alturaNo(y->esquerda), alturaNo(y->direita));
    x->altura = 1 + valorMaximo(alturaNo(x->esquerda), alturaNo(x->direita));

    return x;
}

No *rotacaoEsquerda(No *x)
{
    No *y = x->direita;
    No *a2 = y->esquerda;

    y->pai = x->pai;

    if (a2 != NULL)
    {
        a2->pai = x;
    }

    x->pai = y;

    y->esquerda = x;
    x->direita = a2;

    x->altura = 1 + valorMaximo(alturaNo(x->esquerda), alturaNo(x->direita));
    y->altura = 1 + valorMaximo(alturaNo(y->esquerda), alturaNo(y->direita));

    return y;
}

No *inserirNo(No *no, int chave, No *pai)
{
    if (no == NULL)
    {
        return criarNo(chave);
    }

    if (chave < no->chave)
    {
        no->esquerda = inserirNo(no->esquerda, chave, no);
    }
    else if (chave > no->chave)
    {
        no->direita = inserirNo(no->direita, chave, no);
    }
    else
    {
        return no;
    }

    no->altura = 1 + valorMaximo(alturaNo(no->esquerda), alturaNo(no->direita));

    int fatorB = fatorBalanceamentoNo(no);

    if (fatorB > 1 && chave < no->esquerda->chave)
    {
        return rotacaoDireita(no);
    }

    if (fatorB < -1 && chave > no->direita->chave)
    {
        return rotacaoEsquerda(no);
    }

    if (fatorB > 1 && fatorBalanceamentoNo(no->esquerda) < 0)
    {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (fatorB < -1 && fatorBalanceamentoNo(no->direita) > 0)
    {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

No *valorMinimoNo(No *no)
{
    No *noAtual = no;

    while (noAtual != NULL && noAtual->esquerda != NULL)
    {
        noAtual = noAtual->esquerda;
    }

    return noAtual;
}

No *removerNo(No *raiz, int chave)
{
    if (raiz == NULL)
    {
        printf("No nao encontrado na arvore!");
        return NULL;
    }

    if (chave < raiz->chave)
    {
        raiz->esquerda = removerNo(raiz->esquerda, chave);

        if (raiz->esquerda != NULL)
        {
            raiz->esquerda->pai = raiz;
        }
    }
    else if (chave > raiz->chave)
    {
        raiz->direita = removerNo(raiz->direita, chave);

        if (raiz->direita != NULL)
        {
            raiz->direita->pai = raiz;
        }
    }
    else
    {
        if (raiz->esquerda == NULL || raiz->direita == NULL)
        {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {
                raiz->chave = temp->chave;
                raiz->esquerda = temp->esquerda;
                raiz->direita = temp->direita;
                raiz->pai = temp->pai;
            }

            free(temp);
        }
        else
        {
            No *temp = valorMinimoNo(raiz->direita);

            raiz->chave = temp->chave;

            raiz->direita = removerNo(raiz->direita, temp->chave);
        }
    }

    if (raiz == NULL)
    {
        return raiz;
    }

    raiz->altura = 1 + valorMaximo(alturaNo(raiz->esquerda), alturaNo(raiz->direita));

    int fatorB = fatorBalanceamentoNo(raiz);

    if (fatorB > 1 && fatorBalanceamentoNo(raiz->esquerda) >= 0)
    {
        return rotacaoDireita(raiz);
    }

    if (fatorB > 1 && fatorBalanceamentoNo(raiz->esquerda) < 0)
    {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (fatorB < -1 && fatorBalanceamentoNo(raiz->direita) <= 0)
    {
        return rotacaoEsquerda(raiz);
    }

    if (fatorB < -1 && fatorBalanceamentoNo(raiz->direita) > 0)
    {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

No *buscarNo(No *raiz, int chave)
{
    if (raiz == NULL || raiz->chave == chave)
    {
        return raiz;
    }

    if (raiz->chave < chave)
    {
        return buscarNo(raiz->direita, chave);
    }

    return buscarNo(raiz->esquerda, chave);
}

void imprimirArvore(No *raiz, int nivel)
{
    if (raiz == NULL)
    {
        return;
    }

    for (int i = 0; i < nivel; i++)
    {
        printf("  ");
    }

    if (raiz->pai == NULL)
    {
        printf("%d (raiz - FB: %d)\n", raiz->chave, fatorBalanceamentoNo(raiz));
    }
    else
    {
        printf("%d (pai: %d - FB: %d)\n", raiz->chave, raiz->pai->chave, fatorBalanceamentoNo(raiz));
    }

    imprimirArvore(raiz->esquerda, nivel + 1);
    imprimirArvore(raiz->direita, nivel + 1);
}

No *lerNoArquivo(No *raiz, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        return raiz;
    }

    char linha[MAX_LINHA];

    if (fgets(linha, MAX_LINHA, arquivo) == NULL)
    {
        printf("Erro ao ler o arquivo!\n");
        fclose(arquivo);
        return raiz;
    }

    linha[strcspn(linha, "\r\n")] = '\0';

    char *ponto = strchr(linha, '.');

    if (ponto != NULL)
    {
        *ponto = '\0';
    }

    char *token = strtok(linha, ";");

    while (token != NULL)
    {
        int chave;

        if (sscanf(token, "%d", &chave) == 1)
        {
            raiz = inserirNo(raiz, chave, NULL);
        }

        token = strtok(NULL, ";");
    }

    fclose(arquivo);

    return raiz;
}

void buscarNoPaiFilho(No *raiz, int chave)
{
    No *no = buscarNo(raiz, chave);

    if (no == NULL)
    {
        printf("No %d nao encontrado!", chave);
        return;
    }

    printf("\nNo: %d\n", chave);
    printf("Fator de balanceamento: %d\n", fatorBalanceamentoNo(no));

    if (no->pai == NULL)
    {
        printf("Pai: Nenhum");
    }
    else
    {
        printf("Pai: %d (FB: %d)\n", no->pai->chave, fatorBalanceamentoNo(no->pai));
    }

    printf("Filhos:\n");

    if (no->esquerda == NULL)
    {
        printf("- Esquerdo: Nenhum\n");
    }
    else
    {
        printf("- Esquerdo: %d (FB: %d)\n", no->esquerda->chave, fatorBalanceamentoNo(no->esquerda));
    }

    if (no->direita == NULL)
    {
        printf("- Direito: Nenhum\n");
    }
    else
    {
        printf("- Direito: %d (FB: %d)\n", no->direita->chave, fatorBalanceamentoNo(no->direita));
    }
}

void liberarArvore(No *raiz)
{
    if (raiz != NULL)
    {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}