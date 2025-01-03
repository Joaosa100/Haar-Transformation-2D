/** 
 * @file haar_transform.c 
 * @brief Implementação da Transformada de Haar 2D para compressão de imagens. 
 * @details Esta aplicação lê uma imagem no formato PGM, aplica a Transformada de Haar 2D para compressão 
 * e salva a imagem resultante. 
 * 
 * @copyright 
 * Copyright (c) 2024 João Vitor Silva Assunção e Maria Augusta Sousa Rios.
 * Todos os direitos reservados. Este código é parte de um projeto acadêmico apra a disciplina de
 * Sistemas Embarcados do Instituto Federal de Educação, Ciência e Tecnologia do Ceará (IFCE).
 * 
 * @license MIT License
 * Este projeto é distribuído sob os termos da MIT License. Consulte o arquivo LICENSE para mais detalhes.
 * 
 * @usage 
 * Para usar esta aplicação, compile o código e execute o binário resultante. A imagem de entrada deve estar no 
 * formato PGM (P2) e ser quadrada (mesma largura e altura). 
 * 
 * @entry 
 * - inputFilename: Nome do arquivo de imagem de entrada em formato PGM. 
 * - outputFilename: Nome do arquivo de imagem de saída após a transformação. 
 * 
 * @output 
 * - Uma imagem comprimida usando a Transformada de Haar 2D, salva no formato PGM.
 * 
 * @authors 
 * João Vitor Silva Assunção
 * Maria Augusta Sousa Rios
 * 
 * @date 
 * 23 de Dezembro de 2024 
 * 
 * @context 
 * Trabalho de Sistemas Embarcados 
 * Desenvolvimento de SW Embarcado
 * Compressão de Imagens com Transformada de Haar 
 * 
 * @target
 * Plataforma Alvo: Linux/Windows
 */
 /*-----------------------------------------------------------------------------------------------------------------------------------------
-- #1.
-- Date: Dez,21,2024
-- Author: João Vitor Silva Assunção
-- Motivo: Remoção dos cálculos envolvendo o sqrt da biblioteca <math.h> 
---------------------------------------------------------------------------------------------------------------------------
-- #2.
-- Date: Dez,22,2024
-- Author: Maria Augusta Sousa Rios
-- Motivo: Adicionada validação de valores para garantir range entre 0 e maxVal e implementado cast explícito de double para int na saída
---------------------------------------------------------------------------------------------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 90 // Tamanho máximo da matriz de entrada e saída

/**
 * @brief Realiza a Transformação de Haar 2D em uma imagem.
 * 
 * @param input Matriz de entrada contendo a imagem original.
 * @param output Matriz de saída contendo a imagem transformada.
 * @param input_size Tamanho da imagem de entrada.
 * @param output_size Tamanho da imagem de saída.
 */
//By João: #1.
void haarTransform2D(double input[MAX_SIZE][MAX_SIZE], double output[MAX_SIZE][MAX_SIZE], int input_size, int *output_size) {
    int half = input_size / 2;
    *output_size = half; //Define tamanho de saída para a metade do tamanho de entrada

    // Calcula apenas os coeficientes de baixa frequência (LL)
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            double a = input[2*i][2*j];
            double b = input[2*i][2*j+1];
            double c = input[2*i+1][2*j];
            double d = input[2*i+1][2*j+1];

            // Calculo dos coeficientes LL
            output[i][j] = (a + b + c + d) / 2.0;
        }
    }
}
//End by João

/**
 * @brief Lê uma imagem PGM (P2) de um arquivo e armazena na matriz.
 * 
 * @param filename Nome do arquivo de imagem de entrada.
 * @param matrix Matriz para armazenar a imagem lida.
 * @param size Ponteiro para armazenar o tamanho da imagem.
 */
void readPGM(const char *filename, double matrix[MAX_SIZE][MAX_SIZE], int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char format[3];
    fscanf(file, "%s", format);
    if (strcmp(format, "P2") != 0) {
        fprintf(stderr, "Formato inválido: esperado P2.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int width, height, maxVal;
    fscanf(file, "%d %d", &width, &height);
    fscanf(file, "%d", &maxVal);

    if (width != height) {
        fprintf(stderr, "Imagem deve ser quadrada para Transformação de Haar.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    *size = width;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }
    fclose(file);
}

/**
 * @brief Salva uma imagem em formato PGM (P2).
 * 
 * @param filename Nome do arquivo para salvar a imagem de saída.
 * @param matrix Matriz contendo a imagem a ser salva.
 * @param size Tamanho da imagem.
 * @param maxVal Valor máximo da escala de cinza.
 */
void savePGM(const char *filename, double matrix[MAX_SIZE][MAX_SIZE], int size, int maxVal) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao salvar o arquivo");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "P2\n");
//By Maria: #2
    fprintf(file, "%d %d\n", size, size);  // usando o tamanho reduzido
    fprintf(file, "%d\n", maxVal);

    for (int i = 0; i < size; i++) {  // Loop apenas no tamanho reduzido
        for (int j = 0; j < size; j++) {
            double val = matrix[i][j];
            val = val < 0 ? 0 : (val > maxVal ? maxVal : val);
            fprintf(file, "%d ", (int)val);
//End by João
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

/**
 * @brief Função principal que executa a transformação de Haar em uma imagem PGM
 * 
 * Lê uma imagem PGM, aplica a Transformação de Haar 2D e salva a imagem resultante.
 * 
 * @return int Código de status de execução
 */
int main() {
    const char *inputFilename = "../images/pgm/animal3.pgm";
    const char *outputFilename = "../images/pgm_output/animal3Imp.pgm";
    int input_size, output_size;
    double input_image[MAX_SIZE][MAX_SIZE];
    double output_image[MAX_SIZE][MAX_SIZE];

    // Lê a imagem de entrada no formato PGM
    readPGM(inputFilename, input_image, &input_size);
    printf("Imagem lida com sucesso. Aplicando Transformacao de Haar...\n");

    // Aplica a Transformação de Haar 2D
    haarTransform2D(input_image, output_image, input_size, &output_size);

    printf("Transformacao de Haar concluida. Salvando resultado...\n");
    // Salva a imagem transformada no formato PGM
    savePGM(outputFilename, output_image, output_size, 255);
    printf("Arquivo salvo em '%s'.\n", outputFilename);

    return 0;
}