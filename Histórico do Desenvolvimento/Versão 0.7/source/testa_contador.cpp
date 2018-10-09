#include <gtest/gtest.h>
#include "conta_linha.c"

/*Conjunto dos testes*/

TEST(contador, teste) {
    ASSERT_EQ(16, contador("main.c"));
    ASSERT_EQ(-1, contador("conta"));
}

TEST(conta_tudo, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = "main.c";
    FILE *file = fopen(nome_arquivo, "r");
    ASSERT_EQ(38, conta_tudo(file));
    fclose(file);
}

TEST(conta_espaco, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = "main.c";
    FILE *file = fopen(nome_arquivo, "r");
    ASSERT_EQ(11, conta_espaco(file));
    fclose(file);
}

TEST(conta_comentario_1, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = "main.c";
    FILE *file = fopen(nome_arquivo, "r");
    ASSERT_EQ(5, conta_comentario_1(file));
    fclose(file);
}

TEST(conta_comentario_2, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = "main.c";
    FILE *file = fopen(nome_arquivo, "r");
    ASSERT_EQ(6, conta_comentario_2(file));
    fclose(file);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
