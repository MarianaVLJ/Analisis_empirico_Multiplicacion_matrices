import csv
import matplotlib.pyplot as plt

n = []
tiempo_std = []
tiempo_strassen = []

with open("resultados.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        n.append(int(row["n"]))
        tiempo_std.append(float(row["mediana_std"]))
        tiempo_strassen.append(float(row["mediana_strassen"]))

plt.plot(n, tiempo_std, marker="o", label="Estándar")
plt.plot(n, tiempo_strassen, marker="o", label="Strassen")
plt.axvline(x=112, color="red", linestyle="--", label="N₀ ≈ 112")
plt.xlabel("Tamaño de matriz (n)")
plt.ylabel("Tiempo (segundos)")
plt.title("Comparación de tiempos: Estándar vs Strassen")
plt.legend()
plt.grid(True)
plt.savefig("grafica.png")
print("Grafica guardada en grafica.png")
