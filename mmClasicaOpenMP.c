/*#######################################################################################
 # Fecha: 15/08/25 
 # Autor: Santiago Pineda Mora 
 # Tema:  
 #   - Programa de Multiplicación de Matrices con algoritmo clásico
 #   - Paralelismo implementado con OpenMP
#######################################################################################*/

#include <stdio.h>      // Funciones de entrada/salida (printf, etc.)
#include <stdlib.h>     // Funciones generales (malloc, calloc, rand, atoi, etc.)
#include <string.h>     // Manejo de cadenas (aunque en este programa no se usa)
#include <time.h>       // Para inicializar la semilla de números aleatorios
#include <sys/time.h>   // Para medir tiempos de ejecución con gettimeofday
#include <omp.h>        // Librería OpenMP para paralelismo

// Variables globales para almacenar tiempo de inicio y fin
struct timeval inicio, fin; 

/*--------------------------------------------------------------------------------------
 * Función: InicioMuestra
 * Objetivo: Guardar el tiempo actual como tiempo de inicio
 *-------------------------------------------------------------------------------------*/
void InicioMuestra(){
    gettimeofday(&inicio, (void *)0);
}

/*--------------------------------------------------------------------------------------
 * Función: FinMuestra
 * Objetivo: Guardar el tiempo actual como tiempo de fin, calcular la diferencia 
 *           y mostrar el tiempo de ejecución en microsegundos.
 *-------------------------------------------------------------------------------------*/
void FinMuestra(){
    gettimeofday(&fin, (void *)0);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec); 
    printf("%9.0f \n", tiempo);
}

/*--------------------------------------------------------------------------------------
 * Función: impMatrix
 * Objetivo: Imprimir una matriz de tamaño D x D.
 * Restricción: Solo imprime matrices pequeñas (D < 9) para evitar saturar la consola.
 *-------------------------------------------------------------------------------------*/
void impMatrix(double *matrix, int D){
    printf("\n");
    if(D < 9){
        for(int i=0; i<D*D; i++){
            if(i%D==0) printf("\n"); // Salto de línea al final de cada fila
            printf("%f ", matrix[i]);
        }
        printf("\n**-----------------------------**\n");
    }
}

/*--------------------------------------------------------------------------------------
 * Función: iniMatrix
 * Objetivo: Inicializar dos matrices con valores aleatorios en el rango [0,99].
 *-------------------------------------------------------------------------------------*/
void iniMatrix(double *m1, double *m2, int D){
    for(int i=0; i<D*D; i++, m1++, m2++){
        *m1 =  rand()%100;    // Valor aleatorio entre 0 y 99
        *m2 =  rand()%100;	
    }
}

/*--------------------------------------------------------------------------------------
 * Función: multiMatrix
 * Objetivo: Multiplicar dos matrices (mA y mB) y guardar el resultado en mC.
 *           Usa el algoritmo clásico de multiplicación (O(n^3)).
 *           Se paraleliza con OpenMP dividiendo el bucle externo (filas).
 *-------------------------------------------------------------------------------------*/
void multiMatrix(double *mA, double *mB, double *mC, int D){
    double Suma, *pA, *pB;

    // Región paralela OpenMP
    #pragma omp parallel
    {
        // Se distribuyen las filas de la matriz resultado entre hilos
        #pragma omp for
        for(int i=0; i<D; i++){
            for(int j=0; j<D; j++){
                // Punteros para recorrer fila de A y columna de B
                pA = mA+i*D;	
                pB = mB+j; 
                Suma = 0.0;

                // Producto punto entre fila i de A y columna j de B
                for(int k=0; k<D; k++, pA++, pB+=D){
                    Suma += *pA * *pB;
                }

                // Se almacena el valor calculado en C[i][j]
                mC[i*D+j] = Suma;
            }
        }
    }
}

/*--------------------------------------------------------------------------------------
 * Función principal: main
 * Objetivo: 
 *   - Recibir parámetros de entrada (tamaño de matriz y número de hilos)
 *   - Reservar memoria para matrices
 *   - Inicializar matrices
 *   - Ejecutar la multiplicación con OpenMP
 *   - Medir tiempo de ejecución
 *   - Liberar memoria al final
 *-------------------------------------------------------------------------------------*/
int main(int argc, char *argv[]){
    // Validar parámetros de entrada
    if(argc < 3){
        printf("\n Uso: $ ./clasicaOpenMP SIZE Hilos \n\n");
        exit(0);
    }

    // Conversión de argumentos a enteros
    int N = atoi(argv[1]);   // Tamaño de la matriz cuadrada (N x N)
    int TH = atoi(argv[2]);  // Número de hilos a usar en OpenMP

    // Reserva de memoria dinámica para las matrices A, B y C
    double *matrixA  = (double *)calloc(N*N, sizeof(double));
    double *matrixB  = (double *)calloc(N*N, sizeof(double));
    double *matrixC  = (double *)calloc(N*N, sizeof(double));

    // Inicialización de semilla aleatoria
    srand(time(NULL));

    // Configurar número de hilos en OpenMP
    omp_set_num_threads(TH);

    // Inicializar matrices A y B con valores aleatorios
    iniMatrix(matrixA, matrixB, N);

    // Imprimir matrices A y B (solo si N < 9)
    impMatrix(matrixA, N);
    impMatrix(matrixB, N);

    // Medición del tiempo de multiplicación
    InicioMuestra();
    multiMatrix(matrixA, matrixB, matrixC, N);
    FinMuestra();

    // Imprimir matriz resultado C (solo si N < 9)
    impMatrix(matrixC, N);

    // Liberación de memoria reservada
    free(matrixA);
    free(matrixB);
    free(matrixC);
    
    return 0;
}
