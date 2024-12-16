import matplotlib.pyplot as plt
from PIL import Image

nome = "animal3"

imagem_jpeg = Image.open("images/rgb/"+nome+".jpeg")
imagem_pgm = Image.open("images/pgm/"+nome+".pgm")
imagem_pgmOut = Image.open("images/pgm_output/"+nome+".pgm")

fig, axes = plt.subplots(1, 3, figsize=(12, 6))

axes[0].imshow(imagem_jpeg, cmap='gray')
axes[0].set_title('Imagem JPEG')
axes[0].axis('off')

axes[1].imshow(imagem_pgm, cmap='gray')
axes[1].set_title('Imagem PGM')
axes[1].axis('off')

axes[2].imshow(imagem_pgmOut, cmap='gray')
axes[2].set_title('Output PGM')
axes[2].axis('off')

plt.show()