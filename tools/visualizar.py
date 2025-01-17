import cv2
import matplotlib.pyplot as plt

nome = "animal4"

imagem_pgmOut = cv2.imread("images/pgm_compressão/"+nome+"_pywt.pgm")
imagem_pgmpywt = cv2.imread("images/pgm_output_placa/"+nome+".pgm")

fig, axes = plt.subplots(1, 2, figsize=(12, 6))

axes[0].imshow(imagem_pgmOut, cmap='gray')
axes[0].set_title('Output Haar PGM')
axes[0].axis('off')

axes[1].imshow(imagem_pgmpywt, cmap='gray')
axes[1].set_title('Output Haar PGM pela Pywavelets')
axes[1].axis('off')

plt.show()