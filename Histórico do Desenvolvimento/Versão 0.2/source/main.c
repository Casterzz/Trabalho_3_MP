#include <stdio.h>
#include "conta_linha.h"
#define TAM 25

int main() {
    int total_linhas;
    char nome_arquivo[TAM];

    printf("Digite o nome do arquivo que se deseja contar as linhas: ");
    scanf("%s", nome_arquivo);

    total_linhas = contador(nome_arquivo);

    if (total_linhas == -1) {
        printf("Nao foi possivel encontrar o arquivo.\n");
        return 0;
    }

    printf("Arquivo %s tem: %d linhas.\n", nome_arquivo, total_linhas);

    return 0;
}
