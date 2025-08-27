#!/usr/bin/perl
#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: Santiago Pineda Mora
#     Fecha: 15/08/25
#     Materia: Introduccion Distribuidos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/

$Path = `pwd`;
chomp($Path);

# Nombre del ejecutable
$Nombre_Ejecutable = "mmClasicaOpenMP";

# Tamaños de matrices y número de hilos
@Size_Matriz = ("4080", "4800", "5600");
@Num_Hilos = (1,2,4,8,16,20);
$Repeticiones = 30;

foreach $size (@Size_Matriz) {
	foreach $hilo (@Num_Hilos) {
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

		for ($i=0; $i<$Repeticiones; $i++) {
			system("$Path/$Nombre_Ejecutable $size $hilo >> $file");
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}
	}
}
