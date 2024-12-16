import pywt
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

def load_pgm_image(file_path):
    image = Image.open(file_path).convert('L')
    return np.array(image)

def save_pgm_image(matrix, file_path):
    with open(file_path, 'w') as f:
        f.write('P2\n')
        f.write(f'{matrix.shape[1]} {matrix.shape[0]}\n')
        f.write('255\n')
        
        for row in matrix:
            row_str = ' '.join(map(str, row))
            f.write(f'{row_str}\n')

def haar_transform_2d(image_matrix):
    coeffs2 = pywt.dwt2(image_matrix, 'haar')
    cA, (cH, cV, cD) = coeffs2
    return cA, cH, cV, cD

def main(pgm_input_path, pgm_output_path):
    image_matrix = load_pgm_image(pgm_input_path)
    cA, cH, cV, cD = haar_transform_2d(image_matrix)
    haar_matrix = np.vstack((np.hstack((cA, cH)), np.hstack((cV, cD))))
    save_pgm_image(haar_matrix, pgm_output_path)

    fig, axes = plt.subplots(1, 2, figsize=(12, 6))
    axes[0].imshow(image_matrix, cmap='gray')
    axes[0].set_title('Imagem Original PGM')
    axes[0].axis('off')

    axes[1].imshow(haar_matrix, cmap='gray')
    axes[1].set_title('Imagem Transformada Haar Wavelet')
    axes[1].axis('off')

    plt.show()

nome = "animal3"
pgm_input_path = 'images/pgm/'+nome+'.pgm'
pgm_output_path = 'images/pgm_output/'+nome+'_pywt.pgm'
main(pgm_input_path, pgm_output_path)
