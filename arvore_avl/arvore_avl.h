#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#define MAX_LINHA 1024

typedef struct No
{
    int chave;
    int altura;
    struct No *esquerda;
    struct No *direita;
    struct No *pai;
} No;

No *criarNo(int chave);
int alturaNo(No *no);
int fatorBalanceamentoNo(No *no);
int valorMaximo(int a, int b);
No *rotacaoDireita(No *y);
No *rotacaoEsquerda(No *x);
No *inserirNo(No *no, int chave, No *pai);
No *valorMinimoNo(No *no);
No *removerNo(No *raiz, int chave);
No *buscarNo(No *raiz, int chave);
void imprimirArvore(No *raiz, int nivel);
No *lerNoArquivo(No *raiz, const char *nomeArquivo);
void buscarNoPaiFilho(No *raiz, int chave);
void liberarArvore(No *raiz);

#endif