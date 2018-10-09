#include <stdio.h>
#include "conta_linha.h"

int contador(const char *nome_arquivo) {
    int total = 0;
    int total_espaco;
    int total_comentario_1;
    int total_comentario_2;

    FILE *file = fopen(nome_arquivo, "r");

    if (file == NULL) {
        return -1;
    }

    total = conta_tudo(file);
    rewind(file);
    total_espaco = conta_espaco(file);
    rewind(file);
    total_comentario_1 = conta_comentario_1(file);
    rewind(file);
    total_comentario_2 = conta_comentario_2(file);

    total = total - total_espaco - total_comentario_1 - total_comentario_2;

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
        if (leitor != '\n'){
            if (leitor != ' ')
                linha_conteudo = 1;
        }
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
    int count = 0, atencao = 0;
    char leitor;
    FILE *copia = file;
    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor != '/' && leitor != ' ') {
            while (leitor != '\n' && leitor != EOF) {
                leitor = getc(file);
            }
            atencao = 0;
        } else {
            if (leitor == '/') {
                atencao++;
                if (atencao == 2) {
                    count++;
                }
            }
        }
    }
    return count;
}

int conta_comentario_2(FILE *file) {
    int count = 0, atencao = 0, nivel_atencao = 0, linha_morta = 0, ajustador = 0;
    char leitor;
    FILE *copia = file;
    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor != '/' && leitor != ' ' && leitor != '*') {
            if (leitor != ' ' && atencao == 0) {
                linha_morta = 1;
            }
            if (atencao == 1)
                atencao = 0;
            if (atencao == 3)
                atencao = 2;

            if (ajustador == 1 && leitor == '\n' && atencao == 2) {
                count--;  // anulando espaco em branco
            }

            ajustador = 0;

            while (leitor != '\n' && leitor != EOF && leitor != '*' && leitor != '/') {
                leitor = getc(file);
            }

            if (leitor == '\n' && atencao == 2)
                ajustador = 1;  // para um caso especifico, garante que ao pular uma linha em um comentario com o conteudo logo em seguida sendo */, ele contabiliza 

            if (leitor == '*' && atencao == 2)
                atencao = 3;
            if (leitor == '/' && atencao == 0)
                atencao = 1;

            if (linha_morta == 0) {
                if ((atencao == 2) || (atencao == 3))
                    count++;
            } else {
                if (leitor == '\n')
                    linha_morta = 0;
            }
        } else {
            if (leitor == '/' && atencao == 0) {
                atencao = 1;
            } else {
                if (leitor == '/' && atencao == 3) {
                    atencao = 0;
                    if (ajustador == 1) {
                        count++;
                    }
                }
            }
            if (leitor == '*' && atencao == 1) {
                atencao = 2;
            } else {
                if (leitor == '*' && atencao == 2) {
                    atencao = 3;
                }
            }
        }
    }
    return count;
}

//2 eh estavel