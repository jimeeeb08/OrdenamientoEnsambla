#include <stdlib.h>
#include "integracion.h"

// Declaraciones de funciones en ASM (por ahora están vacías ya que no se ha implementado nada)
extern int asm_burbuja(int *arr, int n, int *buffer);
extern int asm_seleccion(int *arr, int n, int *buffer);


int burbujaOrd(int *arreglo, int n, int **salidaBuffer, int *pasosTotal) {

    // Capacidad estimada: En el peor caso va a durar n*(n-1)/2 pasos, característica de bubble sort
    int max_pasos = n * (n - 1) / 2 + 1; // Se calucla el numero total de iteraciones en el peor de los casos y se le suma 1
    int *buffer = malloc(sizeof(int) * n * max_pasos); // Se reserva memoria para el buffer

    int pasos = asm_burbuja(arreglo, n, buffer);
    

    *salidaBuffer = buffer; // Asignar el buffer al puntero de salida
    *pasosTotal = pasos; // Asignar la cantidad de pasos al puntero de salida

    return 0;
}

// Implementación de la función de ordenamiento por selección
int seleccionOrd(int *arreglo, int n, int **salidaBuffer, int *pasosTotal) {

    int max_pasos = n * (n - 1) / 2 + 1;
    int *buffer = malloc(sizeof(int) * n * max_pasos);

    int pasos = asm_seleccion(arreglo, n, buffer);

    *salidaBuffer = buffer;
    *pasosTotal = pasos;

    return 0;
}
