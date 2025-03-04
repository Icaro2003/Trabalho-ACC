#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_prioridade.h"

FilaPrioridade *criarFilaPrioridade(int capacidade)
{
    FilaPrioridade *fp = (FilaPrioridade *)malloc(sizeof(FilaPrioridade));

    if (fp == NULL)
    {
        printf("Nao foi possivel alocar memoria para a fila de prioridade!");
        exit(1);
    }

    fp->elementos = (ElementoFilaPrioridade *)malloc(capacidade * sizeof(ElementoFilaPrioridade));

    if (fp->elementos == NULL)
    {
        printf("Nao foi possível alocar memoria para os elementos da fila!");
        free(fp);
        exit(1);
    }

    fp->tamanho = 0;
    fp->capacidade = capacidade;

    return fp;
}

void removerFilaPrioridade(FilaPrioridade *fp)
{
    if (fp != NULL)
    {
        free(fp->elementos);
        free(fp);
    }
}

void troca(ElementoFilaPrioridade *e1, ElementoFilaPrioridade *e2)
{
    ElementoFilaPrioridade temp = *e1;
    *e1 = *e2;
    *e2 = temp;
}

int posNoPai(int posicao)
{
    return (posicao - 1) / 2;
}

int posNoFilhoEsquerdo(int posicao)
{
    return 2 * posicao + 1;
}

int posNoFilhoDireito(int posicao)
{
    return 2 * posicao + 2;
}

void reorganizarFilaPrioridadeMaximo(FilaPrioridade *fp, int posicao)
{
    int maior = posicao;
    int esquerdo = posNoFilhoEsquerdo(posicao);
    int direito = posNoFilhoDireito(posicao);

    if (esquerdo < fp->tamanho && fp->elementos[esquerdo].prioridade > fp->elementos[maior].prioridade)
    {
        maior = esquerdo;
    }

    if (direito < fp->tamanho && fp->elementos[direito].prioridade > fp->elementos[maior].prioridade)
    {
        maior = direito;
    }

    if (maior != posicao)
    {
        troca(&fp->elementos[posicao], &fp->elementos[maior]);
        reorganizarFilaPrioridadeMaximo(fp, maior);
    }
}

int inserirElemento(FilaPrioridade *fp, const char *nome, int prioridade)
{
    if (fp->tamanho >= fp->capacidade)
    {
        return 0;
    }

    for (int i = 0; i < fp->tamanho; i++)
    {
        if (strcmp(fp->elementos[i].nome, nome) == 0)
        {
            return 0;
        }
    }
    

    int pos = fp->tamanho;
    strncpy(fp->elementos[pos].nome, nome, MAX_STRING - 1);
    fp->elementos[pos].nome[MAX_STRING - 1] = '\0';
    fp->elementos[pos].prioridade = prioridade;
    fp->tamanho++;

    while (pos > 0 && fp->elementos[posNoPai(pos)].prioridade < fp->elementos[pos].prioridade)
    {
        troca(&fp->elementos[pos], &fp->elementos[posNoPai(pos)]);
        pos = posNoPai(pos);
    }

    return 1;
}

ElementoFilaPrioridade removerMaiorElemento(FilaPrioridade *fp)
{
    if (fp->tamanho <= 0)
    {
        ElementoFilaPrioridade vazio = {"", -1};
        return vazio;
    }

    if (fp->tamanho == 1)
    {
        fp->tamanho--;
        return fp->elementos[0];
    }

    ElementoFilaPrioridade raiz = fp->elementos[0];

    fp->elementos[0] = fp->elementos[fp->tamanho - 1];
    fp->tamanho--;
    reorganizarFilaPrioridadeMaximo(fp, 0);

    return raiz;
}

void imprimirFilaPrioridade(FilaPrioridade *fp)
{
    if (fp->tamanho == 0)
    {
        printf("Fila de prioridade vazia!\n");
        return;
    }

    printf("Capacidade: %d\nQuantidade de elementos: %d\n\n", fp->capacidade, fp->tamanho);

    int altura = 0;
    int tamanho = fp->tamanho;

    while (tamanho > 0)
    {
        tamanho = tamanho / 2;
        altura++;
    }

    int nivel = 0;
    int nosEmNivel = 1;
    int cont = 0;

    for (int i = 0; i < fp->tamanho; i++)
    {
        if (cont == 0)
        {
            printf("Nivel: %d", nivel);
        }

        printf("[%s: %d] ", fp->elementos[i].nome, fp->elementos[i].prioridade);
        cont++;

        if (cont == nosEmNivel)
        {
            printf("\n");
            nivel++;
            nosEmNivel *= 2;
            cont = 0;
        }
    }

    if (cont > 0)
    {
        printf("\n");
    }

    for (int i = 0; i < fp->tamanho; i++)
    {
        printf("%d. %s\nPrioridade: %d\n", i + 1, fp->elementos[i].nome, fp->elementos[i].prioridade);
    }
}

int buscarPosicaoElemento(FilaPrioridade *fp, const char *nome)
{
    for (int i = 0; i < fp->tamanho; i++)
    {
        if (strcmp(fp->elementos[i].nome, nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

int alterarPrioridade(FilaPrioridade *fp, const char *nome, int novaPrioridade)
{
    int pos = buscarPosicaoElemento(fp, nome);

    if (pos == -1)
    {
        return 0;
    }

    int prioridadeAnterior = fp->elementos[pos].prioridade;
    fp->elementos[pos].prioridade = novaPrioridade;

    if (novaPrioridade > prioridadeAnterior)
    {
        while (pos > 0 && fp->elementos[posNoPai(pos)].prioridade < fp->elementos[pos].prioridade)
        {
            troca(&fp->elementos[pos], &fp->elementos[posNoPai(pos)]);
            pos = posNoPai(pos);
        }
    }
    else if (novaPrioridade < prioridadeAnterior)
    {
        reorganizarFilaPrioridadeMaximo(fp, pos);
    }

    return 1;
}

void lerArquivo(FilaPrioridade **fp, int *capacidade, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int numElementos;
    char linha[MAX_LINHA];

    if (fgets(linha, MAX_LINHA, arquivo) == NULL || sscanf(linha, "%d", &numElementos) != 1)
    {
        printf("Erro ao ler o numero de elementos do arquivo!\n");
        fclose(arquivo);
        return;
    }

    if (fgets(linha, MAX_LINHA, arquivo) == NULL || sscanf(linha, "%d", capacidade) != 1)
    {
        printf("Erro ao ler a capacidade do arquivo!\n");
        fclose(arquivo);
        return;
    }

    if (*fp != NULL)
    {
        removerFilaPrioridade(*fp);
    }

    *fp = criarFilaPrioridade(*capacidade);

    for (int i = 0; i < numElementos; i++)
    {
        if (fgets(linha, MAX_LINHA, arquivo) == NULL)
        {
            break;
        }
        
        linha[strcspn(linha, "\n")] = '\0';
        char nome[MAX_STRING];
        int prioridade;
        char *virgula = strchr(linha, ',');

        if (virgula != NULL)
        {
            int tamanhoNome = virgula - linha;
            if (tamanhoNome >= MAX_STRING)
            {
                tamanhoNome = MAX_STRING - 1;
            }
            
            strncpy(nome, linha, tamanhoNome);
            nome[tamanhoNome] = '\0';
            
            prioridade = atoi(virgula + 1);
            
            inserirElemento(*fp, nome, prioridade);
        }
    }

    fclose(arquivo);
}