from PIL import Image

def jpeg2Pgm(input_file, output_file):
    image = Image.open(input_file).convert('L')  
    
    largura, altura = image.size
    
    with open(output_file, 'w') as f:
        f.write('P2\n')
        f.write(f'{largura} {altura}\n')
        f.write('255\n')
        
        pixels = list(image.getdata())
        for i in range(altura):
            line = pixels[i * largura:(i + 1) * largura]
            line_str = ' '.join(map(str, line))
            f.write(f'{line_str}\n')

nome = 'pessoa4'

jpeg2Pgm("images/rgb/" + nome + ".jpeg", "images/pgm/" + nome + ".pgm")
