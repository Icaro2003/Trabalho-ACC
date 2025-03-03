#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#define MAX_STRING 50
#define MAX_LINHA 1024

typedef struct
{
    char nome[MAX_STRING];
    int prioridade;
} ElementoFilaPrioridade;

typedef struct
{
    ElementoFilaPrioridade *elementos;
    int tamanho;
    int capacidade;
} FilaPrioridade;

FilaPrioridade *criarFilaPrioridade(int capacidade);
void removerFilaPrioridade(FilaPrioridade *fp);
void troca(ElementoFilaPrioridade *e1, ElementoFilaPrioridade *e2);
int posNoPai(int posicao);
int posNoFilhoEsquerdo(int posicao);
int posNoFilhoDireito(int posicao);
void reorganizarFilaPrioridadeMaximo(FilaPrioridade *fp, int posicao);
int inserirElemento(FilaPrioridade *fp, const char *nome, int prioridade);
ElementoFilaPrioridade maiorElemento(FilaPrioridade *fp);
void imprimirFilaPrioridade(FilaPrioridade *fp);
int buscarPosicaoElemento(FilaPrioridade *fp, const char *nome);
int alterarPrioridade(FilaPrioridade *fp, const char *nome, int novaPrioridade);
void lerArquivo(FilaPrioridade **fp, int *capacidade, const char *nomeArquivo);

#endif