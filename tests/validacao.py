import numpy as np
import matplotlib.pyplot as plt

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
        return img, largura, altura

def compararPGMs(path1, path2, tolerancia, path):
    img1, largura, altura = lerPGM(path1)
    img2, _, _ = lerPGM(path2)
    
    diferencas = img1 - img2
    
    with open(path, 'w') as f: 
        for linha in diferencas: 
            linha_ = ' '.join(map(str, linha)) 
            f.write(f'{linha_}\n')
    
    margem = np.abs(diferencas) <= tolerancia
    quantidade_dif = np.count_nonzero(~margem)
    total_pixels = largura * altura
    porcentagem = (quantidade_dif / total_pixels) * 100
    
    print(f"Quantidade de pixels diferentes: {quantidade_dif} ({porcentagem:.2f}%)\nCom margem de erro de {tolerancia}")
    
    return diferencas, quantidade_dif, porcentagem

nome = 'animal3'

img1 = 'images/pgm_output_placa/' + nome + '.pgm'
img2 = 'images/pgm_compressao/' + nome + '_pywt.pgm'
pgm_comparacao = 'images/pgm_comparacao/' + nome + '.pgm'

tolerancia = 0
diferencas, quantidade_dif, porcentagem = compararPGMs(img1, img2, tolerancia, pgm_comparacao)

# mapa de calor de erros
if isinstance(diferencas, np.ndarray):
    plt.figure(figsize=(10, 7.5))
    plt.imshow(diferencas, cmap='hot', interpolation='nearest')
    plt.title('Diferenças entre Imagens', fontsize=16)
    plt.colorbar()
    
    # Adicionar a linha de informação como texto no gráfico
    info_text = (
        f"Quantidade de pixels diferentes: {quantidade_dif} ({porcentagem:.2f}%)\n"
        f"Com margem de erro de {tolerancia}"
    )
    plt.gcf().text(0.5, 0.01, info_text, fontsize=16, ha='center', va='bottom')
    
    # Salvar e/ou exibir a imagem
    plt.savefig('diferencas_com_info.png', bbox_inches='tight')
    plt.show()