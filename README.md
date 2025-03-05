# Haar Transformation 2D
Using the 2D Haar Transform to compress PGM P2 images

<div style="display: flex; justify-content: center; gap: 3%;">
    <img src="images/assets/onboarding/BeforeHaar2D.png" width="49%">
    <img src="images/assets/onboarding/AfterHaar2D.png" width="49%">
</div>

## 🌍 Read in another language
- 🇧🇷 [Portuguese-BR](README.pt.md)

## 📄 License  
This project is licensed under the [MIT License](LICENSE).  

## 📖 What will you find here?  
This project, developed during the Embedded Systems course, was divided into two parts:  
1. Designing the algorithm correctly, specifying data input/output, analyzing complexities, and building and defining tests so that everything runs on a PC.  
2. Porting the algorithm to an embedded system, making the necessary modifications and managing memory.  
3. Proposing and implementing optimizations in an embedded application to reduce computation time or memory usage.  

## Part 1: Algorithm in the PC Environment  

### 🎯 Objective  
Develop an algorithm to apply the 2D Haar Transform to images in PGM P2 format. The focus is on correctly defining data inputs and outputs, analyzing computational complexity, and creating automated tests to ensure proper functionality.  

### 🛠 Technologies Used  
- Programming languages: C, Python  
- Testing tools: Haar Transform using the Pywavelets library  

### 🌐 Development Environment  
- Operating System: PopOS 22.04 LTS and Windows 10  
- IDE/Editor: VSCode  
- Compiler/Interpreter: GCC and Python 3.8+  

### 🚧 Development  

1. **Data Input:**  
   - Square images in PGM P2 format with a 90x90 resolution.  

2. **Data Output:**  
   - Image compressed to a 45x45 resolution using the 2D Haar Transform.  

3. **Implementation of the Base Algorithm:**  
   - The implemented algorithm can be viewed in the file [**haar_transformation_2d.c**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work1/haar_transformation_2d.c).  
   - The following libraries were used: <stdio.h>, <stdlib.h>, <string.h>, and <math.h>.  

4. **Complexities:**  
   - **Worst case:** O(NxM), where N is the number of rows and M is the number of columns.  
   - **Best case:** O(NxM), where N is the number of rows and M is the number of columns, as it requires traversing all image elements.  

