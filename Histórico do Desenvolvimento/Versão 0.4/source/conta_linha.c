#include <stdio.h>
#include "conta_linha.h"

int contador(const char *nome_arquivo) {
    int total = 0;
    int total_espaco = 0;
    int total_comentario_1 = 0;
    FILE *file = fopen(nome_arquivo, "r");

    if (file == NULL) {
        return -1;
    }

    total = conta_tudo(file);
    total_espaco = conta_espaco(file);
    total_comentario_1 = conta_comentario_1(file);

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

int conta_espaco(FILE *file) {
    int count = 0, linha_conteudo = 0;
    char leitor;
    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor != '\n')
            linha_conteudo = 1;
        if (leitor == '\n') {
            if (linha_conteudo == 1)
                linha_conteudo = 0;
            else
                count++;
        }
    }
    return count;
}

int conta_comentario_1(FILE *file) {
    int count = 0;
    char leitor, leitor_do_futuro;
    FILE *copia = file;
    leitor_do_futuro = getc(copia);
    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor_do_futuro != EOF)
            leitor_do_futuro = getc(copia);
        if (leitor != '/' && leitor_do_futuro != '/') {
            while (leitor_do_futuro != '\n' && leitor_do_futuro != EOF) {
                leitor = getc(file);
                leitor_do_futuro = getc(copia);
            }
        } else {
            if (leitor == '/' && leitor_do_futuro == '/'){
                count++;
            }
        }
    }
    return count;
}
