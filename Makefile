#**************************************************************
#          Pontificia Universidad Javeriana
#     Autor: Santiago Pineda Mora
#     Fecha: 15/08/25
#     Materia: Introducción Distribuidos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: Makefile para compilar programas de multiplicación de matrices
#**************************************************************

# Compilador a usar
GCC = gcc

# Flags generales de compilación
CFLAGS = -lm             # -lm enlaza la librería matemática (math.h)
FOPENMP = -fopenmp -O3   # -fopenmp habilita OpenMP, -O3 aplica optimización agresiva
POSIX = -lpthread        # -lpthread enlaza la librería de hilos POSIX (si se requiere)

# Archivo fuente adicional (aunque aquí no se usa explícitamente)
modulo = inter.c

# Lista de programas que se van a compilar
PROGRAMAS = mmClasicaOpenMP 

# Regla principal: compilar todos los programas
ALL: $(PROGRAMAS)

# Regla para compilar el ejecutable mmClasicaOpenMP
# Toma el archivo mmClasicaOpenMP.c y lo compila
mmClasicaOpenMP:
	$(GCC) $(CFLAGS) $@.c -o $@ $(FOPENMP)

# Regla de limpieza: elimina los ejecutables generados
clean:
	$(RM) $(PROGRAMAS)
