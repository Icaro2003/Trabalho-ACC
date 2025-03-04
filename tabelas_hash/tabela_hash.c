#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tabela_hash.h"

TabelaHash *criarTabelaHash(int tamanho)
{
    TabelaHash *tabelaHash = (TabelaHash *)malloc(sizeof(TabelaHash));
    tabelaHash->chaves = (int *)malloc(tamanho * sizeof(int));
    tabelaHash->numElementos = 0;
    tabelaHash->tabela = (No **)malloc(tamanho * sizeof(No *));
    tabelaHash->tamanho = tamanho;

    for (int i = 0; i < tamanho; i++)
    {
        tabelaHash->tabela[i] = NULL;
        tabelaHash->chaves[i] = -1;
    }

    return tabelaHash;
}

int divisaoHash(int chave, int tamanho)
{
    return chave % tamanho;
}

int multiplicacaoHash(int chave, int tamanho)
{
    const double RAZAO_AUREA = (sqrt(5) - 1.0) / 2.0;
    const double A = RAZAO_AUREA - (int)RAZAO_AUREA;
    return (int)(tamanho * fmod(chave * A, 1.0));
}

int hash(int chave, int funcaoHash, int tamanho)
{
    if (funcaoHash == 1)
    {
        return divisaoHash(chave, tamanho);
    }
    else
    {
        return multiplicacaoHash(chave, tamanho);
    }
}

void inserirEncademento(TabelaHash *tabelaHash, int chave, int funcaoHash)
{
    int indice = hash(chave, funcaoHash, tabelaHash->tamanho);
    No *novoNo = (No *)malloc(sizeof(No));

    novoNo->chave = chave;
    novoNo->proximo = tabelaHash->tabela[indice];
    tabelaHash->tabela[indice] = novoNo;
    tabelaHash->numElementos++;
}

void inserirEnderecamentoAberto(TabelaHash *tabelaHash, int chave, int funcaoHash)
{
    int indice = hash(chave, funcaoHash, tabelaHash->tamanho);
    int i = 0;

    while (tabelaHash->chaves[(indice + i) % tabelaHash->tamanho] != -1)
    {
        i++;
    }

    tabelaHash->chaves[(indice + i) % tabelaHash->tamanho] = chave;
    tabelaHash->numElementos++;
}

void lerArquivo(TabelaHash **tabelaHash, int *tamanhoTabela, int funcaoHash, int metodoColisao)
{
    FILE *arquivo = fopen("input.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    if (fscanf(arquivo, "%d", tamanhoTabela) != 1)
    {
        printf("Erro ao ler o tamanho da tabela!\n");
        fclose(arquivo);
        return;
    }

    *tabelaHash = criarTabelaHash(*tamanhoTabela);

    int c;
    while ((c = fgetc(arquivo)) != '\n' && c != EOF)
        ;

    char linha[1024] = {0};
    if (fgets(linha, sizeof(linha), arquivo) == NULL)
    {
        printf("Erro ao ler os valores da tabela!\n");
        fclose(arquivo);
        return;
    }
    linha[strcspn(linha, "\r\n")] = 0;

    char *token = strtok(linha, ",");

    while (token != NULL)
    {
        while (*token == ' ')
        {
            token++;
        }

        size_t len = strlen(token);
        if (len > 0 && token[len - 1] == '.')
        {
            token[len - 1] = '\0';
        }

        if (strlen(token) > 0)
        {
            int chave = atoi(token);

            if (metodoColisao == 1)
            {
                inserirEncademento(*tabelaHash, chave, funcaoHash);
            }
            else
            {
                inserirEnderecamentoAberto(*tabelaHash, chave, funcaoHash);
            }
        }

        token = strtok(NULL, ",");
    }

    fclose(arquivo);
}

void removerChave(TabelaHash *tabelaHash, int chave, int funcaoHash, int metodoColisao)
{
    if (tabelaHash == NULL)
    {
        printf("Tabela vazia, não é possível remover!\n");
        return;
    }

    int indice = hash(chave, funcaoHash, tabelaHash->tamanho);

    if (metodoColisao == 1)
    {
        No *noAtual = tabelaHash->tabela[indice];
        No *noAnterior = NULL;

        while (noAtual != NULL)
        {
            if (noAtual->chave == chave)
            {
                if (noAnterior == NULL)
                {
                    tabelaHash->tabela[indice] = noAtual->proximo;
                }
                else
                {
                    noAnterior->proximo = noAtual->proximo;
                }

                free(noAtual);
                tabelaHash->numElementos--;
                printf("Chave removida: %d\n", chave);
                return;
            }

            noAnterior = noAtual;
            noAtual = noAtual->proximo;
        }

        printf("Chave %d nao encontrada!\n", chave);
    }
    else
    {
        int i = 0;

        while (i < tabelaHash->tamanho)
        {
            int novoIndice = (indice + i) % tabelaHash->tamanho;

            if (tabelaHash->chaves[novoIndice] == chave)
            {
                tabelaHash->chaves[novoIndice] = -1;
                tabelaHash->numElementos--;
                return;
            }
            else if (tabelaHash->chaves[novoIndice] == -1)
            {
                break;
            }

            i++;
        }

        printf("Chave %d nao encontrada!\n", chave);
    }
}

void buscarChave(TabelaHash *tabelaHash, int chave, int funcaoHash, int metodoColisao)
{
    int indice = hash(chave, funcaoHash, tabelaHash->tamanho);
    int colisoes = 0;

    if (metodoColisao == 1)
    {
        No *noAtual = tabelaHash->tabela[indice];

        while (noAtual != NULL)
        {
            if (noAtual->chave == chave)
            {
                printf("Chave %d encontrada no indice %d\nColisoes: %d\n", chave, indice, colisoes);
                return;
            }

            noAtual = noAtual->proximo;
            colisoes++;
        }

        printf("Chave %d nao encontrada!\nColisoes: %d\n", chave, colisoes);
    }
    else
    {
        int i = 0;

        while (i < tabelaHash->tamanho)
        {
            int novoIndice = (indice + i) % tabelaHash->tamanho;

            if (tabelaHash->chaves[novoIndice] == chave)
            {
                printf("Chave %d encontrada no indice %d\nColisoes: %d\n", chave, novoIndice, colisoes);
                return;
            }
            else if (tabelaHash->chaves[novoIndice] == -1)
            {
                break;
            }

            i++;
            colisoes++;

            if (i >= tabelaHash->tamanho)
            {
                break;
            }
        }

        printf("Chave %d nao encontrada!\nColisoes: %d\n", chave, colisoes);
    }
}

float fatorCarga(TabelaHash *tabelaHash)
{
    return (float)tabelaHash->numElementos / tabelaHash->tamanho;
}

void imprimirTabelaHash(TabelaHash *tabelaHash, int metodoColisao)
{
    printf("Estado Atual da Tabela Hash:\n");

    for (int i = 0; i < tabelaHash->tamanho; i++)
    {
        printf("Indice %d: ", i);

        if (metodoColisao == 1)
        {
            No *noAtual = tabelaHash->tabela[i];

            if (noAtual == NULL)
            {
                printf("Vazio\n");
            }
            else
            {
                while (noAtual)
                {
                    printf("%d", noAtual->chave);

                    if (noAtual->proximo)
                    {
                        printf(" -> ");
                    }

                    noAtual = noAtual->proximo;
                }
                printf("\n");
            }
        }
        else
        {
            if (tabelaHash->chaves[i] != -1)
            {
                printf("%d\n", tabelaHash->chaves[i]);
            }
            else
            {
                printf("Vazio\n");
            }
        }
    }
}