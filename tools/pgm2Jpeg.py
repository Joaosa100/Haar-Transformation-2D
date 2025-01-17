from PIL import Image

def pgm2jpeg(input_file, output_file):
    with open(input_file, 'r') as f:
        # Ler o cabeçalho PGM
        magic_number = f.readline().strip()  # Primeiro valor (deve ser 'P2')
        if magic_number != 'P2':
            raise ValueError("Arquivo PGM inválido ou não suportado!")
        
        # Ignorar comentários (linhas começando com '#')
        dimensions = f.readline().strip()
        while dimensions.startswith('#'):
            dimensions = f.readline().strip()
        
        largura, altura = map(int, dimensions.split())
        max_value = int(f.readline().strip())  # Valor máximo (normalmente 255)
        
        # Ler os pixels
        pixels = []
        for line in f:
            pixels.extend(map(int, line.split()))
    
    # Criar uma imagem com base nos dados lidos
    image = Image.new('L', (largura, altura))
    image.putdata(pixels)
    
    # Salvar como JPEG
    image.save(output_file, 'JPEG')

# Exemplo de uso
nome = 'animal4'
pgm2jpeg("images/pgm_output_placa/" + nome + ".pgm", "images/pgm_output_placa/" + nome + ".jpeg")
