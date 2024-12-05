#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 90  // Tamanho máximo da imagem, defina de acordo com sua necessidade

// Função para aplicar Transformação de Haar em uma dimensão
void haarTransform1D(double data[], int length) {
    double temp[MAX_SIZE];  // Usando um array estático para armazenar os dados temporários
    int half = length / 2;

    for (int i = 0; i < half; i++) {
        temp[i] = (data[2 * i] + data[2 * i + 1]) / sqrt(2.0);
        temp[half + i] = (data[2 * i] - data[2 * i + 1]) / sqrt(2.0);
    }

    for (int i = 0; i < length; i++) {
        data[i] = temp[i];
    }
}

// Função para aplicar Transformação de Haar em duas dimensões
void haarTransform2D(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    double temp[MAX_SIZE];  // Usando um array estático para armazenar os dados temporários

    // Transformação nas linhas
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[j] = matrix[i][j];
        }
        haarTransform1D(temp, size);
        for (int j = 0; j < size; j++) {
            matrix[i][j] = temp[j];
        }
    }

    // Transformação nas colunas
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            temp[i] = matrix[i][j];
        }
        haarTransform1D(temp, size);
        for (int i = 0; i < size; i++) {
            matrix[i][j] = temp[i];
        }
    }
}

// Função para ler uma imagem PGM P2
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

// Função para salvar uma imagem PGM P2
void savePGM(const char *filename, double matrix[MAX_SIZE][MAX_SIZE], int size, int maxVal) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao salvar o arquivo");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", size, size);
    fprintf(file, "%d\n", maxVal);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int val = (int)round(matrix[i][j]);
            val = val < 0 ? 0 : (val > maxVal ? maxVal : val); // Limitar dentro do intervalo
            fprintf(file, "%d ", val);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    const char *inputFilename = "../images/igirl.pgm";
    const char *outputFilename = "../compressedImages/output.pgm";

    int size;
    double image[MAX_SIZE][MAX_SIZE];  // Usando array estático para a imagem

    readPGM(inputFilename, image, &size);

    printf("Imagem lida com sucesso. Aplicando Transformação de Haar...\n");

    haarTransform2D(image, size);

    printf("Transformação de Haar concluída. Salvando resultado...\n");

    savePGM(outputFilename, image, size, 255);

    printf("Arquivo salvo em '%s'.\n", outputFilename);

    return 0;
}