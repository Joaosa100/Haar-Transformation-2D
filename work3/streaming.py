import serial
import time
import threading

def send_array_to_serial(port, baudrate, data_array, output_file):
    def send_data(ser, data_array):
        for number in data_array:
            ser.write((str(number) + '\n').encode())
            print(f"Enviado: {number}")
            time.sleep(0.01)  # Delay para estabilidade
        ser.write(b'END\n')
        print("Comando 'END' enviado. Todos os dados foram transmitidos.")

    def receive_data(ser, response_lines):
        timeout_counter = 0
        while timeout_counter < 2000:
            if ser.in_waiting > 0:
                response = ser.readline().decode('utf-8', errors='replace').strip()
                if response:
                    response_lines.append(response)
                    print(f"Recebido: {response}")
                timeout_counter = 0  # Reinicia contador ao receber dados
            else:
                time.sleep(0.01)
                timeout_counter += 1

    try:
        with serial.Serial(port, baudrate, timeout=1) as ser:
            print(f"Conectado à porta {port} com baudrate {baudrate}.")

            response_lines = []

            # Threads para envio e recepção
            send_thread = threading.Thread(target=send_data, args=(ser, data_array))
            receive_thread = threading.Thread(target=receive_data, args=(ser, response_lines))

            # Inicia as threads
            send_thread.start()
            receive_thread.start()

            # Aguarda as threads terminarem
            send_thread.join()
            receive_thread.join()

            # Salva todas as mensagens no arquivo de saída
            print("Salvando as respostas no arquivo de saída...")
            with open(output_file, 'w', encoding='utf-8') as outfile:
                outfile.write("\n".join(response_lines) + "\n")
            print(f"Respostas salvas no arquivo: {output_file}")

    except serial.SerialException as e:
        print(f"Erro ao conectar à porta serial: {e}")

def ler_arquivo_para_array(caminho_arquivo):
    try:
        with open(caminho_arquivo, 'r') as arquivo:
            array = [int(linha.strip()) for linha in arquivo if linha.strip().isdigit()]
            print(f"Lido {len(array)} elementos do arquivo {caminho_arquivo}.")
            return array
    except FileNotFoundError:
        print(f"Arquivo não encontrado: {caminho_arquivo}")
        return []
    except Exception as e:
        print(f"Ocorreu um erro ao ler o arquivo {caminho_arquivo}: {e}")
        return []

if __name__ == "__main__":
    SERIAL_PORT = 'COM6'
    BAUDRATE = 9600
    OUTPUT_FILE = 'output_random.txt'
    INPUT_FILE = 'input_random.txt'

    print("Iniciando o processo de envio e recepção serial...")

    data_array = ler_arquivo_para_array(INPUT_FILE)
    print("Array a ser enviado:", data_array[:10], "...", data_array[-10:])

    send_array_to_serial(SERIAL_PORT, BAUDRATE, data_array, OUTPUT_FILE)

    print("Processo concluído. Verifique o arquivo de saída.")