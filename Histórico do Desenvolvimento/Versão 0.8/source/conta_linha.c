/*
Copyright
Nome: Victor Eduardo Fernandes Castor
Matricula: 170115127
Data: 06/10/18
Projeto Contador de Linhas
*/

#include <stdio.h>
#include "conta_linha.h"

/*
A função contador é responsável por abrir o arquivo, o qual se deseja contar linha,
e chamar as funções secundárias que contarão linhas específicas. No final o programa
fará um rápida conta para dizer quantas linhas de código o arquivo de fato contém.
A função retorna -1 caso não consiga abrir o arquivo, ou outro número, que significa
o total efetivo de linhas de códigos escrito.
*/

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

/*
Função que conta todas as linhas do código, sem exceção.
*/

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

/*
Função que conta quantas linhas que contém somente espaços ou quebra de linhas.
*/

int conta_espaco(FILE *file) {
    int count = 0;
    struct Flag flag;
    flag.linha_conteudo = 0;
    char leitor;
    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor != '\n') {
            if (leitor != ' ')
                flag.linha_conteudo = 1;
        }  // If
        if (leitor == '\n') {
            if (flag.linha_conteudo == 1)
                flag.linha_conteudo = 0;
            else
                count++;
        }  // If
    }  // For
    return count;
}

/*
Função responsável por contar quantas linhas de comentários do tipo "//" o arquivo
contém. Linhas que contém ambos, código e comentário não é contabilizado como comentário.

Códigos da flag atencao:
0- Não há comentário na linha.
1- Há um "/" na linha, podendo significar comentário.
2- Há um "/" seguido de outro "/" significando comentário.
*/

int conta_comentario_1(FILE *file) {
    int count = 0;
    struct Flag flag;
    flag.atencao = 0;
    char leitor;
    FILE *copia = file;
    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor != '/' && leitor != ' ') {
            while (leitor != '\n' && leitor != EOF)
                leitor = getc(file);
            flag.atencao = 0;
        } else {
            if (leitor == '/') {
                flag.atencao++;
                if (flag.atencao == 2)
                    count++;
            }  // If
        }  // If-Else
    }  // For
    return count;
}

/*
Função responsável por contar quantas linhas de comentários do tipo "/*" o arquivo
contém. Linhas que contém ambos, código e comentário não é contabilizado como comentário.
Obs.: A variável flag.atencao é responsável por mostrar o estado do comentário,
se houve um "/" ou "*" a atencao pode mudar por significar inicio, fim ou falso alarme
de um comentario.
A variável flag.ajustador serve para auxiliar o código a perceber quando, dentro de um comentário
há uma linha em branco.
A vaŕiável flag.linha_morta auxilia o programa de forma a informar se uma linha começa com código
válido (que não é comentário).

Códigos da flag atencao:
0- Acabou de sair de um comentário/Não está dentro de comentário. (Estável).
1- Inicio de "/", pode indicar inicio de comentário. (Instável, sujeito a voltar para 0).
2- "*" Seguido de "/", indicando inicio verídico de um comentário. (Estável).
3- "*" Estando dentro de um comentário, pode significar fim de comentário. (Instável, sujeito a voltar para 2).

Códigos da flag linha_morta:
0- Não há código na linha (ainda)
1- Há código que não é comentário na linha.
*/

int conta_comentario_2(FILE *file) {
    int count = 0;
    struct Flag flag;
    flag.atencao = 0, flag.linha_morta = 0, flag.ajustador = 0;
    char leitor;
    FILE *copia = file;
    for (leitor = getc(file); leitor != EOF; leitor = getc(file)) {
        if (leitor != '/' && leitor != ' ' && leitor != '*') {
            if (leitor != ' ' && flag.atencao == 0)
                flag.linha_morta = 1;

            if (flag.atencao == 1)
                flag.atencao = 0;
            if (flag.atencao == 3)
                flag.atencao = 2;

            if (flag.ajustador == 1 && leitor == '\n' && flag.atencao == 2)
                count--;  // Anula espaço em branco.

            flag.ajustador = 0;

            while (leitor != '\n' && leitor != EOF && leitor != '*' && leitor != '/')
                leitor = getc(file);

            if (leitor == '\n' && flag.atencao == 2)
                flag.ajustador = 1;

            if (leitor == '*' && flag.atencao == 2)
                flag.atencao = 3;
            if (leitor == '/' && flag.atencao == 0)
                flag.atencao = 1;

            if (flag.linha_morta == 0) {
                if ((flag.atencao == 2) || (flag.atencao == 3))
                    count++;
            } else {
                if (leitor == '\n')
                    flag.linha_morta = 0;
            }  // Else-If
        } else {
            if (leitor == '/') {
                if (flag.atencao == 0)
                    flag.atencao = 1;
                if (flag.atencao == 3) {
                    flag.atencao = 0;
                    if (flag.ajustador == 1)
                        count++;
                }  // If
            } else {
                if (leitor == '*') {
                    if (flag.atencao == 1)
                        flag.atencao = 2;
                    if (flag.atencao == 2)
                        flag.atencao = 3;
                }  // If
            }
        }  // Else-If
    }  // For
    return count;
}
