#include <stdio.h>
#include <stdlib.h>
#include "tabela_hash.h"

int main()
{
    int opcao, tamanhoTabela, metodoColisao, funcaoHash, chave;

    TabelaHash *tabelaHash;

    printf("Tabela Hash\n");
    
    int valorCorreto;

    do
    {
        printf("\nEscolha a funcao de hash:\n");
        printf("1 - Divisao\n2 - Multiplicacao\n");
        scanf("%d", &funcaoHash);

        printf("\n");

        printf("Escolha o metodo de colisao:\n");
        printf("1 - Encadeado\n2 - Enderecamento aberto\n");
        scanf("%d", &metodoColisao);

        valorCorreto = (funcaoHash < 1 || funcaoHash > 2) || (metodoColisao < 1 || metodoColisao > 2) ? 1 : 0;
    } while (valorCorreto);

    do
    {
        printf("\nFuncionalidades da Tabela Hash\n");
        printf("1. Inserir elementos por arquivo\n");
        printf("2. Inserir elementos manualmente\n");
        printf("3. Remover elementos da tabela\n");
        printf("4. Exibir Tabela Hash\n");
        printf("5. Buscar Chave\n");
        printf("6. Exibir Fator de Carga\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            lerArquivo(&tabelaHash, &tamanhoTabela, funcaoHash, metodoColisao);
            printf("\nDados do arquivo carregados!\n");
            break;
        case 2:
            printf("Digite a chave para inserir na tabela: ");
            scanf("%d", &chave);

            if (metodoColisao == 1)
            {
                inserirEncademento(tabelaHash, chave, funcaoHash);
            }
            else
            {
                inserirEnderecamentoAberto(tabelaHash, chave, funcaoHash);
            }
            break;
        case 3:
            printf("Digite a chave para remover da tabela: ");
            scanf("%d", &chave);
            removerChave(tabelaHash, chave, funcaoHash, metodoColisao);
            break;
        case 4:
            imprimirTabelaHash(tabelaHash, metodoColisao);
            printf("Aperte ENTER para entrar no menu");
            getchar();
            getchar();
            break;
        case 5:
            printf("Digite a chave para buscar na tabela: ");
            scanf("%d", &chave);
            buscarChave(tabelaHash, chave, funcaoHash, metodoColisao);
            break;
        case 6:
            printf("Fator de carga da tabela: %g\n", fatorCarga(tabelaHash));
            break;
        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!");
            break;
        }
    } while (opcao != 0);

    return 0;
}