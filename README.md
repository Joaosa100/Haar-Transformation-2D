# Haar-Transformation 2D
Usando a Transformada 2D de Haar para comprimir imagens PGM P2

## 📖 O que você verá aqui?
Este projeto desenvolvido durante a cadeira de Sistemas Embarcados foi dividido em 2 partes:
1. Projetar o algoritmo de forma correta, indicando entrada/saída de dados, complexidades e construir e definir os testes para que tudo seja executado em um PC.
2. Transportar o algoritmo para um sistema embarcado fazendo as devidas alterações e gestão de memória.

## Parte 1: Algoritmo no Ambiente PC
### 🎯 Objetivo
Desenvolver o algoritmo para aplicar a Transformada 2D de Haar em imagens no formato PGM P2. O foco está na correta definição das entradas e saídas de dados, análise de complexidade computacional e criação de testes automatizados para garantir a correta funcionalidade.

### 🛠 Tecnologias Utilizadas
- Linguagem de programação: C, Python
- Ferramentas de teste: Transformada de Haar usando a biblioteca Pywavelets

### 🌐 Ambiente de Desenvolvimento
- Sistema Operacional: PopOS 22.04 LTS e Windows 10
- IDE/Editor: VSCode
- Compilador/Interprete: GCC e Python 3.8+

### 🚧 Desenvolvimento
1. **Entrada de Dados:**
   - Imagens quadradas no formato PGM P2 com proporção 90x90.
2. **Saída de Dados:**
   - Imagem comprimida para proporção 45x45 utilizando a Transformada 2D de Haar.
3. **Implementação do algoritmo base:**
   - O algoritmo implementado pode ser visualizado no arquivo "haar_tranformation.c".
   - Foram utilizadas as bibliotecas <stdio.h>, <stdlib.h>, <string.h> e <math.h>.
4. **Complexidades:**
   - **Pior caso**: O(NxM), sendo N o número de linhas e M o número de colunas.
   - **Melhor caso**: O(NxM), sendo N o número de linhas e M o número de colunas, requer percorrer todos os elementos da imagem.
5. **Primeiros Testes unitários para validar as transformações:**
   - Nos testes realizados tivemos os seguintes resultados comparando as saídas dos algoritmos `haar_transformation.c` e `haarWavelet.py`:

   | **Imagem Original** | **Resultado C** | **Resultado Python** |
   |----------------------|------------------|----------------------|
   | ![Imagem Original](images/assets/animal3Source.jpeg) <br> `Animal_Source.pgm` | ![Haar Transformation - C](images/assets/firstAlgorithmTest/animal390.jpeg) <br> `Haar_C_result.pgm` | ![Haar Wavelet - Python](images/assets/firstAlgorithmTest/animal390_pywt.jpeg) <br> `Haar_Pywavelet_Result.pgm` |

   - Usando o algoritmo para comparar cada pixel dos resultados:<br>
      ![Validacao - py](images/assets/firstAlgorithmTest/comp90er.png)

      **Legenda:** Diferenças entre os resultados obtidos no algoritmo implementado em C e Python (Pywavelets). Cada ponto branco representa a divergência identificada na transformação de Haar. Houve uma diferença em 892 pixels no total de 8100 (90x90), totalizando 11.01% de erro utilizando uma tolerância de diferença zero.

   - Agora, descartando as outras regiões da imagem e utilizando o resultado comprimido (45x45):
   
   | **Imagem Original** | **Resultado C** | **Resultado Python** |
   |----------------------|------------------|----------------------|
   | ![Imagem Original](images/assets/animal3Source.jpeg) <br> `Animal_Source.pgm` | ![Haar Transformation - C](images/assets/firstAlgorithmTest/animal345.jpeg) <br> `Haar_C_result.pgm` | ![Haar Wavelet - Python](images/assets/firstAlgorithmTest/animal345_pywt.jpeg) <br> `Haar_Pywavelet_Result.pgm` |

   - Usando o algoritmo para comparar cada pixel dos resultados:<br>
      ![Validacao - py](images/assets/firstAlgorithmTest/comp45er.png)

      **Legenda:** Diferenças entre os resultados obtidos no algoritmo implementado em C e Python (Pywavelets) utlizando apenas a parte comprimida. Cada ponto branco representa a divergência identificada na transformação de Haar. Houve uma diferença em 87 pixels no total de 2025 (45x45), totalizando 4.3% de erro utilizando uma tolerância de diferença zero.

