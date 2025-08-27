
# Proyecto: Evaluación de Rendimiento de Multiplicación de Matrices con OpenMP

## 📌 Descripción
Este proyecto corresponde a un taller de **Introducción a Sistemas Distribuidos** en el que se desarrolla, automatiza y analiza el rendimiento de la **multiplicación de matrices cuadradas (MM)** usando **paralelismo con OpenMP** y comparación de tiempos de ejecución con distintos tamaños de matrices y diferentes números de hilos.

El objetivo principal es estudiar cómo varía el rendimiento del algoritmo de multiplicación clásica de matrices al aplicar técnicas de paralelización, evaluando la escalabilidad del sistema.

---

## 📂 Estructura del Proyecto

```

├── mmClasicaOpenMP.c       # Código fuente en C con OpenMP para multiplicación de matrices
├── Makefile                # Script de compilación para automatizar la construcción del ejecutable
├── ejecutar\_lotes.pl       # Script en Perl para ejecutar múltiples pruebas por lotes
├── resultados/             # Carpeta sugerida para almacenar los archivos .dat generados
└── README.md               # Documentación del proyecto

````

---

## ⚙️ Dependencias

Para ejecutar el proyecto se requiere tener instalados los siguientes componentes:

- **GCC** con soporte para OpenMP  
- **Perl** para la automatización de pruebas  
- **Linux o WSL (Windows Subsystem for Linux)**  

Verifica si tienes instalado GCC con OpenMP:
```bash
gcc --version
````

---

## 🏗️ Compilación

El proyecto se compila mediante el **Makefile**.
Ejecuta en la terminal:

```bash
make
```

Esto generará el ejecutable:

```
mmClasicaOpenMP
```

En caso de querer limpiar los ejecutables generados:

```bash
make clean
```

---

## ▶️ Ejecución

### Ejecución manual

Puedes ejecutar el programa de la siguiente forma:

```bash
./mmClasicaOpenMP <TamañoMatriz> <NúmeroHilos>
```

Ejemplo:

```bash
./mmClasicaOpenMP 4080 4
```

---

### Ejecución automatizada

El script `ejecutar_lotes.pl` se encarga de correr el programa múltiples veces con diferentes tamaños de matriz y distintos números de hilos.

Configura dentro del script:

* **@Size\_Matriz** → tamaños de matrices a probar
* **@Num\_Hilos** → número de hilos a utilizar
* **\$Repeticiones** → cantidad de repeticiones por combinación

Para ejecutar el script:

```bash
perl ejecutar_lotes.pl
```

Los resultados se guardarán en archivos `.dat` con la siguiente nomenclatura:

```
mmClasicaOpenMP-<Tamaño>-Hilos-<N>.dat
```

Ejemplo:

```
mmClasicaOpenMP-4080-Hilos-4.dat
```

---

## 📊 Resultados esperados

* Cada archivo `.dat` contendrá los tiempos de ejecución de la multiplicación para un tamaño de matriz y número de hilos específico.
* Con estos datos, se pueden graficar curvas de rendimiento y analizar la eficiencia paralela del algoritmo.

---

## ✨ Autor

* **Nombre:** Santiago Pineda Mora
* **Universidad:** Pontificia Universidad Javeriana
* **Materia:** Introducción a Sistemas Distribuidos
* **Fecha:** 15/08/2025

---

```

```
