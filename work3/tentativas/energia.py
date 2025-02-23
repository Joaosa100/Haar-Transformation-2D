import matplotlib.pyplot as plt
import numpy as np

# Dados de consumo de energia
indices = [1,2,3,4,5,6,7,8,9,10]  # 10 medições
media = [62.6, 62.8, 62.5, 62.4, 63.1, 62.9, 63.0, 62.9, 62.8, 63.7]
rms = [62.6, 62.8, 62.5, 62.5, 63.1, 62.9, 63.1, 62.9, 62.8, 63.7]
maximo = [65.6, 66.4, 66.4, 65.6, 72.8, 67.2, 66.4, 66.4, 69.6, 72.0]
mediaUints = [64.5, 64.7, 65.4, 64.2, 63.3, 63.7, 63.4, 64.5, 63.5, 63.4]

plt.style.use('seaborn-v0_8-dark')
plt.figure(figsize=(12, 5))
#plt.plot(indices, rms, marker='s', label='RMS')
plt.plot(indices, media, marker='o', label='Consumo Int')
plt.plot(indices, mediaUints, marker='^', label='Consumo Uint')

def add_labels(x, y):
    for i, j in zip(x, y):
        plt.text(i, j, f"{j:.1f}", ha='right', va='bottom', fontsize=16)

add_labels(indices, media)
#add_labels(indices, rms)
add_labels(indices, mediaUints)

plt.xlabel("Tempo (s)", fontsize = 16)
plt.ylabel("Consumo de Energia (mA)", fontsize = 16)
plt.title("Consumo de Energia da STM32", fontsize=16)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('consumoPlacas.png', bbox_inches='tight')
plt.show()