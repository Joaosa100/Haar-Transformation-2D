#include "mbed.h"
#include <stdio.h>
#include <stdlib.h>
//#include "stm32f0xx.h"

#define IMAGE_SIZE 90

// Inicializa a interface Serial
Serial pc(USBTX, USBRX);

void haarTransform2D() {
    char buffer[16];
    uint8_t bloco[2][2];
    uint16_t sum;
    
    while (true) {
        // Recebe um bloco de 2x2
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (pc.readable()) {
                    pc.scanf("%s", buffer);

                    // Se receber "END", finaliza o processo
                    if (strcmp(buffer, "END") == 0) {
                        pc.printf("Processamento concluído.\n");
                        return;
                    }

                    bloco[i][j] = atoi(buffer);
                }
            }
        }

        // Calcula o Haar para esse bloco
        sum = bloco[0][0] + bloco[0][1] + bloco[1][0] + bloco[1][1];
        sum = sum / 2;
        sum = (sum < 0) ? 0 : ((sum > 255) ? 255 : sum);

        // Envia resultado imediatamente
        pc.printf("%d\n", sum);
    }
}

int main() {
    pc.printf("Pronto para receber imagem via Serial...\n");

    haarTransform2D();

    while (true);
}
