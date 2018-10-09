#include <stdio.h>
#include "conta_linha.h"

int contador(const char *nome_arquivo) {
    int total = 0;
    FILE *file = fopen(nome_arquivo, "r");

    if (file == NULL) {
        return -1;
    }

    total = conta_tudo(file);

    fclose(file);
    return total;
}

int conta_tudo(FILE *file) {
    int count = 0;
    char leitor;
    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor == '\n') {
            count++;
        }
    }
    return count;
}
