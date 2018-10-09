#include <stdio.h>
#include "conta_linha.h"

int contador(const char *nome_arquivo) {
    int count = 0;
    char leitor;
    FILE *file = fopen(nome_arquivo, "r");

    if (file == NULL) {
        return -1;
    }

    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor == '\n') {
            count++;
        }
    }

    fclose(file);
    return count;
}