6. **Melhorando o algoritmo:**
   - Mesmo com uma leve diferença, era necessário atingir 100% de semelhança com a saída da Pywavelets, então modificamos o algoritmo.
   - Retiramos a biblioteca <math.h>:
   ```c
      // Antes a função Haar2D chamava de forma iterativa a Haar1D:
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

      // Agora sem <math.h> e todo o cálculo permanece apenas na função Haar2D:
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
   - Assim, os resultados foram:

   | **Imagem Original** | **Resultado C** | **Resultado Python** |
   |----------------------|------------------|----------------------|
   | ![Imagem Original](images/assets/animal3Source.jpeg) <br> `Animal_Source.pgm` | ![Haar Transformation - C](images/assets/improvedAlgorithmTest/animal3Imp.jpeg) <br> `Haar_C_result.pgm` | ![Haar Wavelet - Python](images/assets/firstAlgorithmTest/animal345_pywt.jpeg) <br> `Haar_Pywavelet_Result.pgm` |

   - Usando o algoritmo para comparar cada pixel dos resultados:<br>
      ![Validacao - py](images/assets/improvedAlgorithmTest/comp45LL.png)

      **Legenda:** Diferenças entre os resultados obtidos no algoritmo implementado em C e Python (Pywavelets) utlizando apenas a parte comprimida. Cada ponto branco representa a divergência identificada na transformação de Haar. Houve uma diferença em 0 pixels no total de 2025 (45x45), totalizando 0.0% de erro utilizando uma tolerância de diferença zero.
7. **Medição de consumo de RAM (a terminar)**
   - Compile o código para gerar o executável da mesma maneira que fizemos para os testes:<br>
   ```bash
   gcc -o myExec haar_transform.c -lm
   ``` 
   - Para saber quanto de memória ram é necessária para rodar o código, usamos a seguinte linha de terminal no sistema Linux:<br>
   ```bash
   size <myExec>
   ```
   - Saída gerada:<br>
     ![ram](images/assets/improvedAlgorithmTest/ramCons.png)

   -  Como pode ver, apenas esses dois consomem RAM:
      -  **data**: Segmento de dados inicializados. Este segmento armazena variáveis globais e estáticas que possuem valores atribuídos explicitamente no código.
      -  **bss**: Segmento de dados não inicializados. Este segmento armazena variáveis globais e estáticas que são declaradas, mas não possuem valores iniciais definidos (ou são inicializadas implicitamente como zero).
      -  Este código precisa de 704 bytes de RAM para ser executado.

---

## 👥 Colaboradores

Membros que participaram do desenvolvimento deste projeto:

| [![GitHub User 1](https://github.com/Joaosa100.png?size=420)](https://github.com/Joaosa100) | [![GitHub User 2](https://github.com/AugustaSousa.png?size=420)](https://github.com/AugustaSousa) |
|:-----------------------------------------------:|:-----------------------------------------------:|
| [**Joaosa100**](https://github.com/Joaosa100)   <br><br> <a href="https://www.linkedin.com/in/joao-silva-assuncao" target="_blank" style="text-decoration:none;"><button style="padding: 10px 20px; font-size: 16px; margin-top: 10px; background-color: #0077B5; color: white; border: none; border-radius: 5px; cursor: pointer;">LinkedIn</button></a> | [**AugustaSousa**](https://github.com/AugustaSousa)   <br><br> <a href="https://linkedin.com/in/augusta-sousa" target="_blank" style="text-decoration:none;"><button style="padding: 10px 20px; font-size: 16px; margin-top: 10px; background-color: #0077B5; color: white; border: none; border-radius: 5px; cursor: pointer;">LinkedIn</button></a> |




