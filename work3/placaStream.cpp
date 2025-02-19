#include "mbed.h"
#include <stdio.h>
#include <stdlib.h>
//#include "stm32f0xx.h"

#define IMAGE_SIZE 90

// Inicializa a interface Serial
Serial pc(USBTX, USBRX);

int input_image[IMAGE_SIZE][IMAGE_SIZE];

void haarTransform2d(int input[][IMAGE_SIZE]) {
    printf("Transform Result:\n");
    uint8_t col, row; 
    uint16_t sum;
    for (row = 0; row < IMAGE_SIZE - 1; row += 2) {
        for (col = 0; col < IMAGE_SIZE - 1; col += 2) {
            sum = input[row][col] + input[row][col+1] + input[row+1][col] + input[row+1][col+1];
            sum = sum / 2;
            sum = (sum < 0) ? 0 : ((sum > 255) ? 255 : sum);
            printf("%d\n", sum);
        }
    }
}

void receberImagem() {
    char buffer[16];
    int row = 0, col = 0;

    while (true) {
        if (pc.readable()) {
            pc.scanf("%s", buffer);
            
            if (strcmp(buffer, "END") == 0) {
                pc.printf("Recebimento concluído.\n");
                return;
            }

            int value = atoi(buffer);
            input_image[row][col] = value;

            col++;
            if (col >= IMAGE_SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

int main() {
    pc.printf("Pronto para receber imagem via Serial...\n");

    receberImagem();

    pc.printf("Aplicando Haar Transform na imagem %dx%d...\n", IMAGE_SIZE, IMAGE_SIZE);
    haarTransform2d(input_image);

    pc.printf("Processamento concluído.\n");

    while (true);
}
