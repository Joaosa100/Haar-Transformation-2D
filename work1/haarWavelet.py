import cv2
import pywt  # Biblioteca PyWavelets
import numpy as np
import matplotlib.pyplot as plt

nomeImg = "animal4"

imagem_input = 'images/pgm/' + nomeImg + '.pgm'
imagem_output = 'images/pgm_output/' + nomeImg + '_pywt.pgm'

# carregar imagem
img = cv2.imread(imagem_input, cv2.IMREAD_GRAYSCALE)

# Transformada 2D Discreta de Wavelet
coeffs2 = pywt.dwt2(img, 'haar')
# Low Low, Low High(vertical), High Low (horizontal), High High(diagonal)
LL, (LH, HL, HH) = coeffs2 
haar_img = np.vstack((np.hstack((LL, HL)), np.hstack((LH, HH))))

#haar_img[haar_img < 0] = 0
haar_img = np.clip(haar_img, 0, 255) # garantir valores entre 0 e 255
haar_img = np.floor(haar_img).astype(int)

# salvar imagem
with open(imagem_output, 'w') as f:
    # Cabeçalho do arquivo PGM P2
    f.write('P2\n')
    f.write(f'{haar_img.shape[1]} {haar_img.shape[0]}\n')
    f.write('255\n')
        
    for row in haar_img:
        row_str = ' '.join(map(str, row))
        f.write(f'{row_str}\n')

#fig, axes = plt.subplots(1, 2, figsize=(12, 6))
#axes[0].imshow(img, cmap='gray')
#axes[0].set_title('Imagem Original PGM')
#axes[0].axis('off')

#axes[1].imshow(haar_img, cmap='gray')
#axes[1].set_title('Imagem Transformada Haar Wavelet')
#axes[1].axis('off')

#plt.show()