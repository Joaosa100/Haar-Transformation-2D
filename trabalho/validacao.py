import numpy as np

def lerPGM(path):
    with open(path, 'r') as f:
        # cabeçalho do PGM P2
        cabecalho = f.readline().strip()
        
        while True: 
            linha = f.readline().strip() 
            if linha[0] != '#': 
                break
            
        # dimensões da imagem
        dimensao = linha.split()
        largura, altura = int(dimensao[0]), int(dimensao[1])
        
        # Ler o valor máximo do pixel
        valor_max = int(f.readline().strip())
        
        # Ler os valores dos pixels
        pixels = []
        for linha in f:
            pixels.extend(map(int, linha.split()))
        
        # Converter a lista de pixels em uma matriz NumPy
        img = np.array(pixels, dtype=np.uint8).reshape((altura, largura))
        return img

def compararPGMs(path1, path2, tolerancia, path):
    img1 = lerPGM(path1)
    img2 = lerPGM(path2)
    
    diferencas = img1 - img2
    
    with open(path, 'w') as f: 
        for linha in diferencas: 
            linha_ = ' '.join(map(str, linha)) 
            f.write(f'{linha_}\n')
    
    margem = np.abs(diferencas) <= tolerancia
    quantidade_dif = np.count_nonzero(~margem)
    
    print(f"Quantidade de pixels diferentes: {quantidade_dif} \nCom margem de erro de {tolerancia}")
    
    return diferencas


nome = 'pessoa4'

img1 = 'images/pgm_output/' + nome + '.pgm'
img2 = 'images/pgm_output/' + nome + '_pywt.pgm'
pgm_comparacao = 'images/pgm_comparacao/' + nome + '.pgm'

diferencas = compararPGMs(img1, img2, 1, pgm_comparacao)

# mapa de calor de erros
if isinstance(diferencas, np.ndarray):
    import matplotlib.pyplot as plt
    plt.imshow(diferencas, cmap='hot', interpolation='nearest')
    plt.title('Diferenças entre Imagens')
    plt.colorbar()
    plt.show()
