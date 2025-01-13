import numpy as np

def lerPGM(file_path):
    with open(file_path, 'r') as f:
        header = f.readline().strip()
        
        while True:
            line = f.readline().strip()
            if line[0] != '#':
                break
        
        dimensions = line.split()
        width, height = int(dimensions[0]), int(dimensions[1])
        
        max_val = int(f.readline().strip())
        
        pixels = []
        for line in f:
            pixels.extend(map(int, line.split()))
        
        img = np.array(pixels, dtype=np.uint8).reshape((height, width))
        return img

def salvarPGM(matrix, file_path):
    with open(file_path, 'w') as f:
        f.write('P2\n')
        f.write(f'{matrix.shape[1]} {matrix.shape[0]}\n')
        f.write('255\n')
        for row in matrix:
            row_str = ' '.join(map(str, row))
            f.write(f'{row_str}\n')

def extract_45x45(img):
    return img[:45, :45]


nome = 'animal4'
pgm_file = 'images/pgm_output/' + nome + '_pywt.pgm'
output_file = 'images/pgm_compressao/' + nome + '_pywt.pgm'

imagem = lerPGM(pgm_file)
imagem_45x45 = extract_45x45(imagem)
salvarPGM(imagem_45x45, output_file)