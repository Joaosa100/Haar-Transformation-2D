from PIL import Image

def jpeg_to_pgm(input_file, output_file):
    image = Image.open(input_file).convert('L')  
    
    width, height = image.size
    
    with open(output_file, 'w') as f:
        f.write('P2\n')
        f.write(f'{width} {height}\n')
        f.write('255\n')
        
        pixels = list(image.getdata())
        for i in range(height):
            line = pixels[i * width:(i + 1) * width]
            line_str = ' '.join(map(str, line))
            f.write(f'{line_str}\n')

nome = 'animal3'

jpeg_to_pgm("images/rgb/" + nome + ".jpeg", "images/pgm/" + nome + ".pgm")
