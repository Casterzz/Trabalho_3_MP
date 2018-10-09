/*
Copyright
Nome: Victor Eduardo Fernandes Castor
Matricula: 170115127
Data: 06/10/18
Projeto Contador de Linhas
*/

#include <gtest/gtest.h>
#include "conta_linha.c"

#define NOME "conta_linha.c"

/*Conjunto dos testes*/

TEST(contador, teste) {
    EXPECT_EQ(132, contador(NOME));
    EXPECT_EQ(-1, contador("NOME_INCORRETO"));
}

TEST(conta_tudo, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = NOME;
    FILE *file = fopen(nome_arquivo, "r");
    EXPECT_EQ(205, conta_tudo(file));
    fclose(file);
}

TEST(conta_espaco, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = NOME;
    FILE *file = fopen(nome_arquivo, "r");
    EXPECT_EQ(26, conta_espaco(file));
    fclose(file);
}

TEST(conta_comentario_1, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = NOME;
    FILE *file = fopen(nome_arquivo, "r");
    EXPECT_EQ(0, conta_comentario_1(file));
    fclose(file);
}

TEST(conta_comentario_2, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = NOME;
    FILE *file = fopen(nome_arquivo, "r");
    EXPECT_EQ(47, conta_comentario_2(file));
    fclose(file);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
