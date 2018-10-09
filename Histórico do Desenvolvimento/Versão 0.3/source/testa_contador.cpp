#include <gtest/gtest.h>
#include "conta_linha.c"

/*Conjunto dos testes*/

TEST(contador, teste) {
    ASSERT_EQ(23, contador("main.c"));
    ASSERT_EQ(-1, contador("conta"));
}

TEST(conta_espaco, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = "main.c";
    FILE *file = fopen(nome_arquivo, "r");
    ASSERT_EQ(5, conta_espaco(file));
    fclose(file);
}

TEST(conta_comentario_1, teste) {
    const int TAM = 25;
    char nome_arquivo[TAM] = "main.c";
    FILE *file = fopen(nome_arquivo, "r");
    ASSERT_EQ(2, conta_comentario_1(file));
    fclose(file);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
