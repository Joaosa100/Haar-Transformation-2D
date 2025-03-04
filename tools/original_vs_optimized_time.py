import matplotlib.pyplot as plt
import numpy as np

labels = ["1", " 2", "3", "4", "5", "6", "7", "8", "9", "10"]
primeriaVersao = [10.5,10.4,11.0,10.4,10.4,10.9,10.8,10.9,10.4,10.8]
segundaVersao = [7.1, 7.2, 8.4,7.3,8.2,7.2,6.9,7.0,7.5,7.6]

x = np.arange(len(labels))

plt.figure(figsize=(12, 5))
plt.plot(labels, primeriaVersao, marker='o', label='Before')
plt.plot(labels, segundaVersao, marker='s', label='After')

def add_labels(x, y):
    for i, j in zip(x, y):
        plt.text(i, j, f"{j:.1f}", ha='right', va='bottom', fontsize=16) 

add_labels(labels, primeriaVersao)
add_labels(labels, segundaVersao)

plt.xlabel('Tests', fontsize=16)  
plt.ylabel('Time (us)', fontsize=16)

plt.legend()
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)

plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('../images/assets/consumption/timeBoards.png', bbox_inches='tight')
plt.show()