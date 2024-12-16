import matplotlib.pyplot as plt

nome_arquivo = "images/pgm_output/animal3.pgm"

with open(nome_arquivo, 'r') as arquivo:

    arquivo.readline()  
    largura, altura = map(int, arquivo.readline().split())
    max_valor = int(arquivo.readline())
    
    pixels = []
    for linha in arquivo:
        pixels.extend(map(int, linha.split()))
        
    imagem = [pixels[i * largura:(i + 1) * largura] for i in range(altura)]


plt.imshow(imagem, cmap='gray', vmin=0, vmax=max_valor)
plt.title("Imagem PGM P2")
plt.axis('off') 
plt.show()
