import serial
import time
import numpy as np

def ler_pgm(arquivo):
    with open(arquivo, 'r') as f:
        linhas = f.readlines()
    
    assert linhas[0].strip() == 'P2', "O arquivo não está no formato PGM P2"
    
    i = 1
    while linhas[i].startswith("#"):  # Ignora comentários
        i += 1

    width, height = map(int, linhas[i].split())  # Dimensões da imagem
    i += 1
    max_val = int(linhas[i])  # Valor máximo (geralmente 255)
    i += 1
    
    dados = [int(valor) for linha in linhas[i:] for valor in linha.split()]
    matriz = np.array(dados).reshape((height, width))

    return matriz, width, height, max_val

def salvar_pgm(matriz, arquivo, max_val=255):
    height, width = matriz.shape
    with open(arquivo, 'w') as f:
        f.write("P2\n")
        f.write(f"{width} {height}\n")
        f.write(f"{max_val}\n")
        for linha in matriz:
            f.write(" ".join(map(str, linha)) + "\n")

def enviar_receber_serial(port, baudrate, matriz, output_file):
    try:
        with serial.Serial(port, baudrate, timeout=1) as ser:
            print(f"Conectado à porta {port}.")

            height, width = matriz.shape
            recebidos = []

            # Enviar os blocos 2x2
            for row in range(0, height - 1, 2):
                for col in range(0, width - 1, 2):
                    bloco = [
                        matriz[row, col], matriz[row, col+1],
                        matriz[row+1, col], matriz[row+1, col+1]
                    ]
                    for valor in bloco:
                        ser.write((str(valor) + '\n').encode())
                        time.sleep(0.01)  # Pequeno delay para estabilidade ele botou 0.002, botei 0.01

            ser.write(b'END\n')
            print("Dados enviados.")

            # Receber os dados processados
            while True:
                resposta = ser.readline().decode().strip()
                if resposta == "Processamento concluído.":
                    break
                elif resposta.isdigit():
                    recebidos.append(int(resposta))

            if not recebidos:
                print("Nenhum dado recebido.")
                return

            # O tamanho da nova matriz é (height/2, width/2)
            new_height = height // 2
            new_width = width // 2
            matriz_resultante = np.array(recebidos).reshape((new_height, new_width))

            # Salvar no arquivo PGM
            salvar_pgm(matriz_resultante, output_file)
            print(f"Imagem processada salva em {output_file}")

    except serial.SerialException as e:
        print(f"Erro na comunicação serial: {e}")

if __name__ == "__main__":
    SERIAL_PORT = "COM6"  # Modifique conforme necessário
    BAUDRATE = 9600
    INPUT_FILE = "images/pgm/animal3.pgm"
    OUTPUT_FILE = "images/pgm_output/animal3Stream.pgm"

    print("Lendo arquivo PGM...")
    matriz, width, height, max_val = ler_pgm(INPUT_FILE)

    print(f"Enviando matriz {width}x{height} via Serial...")
    enviar_receber_serial(SERIAL_PORT, BAUDRATE, matriz, OUTPUT_FILE)

    print("Processo concluído.")
