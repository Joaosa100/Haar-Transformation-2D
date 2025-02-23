#include <iostream>

#define N 8  // Tamanho da matriz
#define B 2  // Tamanho do bloco (2x2)

void processarMatriz(int matriz[N][N]) {
    int numBlocos = (N / B) * (N / B); // Total de blocos 2x2

    for (int idx = 0; idx < numBlocos; idx++) {
        int blocoLinha = (idx / (N / B)) * B; // Linha do bloco -> Se idx = 5 -> [(5 / (8/2)) * 2] --> [(5/4)*2] --> 1*2 --> 2
        int blocoColuna = (idx % (N / B)) * B; // Coluna do bloco

        // Soma os valores do bloco 2x2
        int soma = matriz[blocoLinha][blocoColuna] + matriz[blocoLinha][blocoColuna + 1] + matriz[blocoLinha + 1][blocoColuna] + matriz[blocoLinha + 1][blocoColuna + 1];
        
        //if, else if com a constricao
        soma /= 2;

        std::cout << soma << "\t";

        // SIsso esta fazendo ele percorrer linhna por linha, tenho qu efazer na mao

        if ((idx + 1) % (N / B) == 0) {
            std::cout << std::endl;
        }
    }
}

int main() {
    int matriz[N][N] = {
        {76, 56, 47, 40, 14, 21, 49, 82},
        {12, 48, 39, 93, 49, 29, 27, 41},
        {33, 57, 72, 68, 15, 91, 23, 77},
        {44, 26, 63, 34, 80, 55, 60, 98},
        {11, 88, 30, 90, 66, 42, 13, 24},
        {31, 19, 87, 50, 28, 53, 39, 99},
        {69, 79, 20, 64, 74, 35, 95, 85},
        {54, 18, 22, 70, 36, 45, 67, 81}
    };

    processarMatriz(matriz);
    return 0;
}
/*
96      109     56      99
80      118     120     129
74      128     94      87
110     88      95      164
*/