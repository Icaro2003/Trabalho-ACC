#ifndef TABELA_HASH_H
#define TABELA_HASH_H

typedef struct No
{
    int chave;
    struct No *proximo;
} No;

typedef struct TabelaHash
{
    No **tabela;
    int *chaves;
    int numElementos;
    int tamanho;
} TabelaHash;

TabelaHash *criarTabelaHash(int tamanho);
int divisaoHash(int chave, int tamanho);
int multiplicacaoHash(int chave, int tamanho);
int hash(int chave, int funcaoHash, int tamanho);
void inserirEncademento(TabelaHash *tabelaHash, int chave, int funcaoHash);
void inserirEnderecamentoAberto(TabelaHash *tabelaHash, int chave, int funcaoHash);
void lerArquivo(TabelaHash **tabelaHash, int *tamanhoTabela, int funcaoHash, int metodoColisao);
void removerChave(TabelaHash *tabelaHash, int chave, int funcaoHash, int metodoColisao);
void buscarChave(TabelaHash *tabelaHash, int chave, int funcaoHash, int metodoColisao);
float fatorCarga(TabelaHash *tabelaHash);
void imprimirTabelaHash(TabelaHash *tabelaHash, int metodoColisao);

#endif