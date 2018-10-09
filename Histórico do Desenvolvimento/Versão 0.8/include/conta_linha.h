/*
Copyright
Nome: Victor Eduardo Fernandes Castor
Matricula: 170115127
Data: 06/10/18
Projeto Contador de Linhas
*/

#include <stdio.h>

struct Flag {
    int atencao;
    int linha_morta;
    int ajustador;
    int linha_conteudo;
};

/*Declaração de todas as funções a serem usadas*/

int contador(const char *nome_arquivo);

int conta_tudo(FILE *file);

int conta_espaco(FILE *file);

int conta_comentario_1(FILE *file);

int conta_comentario_2(FILE *file);