5. **Initial Unit Tests to Validate the Transformations:**  
   - In the tests performed, we obtained the following results by comparing the outputs of the algorithms [**haar_transformation_2d.c**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work1/haar_transformation_2d.c) with [**haar_wavelet.py**](https://github.com/Joaosa100/Haar-Transformation/blob/main/tests/haarWavelet.py) using [**validacao.py**](https://github.com/Joaosa100/Haar-Transformation/blob/main/tests/validacao.py):  
   <br>  

   | **Original Image** | **C Result** | **Python Result** |
   |----------------------|------------------|----------------------|
   | ![Original Image](images/assets/firstAlgorithmTest//animal3Source.jpeg) <br> `Animal_Source.pgm` | ![Haar Transformation - C](images/assets/firstAlgorithmTest/animal390.jpeg) <br> `Haar_C_result.pgm` | ![Haar Wavelet - Python](images/assets/firstAlgorithmTest/animal390_pywt.jpeg) <br> `Haar_Pywavelet_Result.pgm` |

   - Using the algorithm to compare each pixel of the results:
     <br>
      ![Validation - py](images/assets/firstAlgorithmTest/comp90er.png)

       *Differences between the results obtained from the algorithm implemented in C and Python (Pywavelets). Each white dot represents a discrepancy identified in the Haar transformation. A total of 892 pixels differed out of 8100 (90x90), resulting in an 11.01% error using a zero-difference tolerance.*

   - Now, discarding other regions of the image and using the compressed result (45x45):


   | **Original Image** | **C Result** | **Python Result** |
   |----------------------|------------------|----------------------|
   | ![Original Image](images/assets/firstAlgorithmTest//animal3Source.jpeg) <br> `Animal_Source.pgm` | ![Haar Transformation - C](images/assets/firstAlgorithmTest/animal345.jpeg) <br> `Haar_C_result.pgm` | ![Haar Wavelet - Python](images/assets/firstAlgorithmTest/animal345_pywt.jpeg) <br> `Haar_Pywavelet_Result.pgm` |

   - Using the algorithm to compare each pixel of the results:
     <br>
      ![Validation - py](images/assets/firstAlgorithmTest/comp45er.png)

      *Differences between the results obtained from the algorithm implemented in C and Python (Pywavelets) using only the compressed part. Each white dot represents a discrepancy identified in the Haar transformation. A total of 87 pixels differed out of 2025 (45x45), resulting in a 4.3% error using a zero-difference tolerance.*

6. **Improving the Algorithm:**
   - Even with a slight difference, it was necessary to achieve 100% similarity with the output from Pywavelets, so we modified the algorithm and saved it in this file [**haar_transform_2d.c**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work1/haar_transform_2d.c).
   - We also saved a version with all the frequency sub-bands in [**haar_all_2d.c**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work1/haar_all_2d.c).
   - We removed the <math.h> library:<br>
   ```c
      // Before, the Haar2D function called Haar1D iteratively:
      void haarTransform1D(double data[], int length) {
         double temp[MAX_SIZE];
         int half = length / 2;

         for (int i = 0; i < half; i++) {
            temp[i] = (data[2 * i] + data[2 * i + 1]) / sqrt(2.0);
            temp[half + i] = (data[2 * i] - data[2 * i + 1]) / sqrt(2.0);
         }

         for (int i = 0; i < length; i++) {
            data[i] = temp[i];
         }
      }

      // Now, without <math.h>, all the calculations remain in the Haar2D function:
      void haarTransform2D(double input[MAX_SIZE][MAX_SIZE], double output[MAX_SIZE][MAX_SIZE], int input_size, int *output_size) {
         int half = input_size / 2;
         *output_size = half;

         for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                  double a = input[2*i][2*j];
                  double b = input[2*i][2*j+1];
                  double c = input[2*i+1][2*j];
                  double d = input[2*i+1][2*j+1];

                  output[i][j] = (a + b + c + d) / 2.0;
            }
         }
      }
   ```
   - Thus, the results using the [**haar_transform_2d.c**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work1/haar_transform_2d.c) were:
   <br>

   | **Original Image** | **C Result** | **Python Result** |
   |----------------------|------------------|----------------------|
   | ![Original Image](images/assets/firstAlgorithmTest//animal3Source.jpeg) <br> `Animal_Source.pgm` | ![Haar Transformation - C](images/assets/improvedAlgorithmTest/animal3Imp.jpeg) <br> `Haar_C_result.pgm` | ![Haar Wavelet - Python](images/assets/firstAlgorithmTest/animal345_pywt.jpeg) <br> `Haar_Pywavelet_Result.pgm` |

   - Using the algorithm to compare each pixel of the results:
     <br>
      ![Validation - py](images/assets/improvedAlgorithmTest/comp45LL.png)

      *Differences between the results obtained from the algorithm implemented in C and Python (Pywavelets) using only the compressed part. Each white dot represents a discrepancy identified in the Haar transformation. There was a difference in 0 pixels out of 2025 (45x45), resulting in 0.0% error using a zero-difference tolerance.*

7. **RAM Consumption Measurement**  
   - Compile the code to generate the executable in the same way we did for the tests:<br>
   ```bash
   gcc -o myExec haar_transform_2d.c -lm
   ``` 
   - To find out how much RAM is required to run the code, we used the following terminal command on a Linux system:<br>
   ```bash
   size <myExec>
   ```
   - Generated output:<br>
     ![ram](images/assets/improvedAlgorithmTest/ramCons.png)

   - As you can see, only these two consume RAM:
      - **data**: Initialized data segment. This segment stores global and static variables that have values explicitly assigned in the code.
      - **bss**: Uninitialized data segment. This segment stores global and static variables that are declared but have no initial values set (or are implicitly initialized to zero).
      - This code requires **704 bytes** of RAM to run.

---

## Part 2: Algorithm in the Embedded Environment  
### 🎯 Objective  
With the algorithm working correctly on a PC, we now need to run it properly on an STM32 board with extremely limited memory.  

### 🛠 Technologies Used  
- Programming languages: C, Python, and C++  
- Testing tools: Haar Transform using the Pywavelets library  

### 🌐 Development Environment  
- Operating System: PopOS 22.04 LTS and Windows 10  
- IDE/Editor: Keil Studio Cloud  
- Compiler/Interpreter: GCC, Python 3.8+, G++ (Keil Studio Cloud)  

### ⚙️ Board Used  
The board selected for this project was the **NUCLEO-F030R8** from STMicroelectronics.  

#### 📋 Main Specifications:  
- **Processor**: ARM Cortex-M0  
- **Frequency**: 48 MHz  
- **Flash Memory**: 64 KB  
- **SRAM**: 8 KB   

#### 🖼️ Board Image:  
![NUCLEO-F030R8](images/assets/secondAlgorithmTest/NUCLEOF030R8.webp)  
*Representation of the NUCLEO-F030R8 board used in the project.*  

---  

### 🛠️ Challenges  
Working with an embedded environment presented several challenges, especially due to hardware limitations and constraints imposed by the academic context. Below are the main issues we faced:  

1. **Amount of Data**  
   - A PGM P2 image with a resolution of 90x90 pixels contains **8100 integers**. Loading this entire volume of data into the board's RAM at once was unfeasible since the available memory for execution was smaller than the input size.  

2. **Data Input and Output**  
   - The board does not have direct communication with the PC, meaning that even if the build was correct, it could not autonomously locate or access files on the computer.  

3. **Board Unavailability**  
   - It was not allowed to take the board home, as it was the property of the University laboratory.  
   - We had a total of **8 hours**, divided into 4 classes (2 hours each), to familiarize ourselves with the device, make code adjustments, and validate the tests.  

4. **Keil Studio Cloud**  
   - Although there are various tools for embedded systems programming, we chose **Keil Studio Cloud** due to its simplicity and quick setup. However, the tool presented several limitations and headaches during the process.  

5. **Outdated Software**  
   - The board was only compatible with the **MBED OS 2** API, a discontinued version.  
   - Finding functional projects in **Keil Studio Cloud** was challenging, as only one buildable project was available for this API version. Additionally, all official documentation for MBED OS 2 had been replaced with newer versions (OS 5 and OS 6), making studying and applying this API difficult.  

---

### 🚧 Development  
### 🧑‍💻 First Day - Warm-up  

We were introduced to how to create a "Hello World" on the board, the famous Blinky LED using Keil Studio Cloud.  

| **Step**                     | **Description**                                                                                                   | **Image**                                                                                |
|------------------------------|-------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------|
| **1. Create an Account**     | Create an account on Arm MBED                                                                                    | --                                                                                       |
| **2. Access Keil Studio**    | Access Keil Studio Cloud                                                                                         | --                                                                                       |
| **3. New Project**           | Create a new active project                                                                                      | ![Create project](images/assets/secondAlgorithmTest/mbedTutorial/mbedNewProject.png)    |
| **4. Select OS 2**           | Choose the only available Mbed OS 2 project                                                                      | ![Select OS 2](images/assets/secondAlgorithmTest/mbedTutorial/mbedSelectOS2.png)        |
| **5. Name the Project**      | Rename the project and click "Add"                                                                               | ![Add project](images/assets/secondAlgorithmTest/mbedTutorial/mbeAddProjectOS2.png)    |
| **6. Project Appearance**    | The created project looks like this                                                                              | ![Appearance](images/assets/secondAlgorithmTest/mbedTutorial/mbedOS2Main.png)          |
| **7. Choose the Board**      | We selected the NUCLEO-F030R8 board for this project                                                             | ![Choose board](images/assets/secondAlgorithmTest/mbedTutorial/mbedBuildTarget.png)    |
| **8. Connect the Board**     | We used a USB V3 cable to connect the NUCLEO-F030R8 board to the PC with Keil Studio Cloud.                      | ![Connect board](images/assets/secondAlgorithmTest/mbedTutorial/mbedConnectMIcro.png)  |
| **9. Build and Run**         | Build the project and run it on the board by pressing the "play" button or build using the "hammer" button and manually dragging the binary file onto the board | ![Build and run](images/assets/secondAlgorithmTest/mbedTutorial/mbedBuildNRun.png)     |

> **Note:** On the same day, we encountered a problem: some boards were defective and would not connect to the PC, and we unknowingly took one of them. We spent a long time trying to run the Blinky code on one of these defective boards, unaware of the issue. Of course, the professor did not provide any support for what we were doing but mentioned that he would bring more boards in the following days. Observing our colleagues, we realized that there were only a few functional boards available. Given this, we concluded that we would not have enough time to test code modifications at that moment. We were forced to leave these changes for **Day 2**, when we finally gained access to a working board.  


---

### 🙏 Second Day - Finally, a Working Board  
As more boards were available on this day, we were finally able to get a functional one for testing.  

### ==> Checkpoint 1  
After an hour of modifying the code and better understanding how the API communication worked in practice (since we couldn't test at home), we discovered that a library needed to be added, but it was neither mentioned in the API documentation nor by the professor. This was the **register library**.  
```c
#include "stm32f0xx.h"
```
So, we used the last hour to test the code directly on the board. Since we were still learning how to use it, we opted for smaller images to avoid exceeding the board's RAM limit. From this, we arrived at the first version of our code, which we named [**Checkpoint 1**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/checkpoint1.cpp), as there was no way we would let this be the final version.  

```c
// Define parameters
#define MAX_SIZE 40
#define IMAGE_SIZE 40

// Initialize serial interface
Serial pc(SERIAL_TX, SERIAL_RX);

// Function to perform 2D Haar transform (LL coefficients only)
void haarTransform2D(const int input[MAX_SIZE][MAX_SIZE], int output[MAX_SIZE][MAX_SIZE], int input_size, int *output_size) {
    int half = input_size / 2;
    *output_size = half;

    // Calculate only LL coefficients
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            double a = input[2*i][2*j];
            double b = input[2*i][2*j+1];
            double c = input[2*i+1][2*j];
            double d = input[2*i+1][2*j+1];
            
            // Calculate LL coefficient and round to integer
            output[i][j] = (int)((a + b + c + d) / 2.0);
        }
    }
}

// Function to print the Haar transformation result
void printResult(int matrix[MAX_SIZE][MAX_SIZE], int size) {
    printf("Transformation Result (showing first few elements):\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            int val = matrix[i][j];
            if (val > 255) val = 255;
            if (val < 0) val = 0;
            printf("%4d ", val);
        }
        printf("\n");
    }
}

// ...

// Define the input image matrix directly in the code
    static const int input_image[MAX_SIZE][MAX_SIZE] = {
      //matrix here
    }

```
> Since we had limited time, we adapted some of the previous code (Part 1) and created a print function—only to realize, moments after the class had ended, that it was unnecessary. However, the goal was always to learn from mistakes as they arose.  

---

### 🔥 Third Day - Code Demonstration  
Today was different—it was the day to **demonstrate the code to the professor**, and knowing him, we would definitely lose points if we presented a program that couldn't process an **input of at least 8000 integers**.  

We were under a lot of pressure because of this, but since we were the last team to demonstrate the code, we took advantage of the extra time.  

### ==> Checkpoint 2  
After an hour and a half of modifying and testing the code, we identified some areas for improvement to handle 8000 input integers. As a result, we achieved [**Checkpoint 2**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/checkpoint2.cpp). However, we only had a short time to add comments to some parts to make it easier for the professor to read (he requested this as he had to evaluate more than 10 different codes on the same day).  
```c
// Define small block size for processing
#define BLOCK_SIZE 10 
#define IMAGE_SIZE 90

// Initialize serial interface
Serial pc(SERIAL_TX, SERIAL_RX);

// Process image in small blocks
void haarTransform2D(const int input[][IMAGE_SIZE]) {
    printf("Transform Result:\n");
    
    // Process each block
    for (int blockRow = 0; blockRow < IMAGE_SIZE; blockRow += BLOCK_SIZE) {
        // Need to combine multiple row outputs
        for (int subRow = 0; subRow < BLOCK_SIZE/2; subRow++) {
            // Process each block in this row
            for (int blockCol = 0; blockCol < IMAGE_SIZE; blockCol += BLOCK_SIZE) {
                int baseRow = blockRow + (2 * subRow);
                for (int j = 0; j < BLOCK_SIZE/2; j++) {
                    int baseCol = blockCol + (2 * j);
                    
                    // Process single 2x2 block
                    int sum = input[baseRow][baseCol] +
                             input[baseRow][baseCol+1] +
                             input[baseRow+1][baseCol] +
                             input[baseRow+1][baseCol+1];
                    
                    int val = sum / 2;
                    val = (val < 0) ? 0 : ((val > 255) ? 255 : val);
                    printf("%4d ", val);
                }
            }
            printf("\n");
        }
    }
}

// ...

// Define the input image matrix directly in the code
    static const int input_image[MAX_SIZE][MAX_SIZE] = {
      //matrix here
    }
```
> We managed to address basic aspects such as printing the output after the calculation and using only integers before the demonstration. However, during the demo, the professor pointed out that the use of BLOCK_SIZE was unnecessary.  

We successfully met our main goal of processing 8000 integers with limited memory. However, we were not going to leave that unnecessary BLOCK_SIZE in the code. So, we decided to use the next day to clean up and optimize everything.  

---

### 🧹 Fourth Day - The Final Code for the Board  
The hardest part was over—now we just needed to clean up the code and remove BLOCK_SIZE.  

We started by analyzing our previous attempts and reviewing the calculation methodology. Since the code processes the input as it iterates, we only needed to iterate the required amount to collect the necessary indices for computation. So, we simply needed two FOR loops, and we removed BLOCK_SIZE because fragmenting the input was unnecessary; we just needed to process the required portion at a time.  

After cleaning up the code and adding some operational messages, we named this final version of the code for the board [**haar_transform_2d_stm.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/haar_transform_2d_stm.cpp).  

```c
#include "mbed.h"
#include <stdio.h>
#include "stm32f0xx.h"

#define IMAGE_SIZE 90

// Initialize serial interface
Serial pc(SERIAL_TX, SERIAL_RX);

void haarTransform2d(const int input[][IMAGE_SIZE]) {
    printf("Transform Result:\n");
    int col, row, sum;
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

//...

// Define the input image matrix directly in the code
    static const int input_image[MAX_SIZE][MAX_SIZE] = {
      //matrix here
    }

```
> We carefully reviewed and cleaned up the code, making it significantly easier to read.  

### Demonstration Result  
After everything, this was the result of the [**validation**](https://github.com/Joaosa100/Haar-Transformation/blob/main/tests/validacao.py) test for [**haar_transform_2d_stm.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/haar_transform_2d_stm.cpp) using [**haar_wavelet.py**](https://github.com/Joaosa100/Haar-Transformation/blob/main/tests/haarWavelet.py).  

   | **Original Image** | **C Result** | **Python Result** |
   |----------------------|------------------|----------------------|
   | ![Original Image](images/assets/firstAlgorithmTest//animal3Source.jpeg) <br> `Animal_Source.pgm` | ![Haar Transformation - C](images/assets/improvedAlgorithmTest/animal3Imp.jpeg) <br> `Haar_Transform_STM.pgm` | ![Haar Wavelet - Python](images/assets/firstAlgorithmTest/animal345_pywt.jpeg) <br> `Haar_Pywavelet_Result.pgm` |

   - Using the algorithm to compare each pixel of the results:  
     <br>
      ![Validation - py](images/assets/improvedAlgorithmTest/comp45LL.png)

      *Differences between the results obtained using the C implementation for the board and the Python (Pywavelets) implementation, considering only the compressed portion. Each white dot represents a divergence detected in the Haar transformation. There was a difference in 0 pixels out of 2025 (45x45), resulting in a total error of 0.0% with zero difference tolerance.*  

### Memory Consumption  
Mbed itself measures the memory usage of the .elf file during the build process before converting it to .bin.  
![ram](images/assets/secondAlgorithmTest/mbedTutorial/mbedAlgorithmMem.png)  

Since the entire input is now defined in the code, it is stored in flash, **adding +32 KB**.  

Now, the algorithm requires **872 bytes** to execute (an increase of **+168 bytes**).  

---

## Part 3: Analysis and Optimization  
### 🎯 Objective  
After validating the algorithm's functionality on both the PC and the embedded platform (STM32-F030R8), the next step is to evaluate and improve its performance, considering:  
1. **Performance measurements** 📊: Analyze execution time, memory usage, and power consumption (when applicable);  
2. **Code optimization** 🚀: Implement improvements focused on reducing computation time or memory usage on the STM32;  
3. **Platform comparison** 🔄: Observe differences between the PC environment and the embedded platform regarding the measurements before and after optimization.  

### 🛠 Technologies Used  
- Programming languages: C, Python, and C++  
- Testing tools: Haar Transform using the Pywavelets library  

### 🌐 Development Environment  
- Operating System: PopOS 22.04 LTS and Windows 10  
- IDE/Editor: Keil Studio Cloud and VSCode  
- Compiler/Interpreter: GCC, Python 3.8+, G++ (Keil Studio Cloud)  

---  
### 🚀 How Will the Optimization Be Performed?  
1. Select **ONE** of the parameters analyzed on the STM32 for optimization: **computation time OR memory usage**;  
2. Implement optimizations exclusively in the **algorithm implementation** section (without modifying data input or output results);  
3. Repeat the measurements to assess the impact of the optimization.  
---  

### 📏 How Will the Measurements Be Conducted?  
- Measurements will be performed under the same conditions for both platforms (PC and STM32) to ensure comparability. The analyzed parameters will be:  

#### 🖥️ For Both Platforms (PC and STM32):  
1. **⏱️ Computation Time** – Measured solely for the algorithm, excluding I/O operations, data generation, and printing;  
2. **📦 Code Memory Usage** – Space occupied by the application code, excluding input data;  
3. **🗄️ Data Memory Usage** – Space occupied by the data manipulated by the application.  

#### 🔋 Exclusive to the Embedded Platform (STM32):  
4. **⚡ Power Consumption** – Measurement of current and voltage during execution.  

---

### 🚧 Development  
During the available classes, we had to find a valid optimization and take current and voltage measurements on the board using both the old code (Part 2) and the optimized one (Part 3).  

Memory consumption measurements were possible without needing the board, but measuring computation time required running the code on it.  

### 🚀 Optimization Process  
We started with a memory consumption optimization by changing **int** types to **uint8_t** and **uint16_t**. Since integers consume 4 bytes while uint8_t and uint16_t consume 1 and 2 bytes respectively, we believed this would provide an acceptable memory improvement.  

Code before the memory consumption optimization:
```c
#include "mbed.h"
#include "stm32f0xx.h"
#include <stdio.h>

#define IMAGE_SIZE 90

Serial pc(SERIAL_TX, SERIAL_RX);

void haarTransform2d(const int input[][IMAGE_SIZE]) {
    int col, row, sum;
    printf("Resultado da Transformada:\n");
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
    static const int input_image[][IMAGE_SIZE] = {
      //matrix
   }
   //...
```
> Partial view of the code [**haar_transform_2d_stm.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/haar_transform_2d_stm.cpp)  

Code after replacing with uints:  
```c
#include "mbed.h"
#include "stm32f0xx.h"
#include <stdio.h>
#include <stdint.h>

#define IMAGE_SIZE 90

Serial pc(SERIAL_TX, SERIAL_RX);

void haarTransform2d(const uint8_t input[][IMAGE_SIZE]) {
    uint8_t col, row;
    uint16_t sum;
    printf("Resultado da Transformada:\n");
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
    static const uint8_t input_image[][IMAGE_SIZE] = {
      //matrix
    }
    //...
```
> Partial view of the code [**haar_transform_2d_stm_uint.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work3/original/haar_transform_2d_stm_uint.cpp)  

However, upon further analysis, we realized that most of the memory optimization impact came from the input data, which was initially **8100 integers of 4 bytes each** and was now **only 1 byte per value**. According to valid optimization rules, the majority of the improvement **cannot come from modifying input data**.  

As for other variables, only **3** were affected by the optimization: *col*, *row*, and *sum*, which **were originally 3 variables of 4 bytes each but were changed to 1 byte (*col* and *row*) and 2 bytes (*sum*)**. The last one needed to be larger to support a sum of up to 4x255 (since 255 is the largest integer allowed in a PGM P2 file, and our code sums 4 integers at a time).  

❌ **Thus, this was considered an insufficient improvement for evaluation.** ❌  

So, we used the remaining classes to improve the code's **computation time**, but we had little time left and **had already streamlined and improved the code significantly** from Part 1 ([**haar_transform_2d.c**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work1/haar_transform_2d.c)) to Part 2 ([**haar_transform_2d_stm.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/haar_transform_2d_stm.cpp)), making it harder to find significant improvements.  

Since we couldn't find an optimized solution during the classes, we were only able to measure the energy consumption using the [**haar_transform_2d_stm.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/haar_transform_2d_stm.cpp) code.  

#### ⚔️ **WE DID NOT GIVE UP!** ⚔️  
**Code Porting to the PC** 🖥️: Since the classes with the board had ended and we still hadn't found an optimized alternative, we ported the board's code to the PC to find a computation time optimization.    

After a lot of debugging and going through the code, we finally found an inconsistency and an improvement in execution time.  

Code before:  
```c
#include "mbed.h"
#include "stm32f0xx.h"
#include <stdio.h>

#define IMAGE_SIZE 90

Serial pc(SERIAL_TX, SERIAL_RX);

void haarTransform2d(const int input[][IMAGE_SIZE]) {
    int col, row, sum;
    printf("Resultado da Transformada:\n");
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
    static const int input_image[][IMAGE_SIZE] = {
      //matrix
   }
   //...
```
> Partial view of the code [**haar_transform_2d_stm.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/haar_transform_2d_stm.cpp)  

In the condition, there are two ternary operators, and the check for negative numbers is considered unnecessary because, in a PGM P2 file, all numbers are within the closed range [0 - 255]. Therefore, when adding positive numbers and dividing them by another positive number, we will only get positive or zero values. So, we removed this check.  

However, the major improvement is in the division. We initially tried modifying it to `sum = sum * 0.5;`, but there was no change in execution time. Then, we replaced the division with a right shift operation, and the results were surprising:  
```c
//#include "mbed.h"
//#include "stm32f0xx.h"
#include <stdio.h>

#define IMAGE_SIZE 90

//Serial pc(SERIAL_TX, SERIAL_RX);

void haarTransform2d(const int input[][IMAGE_SIZE]) {
    int col, row, sum;
    printf("Resultado da Transformada:\n");
    for(row = 0; row < IMAGE_SIZE - 1; row = row + 2){
        for(col = 0; col < IMAGE_SIZE - 1 ; col = col + 2){
            sum = (input[row][col] + input[row][col+1] + 
               input[row+1][col] + input[row+1][col+1]) >> 1;
            sum = (sum > 255) ? 255 : sum;
            printf("%4d ", sum);
        }
        printf("\n");
    }
}

int main() {
    printf("Haar Transform - mbed OS 2\n");
    static const int input_image[][IMAGE_SIZE] = {
      //matrix
    }
```
> Partial view of the code [**haar_transform_2d_stm_optimized.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work3/original/haar_transform_2d_stm_optimized.cpp)  

---

### 🕒 Time Measurements PC x STM32:
We used the chrono library for time measurement in the algorithm on the PC.

On the STM32, we used the Timer library available in the MBED API.

#### => PC ([**haar_transform_2d_stm_chrono.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work3/benchmarking/chrono_based/haar_transform_2d_stm_chrono.cpp)):
 - Average of 10 tests: 10.65 microseconds;
 - Standard deviation: 0.238 microseconds.

#### => STM32 ([**haar_transform_2d_stm_timer.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work3/benchmarking/timer_mbed_based/haar_transform_2d_stm_timer.cpp)):
 - Average of 10 tests: 93 microseconds;
 - Standard deviation: 0 microseconds.
 
 > NOTE: It is very likely that external interferences, such as communication via terminal to display the results in Keil Studio Cloud, occurred.

### 📊 Time Measurements Before and After Optimization (PC):
We used the chrono library for time measurement in the algorithm on the PC.

#### => Not optimized ([**haar_transform_2d_stm_chrono.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work3/benchmarking/chrono_based/haar_transform_2d_stm_chrono.cpp)):
 - Average of 10 tests: 10.65 microseconds;
 - Standard deviation: 0.238 microseconds.

#### => Optimized ([**haar_transform_2d_stm_optimized_chrono.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work3/benchmarking/chrono_based/haar_transform_2d_stm_optimized_chrono.cpp)):
 - Average of 10 tests: 7.44 microseconds;
 - Standard deviation: 0.475 microseconds

**😎 A SAVINGS OF UP TO 30% IN COMPUTATION TIME!**

Graph of the tests used in the presentation:
![Otimized Vs Not Otimized](images/assets/consumption/timeBoards.png)<br>
*Graph comparing the results of each test from the non-optimized algorithm (in blue) with the optimized algorithm (in orange).*

---
### 📦 Memory Measurements
Since we already made these measurements in Parts 1 and 2, we just transcribed the values below:

#### => PC ([**haar_transform_2d.c**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work1/haar_transform_2d.c)):
Using the SIZE command on Linux
  - text: 4446 bytes
  - data: 688 bytes
  - bss: 16 bytes
  - **Total: 5150 bytes**

#### => STM32 ([**haar_transform_2d_stm.cpp**](https://github.com/Joaosa100/Haar-Transformation/blob/main/work2/haar_transform_2d_stm.cpp)):
The Keil Studio Cloud builder provides the values
  - Flash: 53 Kb
  - Memory: 872 bytes

### ⚡ Energy Measurements
Using the formula to calculate energy:
> E = V * I * t

Knowing that the board's voltage is 3.3V according to the datasheet:

We made the following measurements over a 10-second period:
![current](images/assets/consumption/power_consumption.png)<br>
*Graph with current measurements. There are 10 measurements over 10 seconds.*
Using an average of the values in mA, we get: 62.84 mA or 0.063 A. 

> E = 3.3V * 0.063A * 10s<br>
E = 2 J

**Result:** 2 Joules were consumed by the board in 10 seconds.

<h2 align="center">🌟 ⭐ Enjoyed it? Don't forget to leave a star! ⭐ 🌟</h2>
<p align="center">
    <a href="https://github.com/Joaosa100/Haar-Transformation/stargazers">
        <img src="https://img.shields.io/github/stars/Joaosa100/Haar-Transformation?style=social" alt="GitHub Stars"/>
    </a>
</p>

## 👥 Development Team
Members who participated in the development of this project:

| [![GitHub User 1](https://github.com/Joaosa100.png?size=420)](https://github.com/Joaosa100) | [![GitHub User 2](https://github.com/AugustaSousa.png?size=420)](https://github.com/AugustaSousa) |
|:-----------------------------------------------:|:-----------------------------------------------:|
| [**João Vitor**](https://github.com/Joaosa100)   <br><br> <a href="https://www.linkedin.com/in/joao-silva-assuncao" target="_blank" style="text-decoration:none;"><button style="padding: 10px 20px; font-size: 16px; margin-top: 10px; background-color: #0077B5; color: white; border: none; border-radius: 5px; cursor: pointer;">LinkedIn</button></a> | [**AugustaSousa**](https://github.com/AugustaSousa)   <br><br> <a href="https://linkedin.com/in/augusta-sousa" target="_blank" style="text-decoration:none;"><button style="padding: 10px 20px; font-size: 16px; margin-top: 10px; background-color: #0077B5; color: white; border: none; border-radius: 5px; cursor: pointer;">LinkedIn</button></a> |

