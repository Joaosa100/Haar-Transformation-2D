#include "mbed.h"
#include <stdio.h>
#include "stm32f0xx.h"

#define IMAGE_SIZE 90

// Initialize serial interface
Serial pc(SERIAL_TX, SERIAL_RX);

void haarTransform2d(const int input[][IMAGE_SIZE]) {
    printf("Transform Result:\n");
    uint8_t col, row; 
    uint16_t sum;
    for(row = 0; row < IMAGE_SIZE - 1; row = row + 2){
        for(col = 0; col < IMAGE_SIZE - 1 ; col = col + 2){
            sum = input[row][col] + input[row][col+1] + input[row+1][col] + input[row+1][col+1];        
            sum = sum / 2;
            sum = (sum < 0) ? 0 : ((sum > 255) ? 255 : sum);
            printf("%4d ", sum);
        }
        printf("\n");
    }
}

int main() {
    printf("Haar Transform - mbed OS 2\n");

    //90x90 image
    static const int input_image[][IMAGE_SIZE] = {
        //aqui iria a imagem declarada na flash, temos que remover
       };

    printf("Applying Haar Transform to %dx%d image...\n", IMAGE_SIZE, IMAGE_SIZE);
    printf("Output size will be %dx%d\n", IMAGE_SIZE / 2, IMAGE_SIZE / 2);

    
    haarTransform2d(input_image);
    printf("Execution completed.\n");
    
    while(true);
}