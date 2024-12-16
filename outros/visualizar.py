import cv2
import matplotlib.pyplot as plt

nome = "pessoa4"

imagem_pgm = cv2.imread("images/pgm/"+nome+".pgm")
imagem_pgmOut = cv2.imread("images/pgm_output/"+nome+".pgm")
imagem_pgmpywt = cv2.imread("images/pgm_output/"+nome+"_pywt.pgm")

fig, axes = plt.subplots(1, 3, figsize=(12, 6))

axes[0].imshow(imagem_pgm, cmap='gray')
axes[0].set_title('Imagem PGM')
axes[0].axis('off')

axes[1].imshow(imagem_pgmOut, cmap='gray')
axes[1].set_title('Output Haar PGM')
axes[1].axis('off')

axes[2].imshow(imagem_pgmpywt, cmap='gray')
axes[2].set_title('Output Haar PGM pela Pywavelets')
axes[2].axis('off')

plt.show()