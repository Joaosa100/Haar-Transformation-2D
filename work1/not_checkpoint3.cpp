#include "mbed.h"
#include <stdio.h>
#include <stdlib.h>
#include "stm32f0xx.h"
#include <string.h>

// Define parameters
#define BLOCK_SIZE 10    
#define OUTPUT_BLOCK_SIZE 5  
#define IMAGE_SIZE 90
#define IMAGE_OUTPUT_SIZE 45
#define BUFFER_SIZE 32  // For reading lines

// Initialize serial interface
Serial pc(SERIAL_TX, SERIAL_RX);
DigitalOut myled(LED1);

// Function to read PGM header
int readPGMHeader(FILE *file) {
    char line[BUFFER_SIZE];
    int width, height, maxVal;

    // Read magic number (P2)
    if (!fgets(line, sizeof(line), file)) return 0;
    if (line[0] != 'P' || line[1] != '2') return 0;

    // Read dimensions
    if (!fgets(line, sizeof(line), file)) return 0;
    if (sscanf(line, "%d %d", &width, &height) != 2) return 0;
    if (width != IMAGE_SIZE || height != IMAGE_SIZE) return 0;

    // Read maximum value
    if (!fgets(line, sizeof(line), file)) return 0;
    if (sscanf(line, "%d", &maxVal) != 1) return 0;
    if (maxVal != 255) return 0;

    return 1;
}

// Function to read image data block by block
void processImageFromFile(FILE *file) {
    printf("Transform Result:\n");
    int input_block[BLOCK_SIZE][BLOCK_SIZE];
    
    // Skip header - we already read it
    for (int blockRow = 0; blockRow < IMAGE_SIZE; blockRow += BLOCK_SIZE) {
        // Read BLOCK_SIZE rows
        for (int i = 0; i < BLOCK_SIZE; i++) {
            for (int j = 0; j < BLOCK_SIZE; j++) {
                if (fscanf(file, "%d", &input_block[i][j]) != 1) {
                    printf("Error reading pixel data\n");
                    return;
                }
            }
        }
        
        // Process this block
        for (int subRow = 0; subRow < OUTPUT_BLOCK_SIZE; subRow++) {
            for (int j = 0; j < OUTPUT_BLOCK_SIZE; j++) {
                int sum = input_block[2*subRow][2*j] +
                         input_block[2*subRow][2*j+1] +
                         input_block[2*subRow+1][2*j] +
                         input_block[2*subRow+1][2*j+1];
                         
                int val = sum / 2;
                val = (val < 0) ? 0 : ((val > 255) ? 255 : val);
                printf("%4d ", val);
            }
            printf("\n");
        }
    }
}

int main() {
    printf("Haar Transform - mbed OS 2\n");

    // Open PGM file
    FILE *file = fopen("/home/studio/workspace/mbed2-try6/animal3.pgm", "r");  // Adjust path as needed
    if (!file) {
        printf("Error opening PGM file\n");
        while(true);
    }

    // Read and verify header
    if (!readPGMHeader(file)) {
        printf("Invalid PGM header\n");
        fclose(file);
        while(true);
    }

    printf("Processing PGM image %dx%d\n", IMAGE_SIZE, IMAGE_SIZE);
    
    // Process the image
    processImageFromFile(file);
    
    fclose(file);
    printf("Execution completed.\n");
    
    while(true);
}
