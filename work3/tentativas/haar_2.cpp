//#include "mbed.h"
//#include "stm32f0xx.h"
#include <stdio.h>
#include <time.h>

#define IMAGE_SIZE 90
//ENTRE 28us e 29us

//Serial pc(SERIAL_TX, SERIAL_RX);

void haarTransform2d(const int input[][IMAGE_SIZE]) {
    for(int row = 0; row < IMAGE_SIZE - 1; row += 2) {
        const int *row_ptr = &input[row][0];
        const int *next_row_ptr = &input[row+1][0];
        for(int col = 0; col < IMAGE_SIZE - 1; col += 2) {
            int sum = (row_ptr[col] + row_ptr[col+1] + next_row_ptr[col] + next_row_ptr[col+1]) >> 1;
            sum = (sum > 255) ? 255 : sum;
            printf("%4d ", sum);
        }
        printf("\n");
    }
}

int main() {
    //printf("Haar Transform - mbed OS 2\n");
    static const int input_image[][IMAGE_SIZE] = {
        {89, 89, 89, 90, 92, 92, 92, 91, 93, 94, 95, 97, 98, 97, 97, 98, 96, 96, 97, 98, 99, 100, 100, 100, 98, 97, 96, 94, 92, 90, 88, 87, 87, 86, 85, 85, 85, 85, 84, 83, 83, 83, 84, 84, 85, 86, 86, 87, 86, 85, 84, 84, 85, 85, 85, 84, 84, 83, 83, 82, 82, 81, 81, 80, 82, 82, 81, 81, 81, 81, 81, 81, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 84, 83, 84, 84, 85, 85, 87, 88},
        {85, 86, 88, 89, 90, 89, 89, 88, 89, 89, 91, 93, 93, 92, 92, 94, 94, 95, 96, 97, 98, 99, 99, 99, 96, 95, 94, 92, 91, 89, 88, 88, 88, 87, 87, 87, 87, 86, 85, 84, 83, 84, 84, 84, 85, 85, 86, 86, 87, 86, 85, 85, 86, 86, 86, 86, 85, 84, 84, 83, 83, 82, 82, 81, 82, 82, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 82, 82, 82, 82, 82, 83, 84, 85, 85},
{83, 85, 87, 88, 88, 87, 86, 85, 86, 86, 88, 89, 90, 89, 89, 91, 90, 91, 93, 94, 95, 96, 96, 95, 93, 93, 92, 91, 91, 90, 89, 89, 88, 88, 87, 87, 87, 87, 86, 85, 85, 85, 85, 86, 86, 86, 86, 86, 87, 86, 85, 85, 86, 86, 86, 86, 84, 84, 84, 83, 83, 82, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 82, 82, 82, 82, 82, 82, 82, 82, 81, 81, 81, 80, 80, 81, 81, 82, 83, 83},
{85, 86, 86, 87, 88, 87, 85, 83, 85, 85, 86, 87, 87, 87, 88, 89, 89, 90, 91, 92, 93, 94, 95, 95, 93, 93, 92, 92, 92, 91, 91, 91, 91, 90, 90, 90, 90, 90, 89, 88, 88, 88, 88, 88, 88, 88, 88, 88, 87, 87, 86, 86, 87, 87, 87, 87, 85, 85, 85, 84, 84, 83, 83, 83, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 82, 82, 82, 82, 82, 81, 81, 80, 80, 80, 80, 80, 81, 82, 82},
{88, 87, 86, 86, 87, 86, 84, 81, 82, 82, 83, 84, 84, 83, 84, 86, 90, 90, 91, 91, 93, 94, 96, 97, 94, 94, 94, 94, 94, 94, 93, 93, 95, 94, 94, 95, 95, 95, 94, 93, 91, 91, 91, 91, 91, 91, 91, 91, 91, 90, 89, 89, 89, 90, 89, 89, 89, 88, 88, 87, 87, 86, 86, 86, 84, 84, 84, 84, 83, 84, 84, 84, 84, 84, 83, 83, 82, 82, 81, 81, 80, 80, 79, 79, 79, 79, 79, 79, 81, 81},
{88, 88, 87, 88, 88, 87, 84, 82, 83, 82, 83, 84, 84, 83, 85, 87, 91, 91, 91, 92, 93, 95, 97, 98, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 99, 100, 100, 99, 97, 97, 96, 96, 96, 96, 96, 96, 96, 94, 94, 93, 92, 92, 92, 92, 92, 92, 91, 91, 90, 89, 89, 88, 88, 87, 87, 86, 86, 85, 85, 85, 85, 84, 84, 84, 83, 82, 82, 81, 81, 80, 79, 78, 78, 77, 77, 78, 78, 79, 80},
{88, 91, 94, 95, 93, 91, 88, 87, 87, 87, 87, 88, 88, 87, 89, 91, 91, 92, 94, 95, 97, 98, 99, 99, 99, 100, 100, 101, 101, 102, 102, 102, 102, 102, 103, 104, 105, 105, 104, 103, 103, 103, 103, 103, 103, 103, 103, 103, 101, 100, 99, 98, 98, 98, 97, 97, 96, 96, 95, 95, 94, 93, 92, 92, 91, 91, 90, 89, 88, 87, 87, 87, 86, 86, 85, 84, 83, 82, 82, 81, 80, 80, 79, 78, 77, 77, 78, 78, 78, 78},
{89, 94, 100, 102, 98, 94, 93, 93, 91, 90, 90, 91, 91, 90, 92, 94, 94, 96, 98, 101, 102, 103, 102, 102, 102, 102, 103, 104, 105, 106, 107, 107, 107, 107, 108, 110, 111, 111, 110, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 108, 106, 106, 105, 105, 104, 104, 102, 102, 101, 100, 99, 98, 98, 97, 94, 93, 92, 91, 89, 88, 88, 88, 88, 87, 86, 86, 85, 84, 83, 83, 81, 81, 80, 79, 78, 78, 78, 79, 78, 78},
{95, 100, 104, 106, 103, 101, 99, 100, 98, 96, 94, 94, 96, 97, 98, 98, 99, 100, 105, 101, 107, 105, 107, 103, 109, 112, 104, 110, 111, 114, 110, 113, 114, 117, 111, 118, 112, 118, 113, 119, 115, 122, 113, 119, 117, 116, 118, 118, 117, 110, 113, 113, 114, 112, 115, 109, 107, 108, 108, 105, 107, 104, 99, 104, 101, 97, 96, 97, 94, 92, 93, 92, 92, 91, 89, 88, 88, 87, 86, 85, 83, 83, 83, 82, 82, 81, 81, 81, 80, 80},
{99, 102, 106, 107, 106, 104, 103, 102, 102, 100, 99, 99, 100, 102, 102, 102, 102, 102, 107, 104, 109, 108, 112, 111, 108, 107, 119, 115, 115, 118, 119, 123, 120, 119, 125, 124, 126, 127, 129, 123, 125, 124, 129, 128, 128, 128, 125, 125, 123, 130, 126, 121, 126, 119, 114, 120, 120, 118, 113, 116, 109, 115, 107, 106, 107, 103, 103, 103, 100, 98, 98, 95, 96, 95, 93, 92, 91, 90, 89, 88, 86, 86, 86, 86, 85, 85, 84, 84, 85, 85},
{104, 106, 108, 109, 109, 108, 107, 106, 106, 105, 104, 104, 105, 107, 107, 107, 108, 108, 110, 109, 111, 109, 112, 114, 119, 120, 116, 125, 119, 126, 129, 124, 133, 129, 135, 129, 131, 132, 137, 127, 136, 132, 140, 136, 138, 135, 140, 137, 133, 131, 130, 131, 129, 130, 130, 127, 125, 121, 122, 119, 115, 115, 120, 115, 112, 110, 109, 107, 105, 105, 105, 102, 102, 100, 98, 97, 96, 95, 93, 92, 91, 91, 90, 90, 90, 89, 89, 89, 88, 88},
{108, 109, 110, 111, 112, 111, 110, 110, 108, 107, 107, 107, 108, 109, 109, 109, 111, 110, 112, 114, 117, 118, 120, 122, 120, 124, 123, 131, 127, 132, 134, 137, 138, 141, 139, 140, 138, 144, 143, 143, 144, 142, 144, 145, 141, 136, 146, 138, 146, 138, 139, 141, 134, 137, 138, 131, 133, 132, 131, 131, 129, 123, 122, 118, 119, 117, 116, 112, 108, 109, 110, 107, 107, 106, 104, 102, 101, 99, 98, 97, 95, 95, 95, 94, 94, 93, 93, 93, 90, 90},
{112, 112, 113, 113, 114, 114, 114, 113, 110, 110, 109, 110, 110, 111, 111, 111, 114, 113, 112, 116, 118, 121, 122, 124, 130, 127, 138, 130, 141, 141, 134, 143, 141, 150, 144, 148, 148, 146, 139, 149, 144, 141, 149, 153, 145, 152, 151, 150, 148, 152, 148, 146, 149, 142, 136, 143, 133, 139, 125, 136, 135, 137, 129, 131, 126, 124, 123, 120, 115, 113, 113, 111, 113, 111, 109, 107, 106, 104, 103, 101, 100, 100, 99, 99, 98, 98, 97, 97, 95, 95},
{117, 117, 117, 118, 118, 118, 117, 117, 114, 114, 113, 113, 114, 114, 115, 115, 118, 119, 116, 120, 123, 134, 139, 143, 149, 159, 142, 144, 136, 139, 143, 147, 151, 155, 149, 148, 154, 148, 145, 158, 155, 144, 155, 149, 140, 158, 148, 161, 155, 150, 152, 151, 154, 140, 137, 138, 131, 142, 143, 143, 151, 144, 149, 145, 132, 128, 127, 127, 123, 121, 120, 118, 119, 117, 115, 113, 112, 110, 109, 107, 106, 106, 105, 104, 103, 103, 102, 102, 101, 101},
{122, 122, 123, 123, 123, 122, 122, 122, 119, 119, 118, 117, 117, 118, 119, 120, 119, 124, 123, 128, 137, 161, 177, 188, 193, 213, 213, 214, 186, 179, 169, 146, 155, 154, 152, 160, 158, 164, 164, 169, 177, 170, 167, 157, 150, 155, 156, 164, 168, 154, 166, 161, 152, 133, 144, 145, 166, 187, 207, 216, 215, 205, 199, 167, 152, 139, 132, 132, 131, 129, 128, 126, 125, 124, 122, 120, 118, 117, 115, 114, 113, 112, 112, 111, 109, 108, 108, 107, 106, 106},
{125, 126, 128, 128, 127, 126, 125, 125, 122, 122, 120, 119, 119, 120, 121, 122, 122, 129, 126, 130, 137, 168, 191, 207, 182, 138, 174, 135, 166, 203, 197, 170, 154, 155, 153, 175, 153, 170, 157, 149, 144, 154, 140, 144, 147, 133, 153, 146, 159, 166, 183, 168, 162, 135, 159, 190, 203, 191, 143, 149, 127, 192, 214, 201, 179, 158, 141, 137, 135, 133, 131, 130, 130, 128, 126, 124, 123, 121, 120, 119, 117, 117, 116, 115, 114, 113, 112, 111, 111, 111},
{129, 129, 130, 132, 131, 129, 129, 130, 128, 127, 126, 125, 124, 124, 125, 127, 127, 129, 134, 136, 142, 159, 195, 156, 90, 91, 111, 127, 122, 100, 144, 164, 164, 149, 146, 150, 140, 131, 111, 120, 115, 98, 109, 130, 126, 116, 120, 114, 112, 139, 149, 140, 145, 149, 188, 163, 130, 119, 120, 81, 77, 106, 148, 203, 189, 167, 152, 144, 139, 138, 133, 133, 134, 133, 131, 129, 128, 127, 126, 125, 122, 121, 119, 118, 118, 118, 117, 117, 114, 114},
{134, 134, 135, 136, 135, 133, 133, 133, 132, 131, 130, 128, 128, 128, 130, 131, 133, 135, 139, 140, 147, 160, 167, 97, 62, 66, 101, 98, 111, 128, 128, 139, 169, 139, 111, 111, 119, 119, 101, 102, 100, 119, 126, 118, 105, 94, 96, 88, 89, 115, 132, 110, 128, 163, 127, 121, 113, 100, 94, 63, 59, 65, 95, 181, 182, 163, 153, 147, 143, 142, 139, 139, 137, 136, 134, 132, 131, 130, 129, 128, 126, 125, 124, 123, 122, 122, 121, 120, 118, 118},
{139, 139, 139, 140, 139, 137, 137, 138, 136, 136, 134, 133, 132, 133, 135, 136, 136, 139, 145, 148, 154, 167, 164, 86, 45, 44, 70, 58, 87, 84, 95, 104, 129, 143, 103, 121, 94, 118, 89, 100, 91, 85, 123, 96, 138, 90, 72, 111, 106, 118, 95, 64, 120, 113, 133, 118, 95, 72, 44, 48, 60, 53, 75, 153, 172, 159, 154, 150, 147, 146, 143, 143, 142, 140, 138, 136, 135, 134, 132, 131, 131, 130, 129, 128, 127, 126, 124, 123, 123, 123},
{142, 141, 142, 142, 141, 139, 139, 140, 139, 139, 137, 135, 135, 136, 138, 140, 145, 142, 147, 151, 152, 160, 157, 90, 68, 40, 37, 44, 66, 82, 89, 111, 92, 114, 106, 74, 85, 77, 87, 73, 96, 87, 79, 85, 98, 78, 75, 90, 96, 98, 68, 72, 104, 95, 116, 97, 82, 41, 31, 30, 31, 46, 61, 150, 166, 158, 157, 154, 149, 148, 145, 146, 145, 143, 141, 140, 138, 137, 136, 135, 133, 133, 132, 131, 131, 129, 128, 126, 127, 127},
{143, 142, 142, 143, 142, 140, 140, 142, 142, 141, 140, 139, 138, 140, 142, 144, 150, 146, 147, 153, 155, 160, 146, 81, 52, 42, 30, 27, 49, 53, 102, 96, 85, 104, 92, 62, 72, 69, 84, 67, 85, 94, 66, 90, 98, 80, 78, 81, 88, 85, 61, 84, 81, 104, 94, 83, 70, 40, 21, 29, 33, 48, 71, 150, 163, 159, 161, 157, 152, 151, 148, 148, 147, 145, 144, 142, 141, 139, 138, 137, 135, 134, 134, 133, 133, 132, 130, 129, 129, 129},
{144, 144, 143, 144, 143, 142, 143, 145, 145, 145, 144, 143, 143, 144, 146, 148, 148, 152, 154, 157, 160, 166, 148, 89, 64, 43, 36, 34, 41, 82, 78, 66, 71, 75, 75, 61, 68, 59, 82, 73, 96, 88, 70, 86, 67, 77, 74, 63, 59, 62, 47, 64, 69, 66, 68, 66, 52, 34, 33, 25, 28, 46, 60, 162, 157, 156, 161, 158, 152, 152, 150, 149, 148, 147, 145, 144, 143, 141, 140, 139, 137, 137, 136, 136, 135, 135, 133, 132, 131, 131},
{145, 145, 145, 145, 145, 144, 146, 148, 147, 147, 147, 147, 147, 148, 150, 151, 151, 158, 158, 159, 159, 162, 148, 111, 75, 56, 49, 52, 60, 74, 75, 75, 76, 59, 59, 61, 59, 54, 79, 77, 87, 75, 67, 74, 98, 58, 65, 73, 57, 52, 50, 53, 54, 51, 52, 68, 69, 56, 28, 30, 44, 60, 90, 157, 154, 155, 162, 160, 155, 155, 151, 150, 148, 147, 146, 145, 144, 143, 142, 140, 140, 139, 138, 137, 137, 136, 135, 134, 133, 133},
{146, 145, 145, 146, 146, 146, 147, 149, 148, 149, 149, 149, 149, 150, 151, 153, 157, 158, 155, 162, 166, 164, 153, 133, 93, 70, 46, 59, 61, 76, 70, 92, 82, 68, 75, 81, 54, 48, 69, 72, 74, 79, 83, 58, 66, 82, 58, 86, 59, 60, 68, 62, 69, 58, 65, 46, 50, 48, 41, 51, 59, 80, 115, 151, 155, 158, 166, 164, 159, 159, 154, 151, 149, 148, 147, 146, 145, 144, 143, 142, 142, 141, 139, 138, 137, 136, 135, 135, 135, 135},
{146, 145, 145, 147, 147, 146, 148, 151, 150, 149, 150, 152, 152, 150, 151, 155, 155, 161, 160, 162, 167, 165, 153, 134, 126, 83, 56, 52, 68, 72, 74, 70, 67, 70, 79, 82, 65, 79, 41, 102, 81, 76, 113, 59, 56, 62, 60, 88, 42, 73, 67, 47, 67, 54, 68, 68, 62, 68, 48, 36, 55, 78, 122, 128, 141, 157, 172, 165, 160, 160, 153, 156, 151, 150, 149, 147, 145, 145, 145, 145, 144, 142, 140, 139, 139, 138, 137, 136, 137, 137},
{146, 145, 146, 147, 147, 147, 148, 151, 151, 150, 151, 153, 153, 151, 153, 157, 160, 161, 160, 164, 166, 165, 159, 143, 120, 98, 66, 71, 74, 87, 81, 75, 73, 80, 71, 76, 76, 73, 74, 54, 79, 62, 80, 70, 89, 84, 51, 74, 59, 59, 62, 58, 47, 62, 83, 79, 79, 72, 41, 59, 75, 89, 102, 124, 142, 159, 170, 167, 167, 167, 159, 158, 153, 152, 150, 148, 147, 146, 146, 146, 146, 144, 143, 141, 141, 140, 138, 137, 138, 138},
{148, 147, 148, 149, 149, 149, 150, 152, 152, 152, 153, 155, 155, 153, 155, 159, 159, 163, 162, 161, 164, 167, 145, 101, 94, 100, 79, 64, 95, 89, 68, 86, 80, 114, 100, 59, 97, 105, 103, 75, 66, 49, 66, 67, 85, 86, 83, 81, 54, 59, 90, 89, 93, 68, 80, 73, 72, 66, 70, 54, 87, 98, 111, 120, 120, 151, 165, 167, 167, 163, 159, 157, 156, 155, 153, 150, 149, 148, 147, 147, 147, 146, 145, 144, 143, 142, 141, 140, 141, 140},
{150, 150, 151, 152, 152, 152, 153, 154, 153, 153, 154, 156, 155, 155, 157, 160, 158, 161, 162, 164, 170, 178, 152, 97, 67, 70, 110, 99, 109, 97, 96, 116, 122, 102, 93, 101, 83, 77, 97, 71, 71, 32, 30, 58, 94, 63, 93, 70, 60, 86, 78, 113, 68, 95, 76, 66, 83, 80, 62, 93, 56, 70, 83, 84, 123, 157, 169, 171, 171, 164, 165, 165, 159, 158, 155, 152, 151, 149, 148, 148, 147, 147, 147, 146, 145, 144, 143, 142, 143, 142},
{152, 153, 154, 155, 155, 155, 155, 155, 154, 154, 155, 156, 155, 155, 157, 160, 164, 160, 162, 170, 171, 175, 171, 147, 117, 114, 136, 133, 128, 121, 115, 119, 99, 105, 106, 83, 89, 115, 139, 74, 59, 32, 35, 83, 92, 122, 87, 125, 100, 112, 77, 81, 68, 112, 86, 93, 93, 80, 87, 81, 79, 71, 58, 102, 142, 163, 164, 164, 167, 165, 166, 163, 163, 160, 157, 155, 153, 151, 150, 149, 147, 147, 147, 147, 147, 146, 146, 146, 145, 144},
{154, 156, 157, 157, 157, 158, 157, 157, 155, 156, 157, 156, 156, 156, 158, 161, 164, 165, 168, 172, 169, 171, 175, 164, 127, 123, 129, 135, 142, 140, 136, 108, 124, 119, 97, 136, 98, 153, 168, 151, 63, 29, 28, 64, 143, 165, 133, 100, 154, 146, 112, 121, 126, 132, 78, 134, 134, 113, 136, 116, 94, 100, 112, 133, 154, 164, 168, 169, 170, 171, 172, 169, 166, 163, 160, 157, 156, 154, 152, 151, 148, 149, 148, 148, 147, 147, 148, 148, 147, 147},
{156, 159, 161, 161, 161, 161, 161, 159, 160, 161, 161, 160, 160, 160, 162, 164, 161, 168, 171, 174, 176, 180, 176, 160, 145, 155, 145, 130, 145, 153, 149, 160, 181, 180, 180, 135, 111, 63, 155, 122, 101, 33, 34, 94, 178, 165, 107, 70, 113, 144, 140, 127, 118, 155, 133, 135, 146, 123, 147, 138, 108, 123, 123, 150, 149, 150, 159, 162, 162, 167, 169, 169, 169, 167, 163, 160, 159, 157, 155, 154, 151, 151, 150, 149, 148, 148, 149, 150, 150, 150},
{159, 162, 164, 164, 164, 164, 163, 162, 164, 165, 166, 164, 163, 164, 166, 168, 171, 171, 168, 174, 178, 174, 171, 164, 162, 146, 159, 170, 140, 175, 143, 150, 141, 168, 174, 177, 104, 74, 130, 183, 104, 50, 41, 127, 171, 144, 70, 115, 139, 162, 140, 149, 141, 136, 139, 152, 158, 159, 151, 173, 146, 148, 142, 141, 163, 148, 151, 154, 158, 172, 175, 174, 172, 169, 165, 162, 161, 160, 157, 156, 154, 153, 152, 150, 149, 149, 150, 151, 152, 152},
{159, 163, 166, 164, 162, 161, 162, 163, 166, 167, 168, 168, 169, 171, 171, 170, 171, 173, 173, 178, 172, 168, 171, 162, 170, 168, 159, 159, 152, 165, 143, 163, 168, 142, 137, 128, 139, 77, 173, 166, 69, 53, 61, 152, 192, 139, 75, 123, 137, 149, 160, 183, 191, 176, 168, 170, 168, 178, 146, 158, 169, 170, 149, 151, 148, 143, 153, 151, 158, 159, 178, 173, 171, 170, 167, 165, 164, 162, 159, 157, 156, 156, 155, 153, 153, 153, 154, 155, 154, 154},
{159, 163, 165, 164, 161, 161, 162, 163, 165, 167, 168, 169, 170, 171, 171, 170, 170, 168, 167, 176, 177, 174, 174, 163, 162, 167, 157, 151, 130, 148, 119, 106, 87, 90, 66, 50, 47, 81, 157, 162, 81, 43, 64, 143, 180, 139, 60, 59, 80, 82, 103, 96, 100, 142, 174, 136, 171, 112, 123, 165, 151, 162, 162, 166, 175, 158, 172, 165, 163, 169, 166, 172, 172, 170, 167, 166, 165, 164, 162, 160, 158, 157, 155, 153, 152, 153, 154, 155, 154, 154},
{159, 162, 163, 162, 159, 159, 160, 160, 163, 165, 168, 169, 170, 172, 172, 171, 177, 173, 171, 176, 173, 167, 169, 166, 150, 134, 145, 116, 110, 84, 87, 60, 36, 47, 46, 36, 36, 55, 94, 87, 65, 43, 59, 94, 112, 83, 39, 50, 35, 37, 39, 73, 92, 114, 109, 154, 141, 118, 141, 150, 144, 153, 161, 178, 164, 147, 144, 157, 163, 169, 172, 174, 173, 171, 169, 167, 167, 166, 164, 163, 161, 158, 155, 153, 152, 153, 154, 155, 155, 155},
{158, 160, 161, 158, 156, 156, 156, 157, 159, 163, 166, 169, 171, 173, 173, 172, 169, 168, 170, 177, 174, 167, 169, 174, 155, 151, 141, 150, 94, 63, 38, 30, 13, 60, 68, 109, 30, 37, 39, 48, 46, 55, 49, 65, 56, 31, 44, 61, 105, 108, 34, 22, 28, 39, 60, 72, 101, 148, 158, 125, 130, 170, 170, 183, 165, 154, 146, 153, 156, 156, 172, 177, 175, 173, 170, 167, 166, 165, 164, 163, 161, 159, 156, 153, 152, 153, 154, 155, 154, 154},
{159, 160, 159, 156, 154, 154, 154, 154, 156, 161, 165, 168, 171, 172, 173, 172, 176, 172, 173, 177, 175, 164, 155, 157, 161, 146, 117, 94, 60, 32, 31, 30, 32, 71, 26, 19, 20, 44, 40, 73, 56, 37, 61, 61, 42, 60, 44, 40, 27, 22, 15, 54, 24, 24, 20, 51, 114, 94, 141, 124, 149, 145, 160, 179, 176, 153, 156, 143, 154, 163, 165, 173, 175, 172, 169, 167, 166, 164, 163, 161, 160, 158, 155, 154, 154, 154, 154, 154, 154, 154},
{159, 159, 157, 155, 154, 154, 154, 154, 155, 160, 166, 169, 170, 171, 171, 170, 170, 168, 169, 167, 163, 156, 152, 162, 144, 120, 81, 52, 47, 36, 43, 42, 43, 49, 29, 27, 32, 60, 51, 84, 66, 67, 60, 66, 57, 73, 72, 45, 10, 14, 30, 33, 31, 24, 29, 26, 39, 81, 98, 143, 149, 160, 175, 174, 162, 149, 150, 139, 156, 162, 170, 171, 173, 171, 168, 166, 165, 164, 162, 160, 158, 156, 154, 153, 154, 154, 154, 154, 154, 154},
{157, 157, 155, 153, 153, 155, 155, 155, 157, 162, 167, 170, 170, 170, 169, 168, 173, 172, 171, 159, 147, 140, 139, 157, 138, 107, 72, 42, 43, 35, 43, 40, 41, 44, 46, 62, 64, 60, 45, 80, 64, 72, 62, 58, 58, 60, 65, 60, 47, 24, 39, 42, 21, 34, 26, 49, 21, 54, 75, 86, 99, 144, 139, 183, 159, 168, 166, 157, 153, 146, 166, 173, 173, 171, 168, 166, 165, 163, 160, 158, 157, 155, 152, 152, 153, 154, 155, 155, 154, 154},
{155, 155, 153, 152, 152, 155, 156, 155, 158, 164, 169, 170, 170, 169, 167, 166, 166, 166, 166, 155, 148, 141, 135, 148, 115, 92, 72, 36, 35, 35, 52, 45, 35, 49, 47, 57, 77, 71, 74, 87, 79, 66, 79, 87, 85, 68, 61, 50, 45, 47, 31, 45, 43, 53, 26, 28, 27, 38, 62, 97, 112, 136, 149, 158, 162, 157, 159, 150, 149, 156, 154, 169, 175, 172, 169, 167, 165, 162, 158, 156, 156, 154, 151, 150, 152, 154, 156, 156, 155, 154},
{154, 156, 155, 153, 153, 152, 152, 155, 156, 162, 168, 170, 167, 164, 163, 165, 165, 170, 162, 159, 156, 144, 135, 135, 137, 104, 61, 35, 36, 46, 35, 56, 54, 33, 52, 64, 108, 126, 108, 97, 75, 90, 102, 102, 120, 107, 80, 44, 37, 40, 32, 42, 31, 29, 31, 38, 35, 44, 61, 97, 108, 131, 151, 145, 145, 140, 164, 150, 136, 140, 152, 165, 173, 171, 170, 168, 163, 159, 156, 155, 153, 151, 149, 149, 151, 154, 157, 158, 156, 155},
{156, 157, 155, 152, 152, 152, 152, 155, 157, 162, 167, 168, 165, 162, 161, 162, 166, 166, 173, 156, 151, 153, 137, 125, 113, 97, 64, 43, 43, 49, 42, 35, 51, 31, 71, 133, 156, 168, 107, 89, 85, 95, 88, 114, 161, 155, 121, 90, 40, 33, 26, 38, 32, 112, 30, 40, 25, 38, 69, 82, 126, 133, 136, 133, 130, 134, 146, 149, 135, 152, 159, 175, 174, 172, 168, 164, 161, 158, 156, 155, 152, 151, 150, 150, 150, 153, 155, 157, 157, 156},
{159, 159, 155, 153, 155, 155, 155, 157, 160, 163, 166, 167, 165, 163, 161, 161, 167, 167, 166, 160, 152, 140, 146, 127, 119, 103, 75, 61, 48, 37, 44, 29, 23, 52, 122, 183, 183, 195, 116, 91, 101, 95, 104, 118, 190, 184, 191, 155, 84, 52, 22, 43, 76, 28, 39, 30, 24, 38, 53, 77, 125, 141, 141, 111, 126, 138, 149, 140, 130, 131, 148, 164, 177, 176, 171, 164, 160, 160, 158, 156, 150, 150, 151, 150, 150, 151, 154, 157, 156, 155},
{162, 160, 157, 157, 161, 161, 159, 160, 163, 164, 166, 167, 167, 165, 163, 162, 169, 169, 160, 163, 161, 134, 147, 127, 108, 109, 100, 73, 48, 43, 54, 27, 28, 98, 185, 187, 198, 206, 152, 91, 118, 115, 125, 135, 189, 193, 201, 188, 174, 94, 26, 28, 51, 32, 37, 33, 34, 35, 78, 103, 130, 147, 128, 134, 132, 137, 137, 131, 141, 140, 158, 163, 177, 178, 175, 167, 161, 160, 158, 155, 149, 150, 150, 150, 150, 151, 153, 154, 152, 152},
{162, 161, 159, 162, 167, 166, 163, 163, 166, 165, 165, 166, 167, 165, 162, 159, 163, 162, 162, 151, 159, 143, 132, 117, 107, 103, 105, 76, 47, 35, 33, 18, 26, 159, 188, 185, 183, 186, 113, 109, 124, 124, 126, 128, 194, 206, 185, 188, 194, 139, 87, 68, 75, 72, 40, 36, 44, 63, 88, 92, 125, 130, 124, 134, 121, 137, 128, 134, 129, 135, 150, 166, 170, 175, 175, 168, 161, 158, 156, 154, 153, 151, 150, 150, 151, 151, 150, 148, 148, 148},
{161, 160, 161, 166, 171, 169, 165, 165, 167, 165, 164, 165, 166, 164, 159, 154, 165, 171, 169, 162, 166, 147, 142, 139, 97, 86, 100, 96, 83, 63, 43, 52, 82, 147, 175, 191, 197, 165, 121, 115, 113, 124, 139, 108, 143, 185, 192, 196, 189, 152, 76, 27, 32, 44, 24, 35, 48, 97, 99, 112, 104, 94, 133, 127, 127, 130, 122, 131, 142, 149, 161, 169, 165, 170, 171, 166, 160, 157, 156, 156, 156, 154, 151, 151, 152, 150, 146, 143, 145, 145},
{161, 161, 162, 168, 174, 171, 166, 167, 167, 165, 163, 165, 168, 166, 160, 154, 157, 165, 161, 165, 161, 142, 146, 140, 103, 105, 97, 71, 68, 75, 62, 78, 96, 145, 170, 174, 166, 101, 49, 52, 52, 53, 52, 48, 50, 166, 192, 178, 181, 149, 105, 80, 66, 44, 40, 64, 66, 69, 86, 114, 97, 97, 111, 99, 128, 128, 134, 132, 140, 132, 149, 160, 166, 166, 165, 161, 157, 155, 155, 156, 155, 154, 153, 152, 152, 150, 146, 143, 143, 144},
{163, 163, 164, 170, 174, 171, 167, 168, 167, 165, 164, 167, 171, 171, 164, 158, 160, 160, 172, 166, 162, 168, 145, 121, 94, 115, 107, 84, 84, 86, 65, 81, 67, 140, 173, 151, 160, 90, 19, 13, 15, 13, 15, 21, 16, 119, 160, 157, 162, 163, 172, 141, 75, 116, 71, 74, 70, 74, 84, 74, 91, 105, 124, 89, 119, 121, 124, 139, 140, 146, 153, 169, 168, 163, 158, 155, 152, 150, 151, 152, 151, 152, 153, 153, 152, 151, 148, 146, 142, 143},
{167, 172, 166, 163, 169, 169, 166, 171, 175, 170, 169, 172, 172, 170, 167, 162, 161, 162, 168, 165, 156, 160, 158, 140, 118, 96, 90, 95, 89, 77, 66, 93, 73, 84, 112, 136, 125, 94, 26, 21, 11, 14, 13, 16, 29, 123, 130, 149, 164, 149, 108, 92, 79, 79, 67, 69, 73, 62, 68, 62, 94, 92, 118, 100, 107, 115, 117, 137, 158, 147, 150, 163, 159, 157, 154, 153, 151, 151, 151, 151, 151, 153, 155, 155, 153, 151, 148, 146, 146, 146},
{174, 171, 165, 165, 170, 168, 165, 168, 175, 174, 175, 173, 169, 169, 168, 164, 167, 162, 164, 167, 169, 172, 160, 136, 114, 105, 84, 100, 83, 60, 77, 89, 69, 53, 67, 77, 90, 90, 69, 39, 36, 18, 21, 32, 54, 96, 105, 116, 110, 84, 94, 65, 80, 67, 66, 61, 75, 63, 66, 76, 91, 101, 110, 105, 123, 114, 104, 132, 162, 146, 167, 165, 160, 158, 156, 154, 152, 151, 150, 151, 150, 151, 153, 154, 154, 154, 152, 151, 152, 152},
{176, 167, 162, 165, 168, 165, 166, 171, 173, 175, 175, 169, 167, 172, 173, 167, 162, 165, 170, 171, 168, 164, 154, 141, 113, 102, 100, 84, 69, 84, 69, 50, 39, 44, 62, 24, 34, 37, 28, 44, 32, 33, 54, 57, 54, 49, 55, 53, 38, 50, 34, 40, 46, 34, 52, 57, 46, 71, 70, 83, 104, 109, 112, 107, 123, 121, 134, 156, 157, 160, 162, 169, 166, 166, 165, 162, 158, 154, 152, 151, 150, 150, 151, 153, 156, 157, 156, 155, 155, 155},
{168, 163, 161, 162, 158, 159, 167, 174, 171, 172, 169, 165, 169, 181, 182, 171, 168, 168, 167, 166, 165, 161, 150, 140, 122, 108, 104, 89, 83, 99, 76, 55, 53, 82, 43, 27, 51, 23, 28, 27, 29, 23, 26, 34, 39, 52, 47, 29, 25, 38, 31, 38, 39, 43, 114, 71, 78, 67, 66, 99, 109, 103, 120, 111, 102, 90, 127, 141, 172, 175, 173, 176, 167, 169, 170, 168, 163, 159, 155, 152, 150, 149, 151, 154, 158, 158, 157, 156, 155, 155},
{160, 165, 169, 163, 153, 155, 165, 173, 169, 169, 167, 165, 172, 186, 189, 179, 174, 172, 170, 169, 168, 163, 153, 144, 127, 117, 116, 108, 99, 91, 55, 47, 70, 57, 53, 26, 33, 29, 20, 23, 25, 23, 32, 42, 31, 35, 28, 31, 56, 27, 46, 33, 50, 45, 82, 51, 52, 71, 74, 123, 96, 118, 107, 143, 143, 132, 127, 157, 176, 177, 168, 172, 161, 165, 169, 169, 167, 163, 158, 154, 149, 149, 151, 157, 160, 160, 158, 157, 157, 157},
{162, 176, 181, 170, 159, 159, 165, 168, 165, 166, 167, 166, 170, 182, 187, 182, 172, 172, 176, 177, 174, 171, 163, 152, 108, 116, 134, 135, 113, 87, 61, 76, 81, 61, 55, 28, 30, 28, 35, 19, 26, 24, 33, 36, 34, 32, 33, 41, 47, 28, 39, 35, 61, 63, 43, 69, 81, 86, 92, 93, 118, 96, 160, 128, 147, 145, 158, 156, 178, 170, 169, 169, 165, 169, 173, 173, 171, 168, 163, 157, 150, 150, 153, 159, 163, 162, 160, 160, 159, 159},
{167, 180, 180, 170, 165, 165, 163, 163, 165, 163, 163, 165, 170, 177, 181, 179, 175, 170, 174, 181, 185, 187, 175, 153, 144, 125, 99, 125, 116, 81, 79, 81, 73, 79, 53, 39, 41, 30, 41, 30, 15, 31, 39, 44, 47, 36, 33, 27, 34, 34, 55, 34, 47, 69, 58, 74, 93, 103, 93, 116, 120, 141, 137, 161, 140, 140, 163, 170, 173, 181, 167, 168, 171, 173, 175, 174, 173, 172, 167, 161, 155, 154, 157, 162, 164, 162, 161, 163, 162, 162},
{168, 176, 170, 161, 165, 166, 161, 159, 169, 161, 158, 164, 172, 178, 179, 175, 169, 171, 185, 191, 185, 185, 181, 164, 151, 134, 133, 120, 91, 89, 92, 107, 73, 61, 41, 31, 31, 43, 15, 24, 22, 40, 29, 45, 47, 35, 37, 36, 35, 30, 48, 27, 39, 57, 33, 70, 106, 113, 103, 93, 141, 117, 155, 148, 155, 143, 159, 182, 174, 148, 162, 167, 166, 168, 169, 169, 171, 173, 170, 165, 160, 159, 161, 164, 164, 161, 161, 163, 165, 165},
{161, 168, 175, 167, 168, 174, 172, 179, 172, 164, 160, 159, 174, 175, 175, 165, 175, 176, 194, 192, 176, 191, 177, 157, 145, 135, 130, 105, 91, 87, 126, 105, 69, 73, 57, 54, 39, 48, 23, 22, 29, 31, 38, 46, 41, 39, 35, 43, 46, 38, 38, 23, 42, 21, 38, 37, 84, 88, 121, 131, 123, 123, 134, 122, 148, 161, 168, 170, 186, 162, 157, 161, 160, 165, 162, 164, 170, 169, 166, 161, 158, 163, 166, 165, 161, 159, 159, 161, 166, 167},
{158, 157, 175, 178, 157, 165, 172, 162, 161, 163, 163, 172, 175, 164, 164, 182, 192, 191, 189, 179, 181, 190, 170, 151, 142, 131, 98, 108, 116, 99, 128, 71, 82, 62, 56, 82, 49, 48, 36, 36, 33, 42, 44, 43, 40, 52, 53, 54, 43, 51, 38, 25, 25, 57, 48, 57, 39, 55, 93, 142, 170, 150, 139, 122, 134, 157, 171, 182, 163, 163, 169, 160, 162, 164, 160, 162, 166, 164, 162, 157, 160, 162, 163, 161, 156, 153, 157, 164, 168, 169},
{152, 160, 160, 167, 159, 150, 149, 162, 161, 169, 168, 182, 177, 173, 172, 184, 191, 188, 180, 175, 186, 190, 168, 141, 125, 126, 118, 113, 107, 109, 125, 85, 74, 73, 55, 77, 78, 43, 41, 49, 39, 45, 48, 53, 46, 53, 67, 87, 69, 38, 57, 56, 46, 44, 94, 99, 93, 65, 107, 137, 131, 156, 162, 156, 162, 139, 162, 168, 162, 158, 161, 164, 159, 159, 157, 163, 166, 162, 160, 154, 157, 159, 162, 160, 154, 150, 154, 162, 167, 167},
{169, 161, 158, 168, 163, 150, 165, 178, 161, 163, 162, 178, 174, 178, 176, 165, 180, 173, 169, 176, 178, 188, 175, 140, 120, 134, 126, 100, 118, 121, 87, 90, 83, 69, 48, 45, 41, 37, 47, 56, 43, 53, 51, 52, 51, 59, 56, 46, 20, 90, 97, 124, 65, 79, 110, 109, 124, 94, 83, 134, 144, 151, 149, 159, 160, 166, 157, 168, 153, 150, 148, 162, 155, 154, 154, 163, 165, 159, 155, 148, 148, 155, 161, 161, 155, 152, 155, 159, 163, 163},
{181, 170, 166, 156, 155, 160, 190, 185, 153, 158, 155, 170, 177, 172, 168, 160, 171, 171, 170, 184, 183, 191, 169, 137, 138, 131, 122, 133, 143, 124, 89, 74, 82, 57, 75, 45, 58, 52, 35, 45, 47, 57, 52, 53, 50, 51, 38, 18, 23, 48, 43, 43, 72, 80, 117, 144, 117, 108, 81, 110, 142, 153, 152, 153, 160, 162, 160, 160, 155, 166, 135, 153, 157, 154, 153, 161, 160, 155, 152, 143, 142, 151, 157, 155, 155, 158, 162, 162, 160, 159},
{154, 167, 179, 159, 154, 165, 177, 147, 140, 164, 154, 160, 177, 175, 168, 160, 179, 183, 176, 181, 192, 192, 160, 139, 131, 138, 135, 140, 129, 100, 83, 77, 86, 56, 59, 50, 49, 35, 29, 34, 38, 49, 50, 60, 53, 44, 37, 28, 22, 37, 41, 95, 105, 151, 84, 149, 135, 96, 120, 140, 142, 139, 154, 157, 154, 158, 153, 152, 149, 147, 156, 160, 162, 156, 153, 158, 157, 156, 158, 150, 141, 146, 148, 148, 153, 162, 167, 167, 158, 157},
{158, 157, 172, 162, 137, 150, 162, 145, 131, 157, 150, 158, 161, 173, 173, 153, 184, 180, 177, 167, 187, 187, 167, 155, 144, 138, 151, 136, 104, 98, 99, 85, 79, 86, 39, 52, 38, 36, 13, 37, 28, 46, 44, 53, 55, 57, 45, 18, 27, 23, 15, 57, 77, 137, 73, 154, 129, 115, 133, 149, 154, 143, 151, 143, 158, 160, 147, 149, 140, 173, 167, 158, 164, 157, 153, 157, 157, 162, 167, 158, 143, 141, 142, 148, 156, 162, 164, 163, 153, 152},
{143, 154, 156, 166, 159, 144, 127, 163, 133, 144, 151, 176, 147, 162, 177, 157, 162, 156, 182, 174, 191, 186, 175, 155, 129, 128, 131, 121, 114, 109, 109, 97, 77, 62, 65, 39, 33, 32, 16, 18, 41, 47, 37, 47, 50, 53, 56, 47, 42, 25, 38, 39, 36, 91, 123, 152, 124, 108, 137, 152, 156, 155, 119, 142, 152, 160, 161, 173, 171, 160, 163, 162, 164, 158, 154, 157, 156, 162, 168, 157, 143, 137, 140, 153, 163, 161, 156, 153, 148, 147},
{132, 153, 132, 176, 155, 109, 151, 160, 138, 155, 151, 186, 152, 144, 166, 164, 169, 152, 180, 169, 181, 183, 171, 136, 115, 135, 125, 127, 128, 120, 114, 83, 78, 71, 71, 47, 28, 24, 24, 20, 37, 54, 44, 45, 48, 46, 51, 45, 37, 30, 26, 18, 16, 31, 124, 135, 110, 128, 137, 153, 152, 148, 144, 134, 166, 152, 158, 166, 170, 177, 175, 172, 168, 165, 158, 165, 163, 164, 154, 151, 145, 151, 148, 158, 161, 158, 144, 138, 139, 146},
{133, 140, 128, 178, 144, 92, 164, 176, 162, 161, 167, 176, 150, 137, 160, 182, 163, 148, 175, 187, 195, 179, 156, 130, 115, 108, 115, 135, 124, 104, 78, 85, 87, 82, 72, 36, 23, 42, 36, 32, 41, 43, 42, 44, 41, 35, 44, 49, 30, 30, 23, 35, 17, 31, 62, 95, 89, 121, 133, 135, 112, 137, 111, 138, 144, 153, 165, 166, 175, 177, 187, 173, 176, 174, 166, 169, 169, 169, 157, 153, 152, 152, 157, 164, 160, 145, 138, 135, 139, 145},
{137, 140, 119, 127, 137, 141, 179, 159, 152, 145, 152, 124, 157, 141, 152, 155, 152, 161, 178, 186, 181, 175, 159, 138, 115, 108, 133, 129, 119, 110, 85, 78, 83, 76, 66, 44, 53, 58, 33, 40, 44, 53, 46, 49, 45, 44, 43, 33, 32, 27, 26, 34, 23, 23, 34, 65, 63, 69, 82, 73, 116, 97, 140, 116, 137, 149, 174, 176, 176, 173, 172, 176, 176, 175, 165, 164, 168, 169, 159, 157, 159, 154, 165, 166, 159, 138, 138, 142, 149, 149},
{153, 129, 130, 131, 129, 142, 161, 153, 158, 142, 134, 168, 148, 109, 134, 141, 143, 175, 181, 181, 168, 176, 161, 135, 127, 121, 107, 93, 117, 114, 88, 90, 85, 94, 78, 65, 63, 55, 33, 57, 60, 49, 40, 42, 49, 30, 37, 33, 33, 25, 25, 26, 21, 18, 42, 50, 56, 68, 81, 60, 62, 103, 118, 134, 149, 156, 142, 170, 175, 177, 177, 174, 170, 169, 158, 155, 161, 165, 163, 165, 165, 166, 170, 163, 158, 145, 143, 151, 159, 162},
{148, 139, 120, 112, 121, 157, 174, 162, 161, 128, 117, 139, 132, 150, 140, 151, 152, 160, 150, 167, 164, 169, 161, 154, 124, 109, 116, 118, 105, 110, 105, 108, 104, 84, 67, 72, 76, 54, 52, 52, 46, 60, 44, 62, 43, 42, 30, 27, 24, 25, 18, 29, 13, 25, 31, 38, 46, 59, 67, 55, 96, 78, 114, 152, 144, 151, 162, 177, 178, 188, 165, 165, 170, 169, 162, 156, 159, 162, 165, 170, 169, 181, 175, 161, 157, 157, 143, 148, 157, 169},
{162, 156, 122, 157, 132, 130, 193, 157, 137, 131, 118, 127, 122, 141, 158, 109, 121, 150, 152, 154, 157, 177, 167, 138, 116, 106, 129, 97, 81, 89, 112, 126, 104, 98, 90, 98, 60, 51, 60, 33, 59, 147, 48, 63, 63, 42, 34, 26, 20, 23, 19, 28, 19, 32, 18, 42, 56, 77, 62, 74, 90, 121, 120, 129, 148, 164, 179, 181, 170, 157, 172, 185, 177, 175, 175, 166, 158, 153, 159, 165, 165, 181, 175, 160, 159, 166, 145, 144, 148, 161},
{147, 141, 147, 158, 152, 144, 145, 147, 151, 151, 113, 124, 122, 130, 123, 135, 142, 138, 142, 156, 156, 147, 147, 149, 152, 118, 125, 109, 104, 108, 128, 117, 103, 110, 119, 76, 87, 85, 107, 42, 70, 76, 62, 62, 56, 39, 33, 23, 22, 21, 24, 26, 27, 32, 33, 52, 59, 53, 72, 77, 73, 95, 123, 136, 152, 147, 180, 173, 171, 171, 176, 195, 184, 180, 183, 170, 151, 136, 146, 152, 158, 163, 170, 160, 160, 167, 153, 148, 142, 148},
{163, 187, 164, 163, 171, 144, 156, 155, 138, 167, 148, 110, 119, 137, 114, 124, 149, 130, 136, 151, 157, 144, 148, 153, 176, 177, 124, 133, 129, 143, 136, 128, 121, 137, 105, 108, 102, 116, 81, 60, 99, 96, 79, 86, 43, 41, 22, 26, 20, 23, 21, 34, 23, 30, 54, 53, 58, 43, 70, 80, 92, 80, 118, 128, 151, 154, 175, 165, 159, 179, 184, 190, 188, 180, 185, 169, 142, 123, 137, 144, 155, 148, 166, 161, 159, 162, 160, 153, 141, 143},
{155, 157, 156, 148, 159, 128, 137, 150, 156, 151, 131, 135, 158, 156, 143, 141, 136, 144, 134, 150, 155, 163, 155, 137, 168, 162, 122, 165, 163, 151, 181, 132, 139, 132, 112, 114, 133, 103, 71, 59, 107, 65, 85, 164, 83, 78, 28, 23, 23, 20, 26, 33, 28, 40, 50, 39, 56, 98, 52, 140, 69, 85, 91, 124, 145, 160, 163, 164, 163, 185, 183, 186, 182, 182, 171, 133, 113, 116, 133, 151, 153, 151, 160, 166, 164, 162, 135, 141, 142, 157},
{174, 159, 145, 142, 140, 156, 164, 129, 156, 139, 139, 161, 160, 170, 164, 155, 135, 139, 148, 143, 138, 153, 154, 135, 164, 152, 145, 157, 166, 156, 126, 141, 155, 148, 135, 111, 139, 117, 85, 132, 118, 78, 84, 144, 95, 174, 115, 81, 25, 45, 51, 58, 31, 35, 35, 39, 46, 44, 84, 126, 71, 81, 88, 137, 138, 154, 156, 150, 165, 169, 172, 174, 163, 160, 128, 113, 111, 115, 138, 159, 171, 171, 169, 158, 133, 121, 130, 130, 144, 149},
{153, 138, 132, 130, 128, 136, 136, 133, 159, 139, 137, 168, 138, 167, 155, 147, 141, 118, 139, 158, 136, 143, 144, 164, 163, 148, 132, 158, 172, 147, 144, 133, 155, 143, 134, 137, 142, 107, 113, 133, 94, 77, 121, 152, 156, 156, 129, 166, 37, 81, 98, 115, 38, 151, 59, 59, 36, 41, 69, 86, 143, 99, 84, 130, 126, 133, 146, 124, 134, 161, 155, 149, 149, 146, 107, 122, 99, 121, 146, 171, 168, 159, 139, 115, 95, 110, 104, 98, 128, 145},
{177, 129, 122, 124, 162, 142, 116, 138, 181, 138, 127, 158, 155, 165, 143, 145, 144, 117, 153, 145, 146, 136, 156, 168, 173, 167, 177, 178, 153, 125, 162, 138, 171, 129, 119, 131, 137, 123, 140, 125, 100, 140, 143, 161, 183, 147, 158, 164, 180, 168, 93, 159, 132, 137, 60, 99, 65, 59, 64, 115, 92, 106, 112, 122, 127, 142, 144, 147, 177, 152, 154, 121, 153, 130, 99, 95, 118, 128, 137, 153, 137, 126, 103, 85, 114, 116, 127, 124, 128, 145},
{159, 116, 125, 131, 150, 124, 127, 145, 151, 123, 139, 138, 157, 147, 148, 150, 148, 138, 149, 133, 130, 131, 143, 141, 162, 156, 162, 157, 151, 154, 171, 149, 153, 121, 143, 162, 144, 143, 168, 126, 156, 159, 157, 146, 155, 160, 190, 147, 159, 157, 157, 135, 131, 158, 87, 146, 83, 88, 92, 112, 127, 104, 120, 119, 146, 126, 144, 169, 149, 109, 136, 120, 148, 119, 121, 122, 129, 134, 116, 138, 110, 78, 84, 102, 99, 120, 91, 149, 133, 125},
{129, 119, 121, 142, 140, 121, 141, 143, 135, 129, 155, 151, 138, 136, 155, 164, 166, 144, 151, 131, 143, 121, 143, 135, 146, 148, 128, 141, 138, 152, 161, 149, 129, 142, 143, 139, 140, 136, 139, 128, 160, 161, 141, 145, 146, 159, 149, 169, 163, 157, 142, 144, 144, 144, 138, 146, 171, 123, 166, 72, 157, 140, 122, 135, 151, 116, 158, 131, 108, 100, 132, 130, 147, 110, 131, 112, 137, 111, 94, 119, 87, 61, 69, 63, 66, 131, 117, 127, 160, 151},
{120, 131, 125, 144, 139, 128, 131, 137, 142, 126, 135, 161, 132, 128, 138, 156, 150, 134, 135, 136, 124, 128, 137, 127, 143, 139, 137, 144, 142, 154, 146, 149, 154, 140, 150, 137, 138, 159, 133, 120, 149, 147, 138, 146, 154, 158, 174, 134, 140, 169, 107, 164, 149, 142, 128, 147, 152, 97, 135, 138, 141, 139, 102, 143, 131, 142, 167, 110, 171, 128, 153, 142, 186, 161, 124, 119, 159, 150, 113, 131, 125, 51, 52, 44, 53, 127, 102, 125, 110, 114},
{125, 122, 123, 129, 135, 149, 136, 138, 113, 125, 144, 146, 127, 121, 136, 140, 146, 124, 136, 148, 127, 132, 139, 130, 134, 151, 161, 157, 165, 146, 130, 138, 137, 136, 142, 152, 134, 144, 149, 124, 141, 131, 137, 138, 137, 165, 147, 133, 129, 151, 123, 164, 172, 136, 143, 155, 147, 122, 106, 112, 111, 135, 116, 136, 116, 122, 143, 129, 150, 115, 135, 174, 156, 147, 149, 160, 134, 129, 139, 115, 119, 61, 87, 63, 95, 121, 111, 132, 111, 105},
{119, 125, 119, 123, 142, 157, 135, 123, 114, 129, 158, 126, 117, 122, 129, 129, 141, 128, 129, 149, 156, 141, 133, 140, 156, 167, 164, 148, 148, 143, 143, 137, 133, 135, 138, 143, 143, 155, 134, 138, 151, 118, 124, 130, 130, 149, 141, 128, 113, 144, 144, 158, 156, 135, 135, 154, 135, 111, 108, 139, 138, 138, 127, 127, 110, 105, 142, 110, 134, 112, 113, 141, 134, 127, 132, 174, 119, 110, 124, 115, 112, 135, 161, 55, 104, 124, 127, 132, 121, 133},
{116, 115, 122, 138, 149, 157, 138, 122, 118, 126, 136, 115, 123, 134, 135, 134, 128, 117, 132, 147, 154, 145, 139, 151, 144, 151, 133, 129, 135, 130, 148, 138, 138, 128, 134, 133, 131, 143, 139, 137, 143, 110, 124, 132, 133, 141, 134, 129, 106, 135, 154, 140, 131, 153, 144, 129, 134, 124, 139, 132, 153, 116, 125, 127, 124, 131, 136, 117, 113, 92, 108, 130, 148, 138, 138, 139, 123, 91, 92, 105, 127, 175, 163, 88, 87, 110, 98, 121, 103, 119},
{123, 122, 135, 143, 140, 153, 143, 117, 123, 129, 121, 111, 122, 130, 130, 131, 125, 114, 138, 142, 144, 138, 137, 148, 133, 137, 126, 130, 130, 123, 141, 135, 138, 124, 134, 137, 123, 138, 142, 136, 139, 113, 119, 131, 134, 121, 129, 127, 121, 126, 151, 133, 91, 105, 121, 117, 115, 127, 134, 112, 135, 110, 118, 128, 132, 142, 116, 116, 138, 115, 121, 146, 162, 154, 132, 108, 146, 157, 120, 102, 129, 154, 139, 89, 133, 121, 110, 107, 117, 132},
{131, 131, 141, 138, 129, 137, 132, 112, 127, 131, 118, 119, 120, 125, 127, 126, 117, 108, 128, 127, 127, 118, 124, 125, 121, 116, 124, 127, 123, 120, 121, 123, 136, 127, 129, 143, 119, 142, 143, 143, 126, 114, 112, 129, 140, 112, 130, 121, 119, 147, 133, 110, 91, 89, 110, 117, 114, 131, 123, 104, 112, 125, 110, 119, 108, 124, 118, 114, 153, 130, 137, 159, 135, 148, 157, 104, 122, 123, 106, 85, 102, 120, 120, 99, 128, 102, 102, 113, 146, 133},
{129, 125, 133, 134, 127, 118, 111, 111, 142, 139, 129, 135, 122, 123, 125, 115, 108, 105, 115, 118, 122, 110, 121, 109, 112, 100, 104, 112, 114, 118, 117, 119, 133, 122, 112, 123, 115, 140, 142, 146, 118, 116, 123, 131, 148, 121, 126, 114, 129, 152, 131, 116, 103, 103, 129, 111, 113, 113, 118, 105, 108, 131, 109, 116, 107, 114, 126, 122, 147, 137, 162, 149, 110, 116, 112, 119, 104, 114, 90, 92, 110, 110, 109, 105, 107, 104, 98, 114, 148, 122},
{125, 125, 129, 122, 121, 113, 107, 111, 141, 141, 141, 143, 119, 117, 125, 116, 113, 114, 114, 121, 126, 113, 120, 103, 101, 102, 96, 107, 106, 108, 119, 123, 121, 105, 96, 99, 115, 127, 133, 130, 116, 116, 136, 126, 147, 139, 131, 128, 150, 147, 122, 104, 106, 104, 111, 110, 101, 86, 100, 107, 100, 121, 107, 128, 131, 120, 104, 115, 137, 128, 144, 120, 100, 105, 102, 114, 98, 102, 89, 93, 97, 90, 114, 103, 106, 111, 107, 115, 119, 133},
{126, 127, 127, 110, 113, 120, 121, 116, 125, 132, 137, 132, 112, 114, 128, 130, 118, 117, 112, 115, 120, 114, 114, 104, 102, 113, 110, 112, 101, 100, 110, 121, 113, 101, 102, 104, 118, 119, 125, 116, 110, 122, 133, 118, 137, 137, 137, 141, 150, 124, 110, 91, 93, 106, 110, 97, 106, 87, 90, 112, 100, 115, 108, 128, 142, 135, 113, 115, 129, 116, 115, 108, 96, 112, 114, 131, 86, 108, 95, 100, 95, 76, 91, 91, 104, 118, 93, 91, 106, 144},
{124, 117, 120, 111, 117, 125, 130, 122, 130, 134, 131, 118, 108, 112, 120, 124, 117, 114, 109, 109, 115, 119, 117, 118, 121, 126, 128, 116, 105, 110, 105, 123, 118, 113, 118, 125, 119, 118, 125, 118, 116, 141, 132, 118, 126, 111, 122, 118, 123, 123, 121, 107, 108, 98, 98, 108, 110, 92, 92, 109, 117, 118, 117, 117, 119, 114, 122, 103, 111, 122, 114, 96, 109, 87, 110, 141, 104, 114, 107, 106, 133, 89, 87, 80, 113, 116, 91, 88, 93, 101},
{126, 124, 120, 113, 124, 129, 131, 126, 126, 133, 129, 120, 109, 103, 108, 109, 115, 117, 116, 114, 120, 130, 133, 130, 133, 133, 122, 118, 111, 105, 118, 123, 118, 123, 126, 126, 123, 127, 132, 124, 119, 136, 135, 123, 124, 114, 115, 119, 131, 124, 108, 120, 121, 114, 115, 120, 128, 105, 110, 125, 108, 114, 112, 117, 134, 140, 140, 139, 122, 123, 114, 120, 110, 85, 113, 128, 116, 101, 122, 131, 130, 91, 91, 92, 103, 107, 100, 109, 103, 101},
{132, 131, 127, 119, 129, 132, 133, 127, 127, 133, 129, 120, 108, 101, 105, 105, 113, 117, 119, 119, 125, 136, 144, 144, 138, 136, 123, 120, 115, 110, 121, 124, 118, 123, 125, 125, 122, 126, 134, 127, 126, 143, 141, 128, 128, 117, 117, 121, 129, 134, 123, 127, 130, 136, 140, 139, 138, 117, 121, 130, 109, 114, 113, 119, 136, 145, 147, 144, 124, 125, 117, 122, 117, 91, 115, 130, 121, 105, 122, 130, 124, 118, 128, 106, 102, 115, 112, 109, 108, 106}
    };


    //printf("Aplicando a transformada em uma imagem de %dx%d ...\n", IMAGE_SIZE, IMAGE_SIZE);
    //printf("Saída será do tamanho %dx%d\n", IMAGE_SIZE / 2, IMAGE_SIZE / 2);

    //struct timespec start, end;
    //clock_gettime(CLOCK_MONOTONIC, &start);

    haarTransform2d(input_image);

    //clock_gettime(CLOCK_MONOTONIC, &end);

    //double tempo_execucao = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    //printf("Tempo de execução da Transformação de Haar: %f segundos\n", tempo_execucao);

    //printf("Execucao Completa.\n");
    
    //while(true);
    //for(;;);
}