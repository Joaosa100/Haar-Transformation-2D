#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 90

void haarTransform2D(double input[MAX_SIZE][MAX_SIZE], double output[MAX_SIZE][MAX_SIZE], int input_size, int *output_size) {
    int half = input_size / 2;
    *output_size = half;  // Set the new size to half of the input

    // Calculate only LL coefficients
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            double a = input[2*i][2*j];
            double b = input[2*i][2*j+1];
            double c = input[2*i+1][2*j];
            double d = input[2*i+1][2*j+1];

            // Calculate LL coefficient
            output[i][j] = (a + b + c + d) / 2.0;
        }
    }
}

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

void savePGM(const char *filename, double matrix[MAX_SIZE][MAX_SIZE], int size, int maxVal) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao salvar o arquivo");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", size, size);  // Now using the reduced size
    fprintf(file, "%d\n", maxVal);

    for (int i = 0; i < size; i++) {  // Only loop through the reduced size
        for (int j = 0; j < size; j++) {
            double val = matrix[i][j];
            val = val < 0 ? 0 : (val > maxVal ? maxVal : val);
            fprintf(file, "%d ", (int)val);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main() {
    const char *inputFilename = "../images/pgm/animal3.pgm";
    const char *outputFilename = "../images/pgm_output/animal3.pgm";
    int input_size, output_size;
    double input_image[MAX_SIZE][MAX_SIZE];
    double output_image[MAX_SIZE][MAX_SIZE];

    readPGM(inputFilename, input_image, &input_size);
    printf("Imagem lida com sucesso. Aplicando Transformacao de Haar...\n");

    haarTransform2D(input_image, output_image, input_size, &output_size);

    printf("Transformacao de Haar concluida. Salvando resultado...\n");
    savePGM(outputFilename, output_image, output_size, 255);
    printf("Arquivo salvo em '%s'.\n", outputFilename);

    return 0;
}