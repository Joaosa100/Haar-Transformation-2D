#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 90

void haarTransform2D(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    double temp[MAX_SIZE][MAX_SIZE];
    int half = size / 2;

    // Copy input to temp
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[i][j] = matrix[i][j];
        }
    }

    // Process 2x2 blocks directly (matches PyWavelets behavior)
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            double a = temp[2*i][2*j];
            double b = temp[2*i][2*j+1];
            double c = temp[2*i+1][2*j];
            double d = temp[2*i+1][2*j+1];

            // LL quadrant (top-left)
            matrix[i][j] = (a + b + c + d) / 2.0;
            
            // HL quadrant (top-right)
            matrix[i][j + half] = (a + b - c - d) / 2.0;
            
            // LH quadrant (bottom-left)
            matrix[i + half][j] = (a - b + c - d) / 2.0;
            
            // HH quadrant (bottom-right)
            matrix[i + half][j + half] = (a - b - c + d) / 2.0;
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
    fprintf(file, "%d %d\n", size, size);
    fprintf(file, "%d\n", maxVal);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Match Python's np.clip() behavior
            double val = matrix[i][j];
            val = val < 0 ? 0 : (val > maxVal ? maxVal : val);
            fprintf(file, "%d ", (int)val);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main() {
    const char *inputFilename = "../images/pgm/pessoa1.pgm";
    const char *outputFilename = "../images/pgm_output/pessoa1.pgm";
    int size;
    double image[MAX_SIZE][MAX_SIZE];

    readPGM(inputFilename, image, &size);
    printf("Imagem lida com sucesso. Aplicando Transformacao de Haar...\n");

    haarTransform2D(image, size);

    printf("Transformacao de Haar concluida. Salvando resultado...\n");
    savePGM(outputFilename, image, size, 255);
    printf("Arquivo salvo em '%s'.\n", outputFilename);

    return 0;
}