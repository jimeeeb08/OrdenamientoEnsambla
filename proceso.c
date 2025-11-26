#include "proceso.h"
#include <stdlib.h>
#include <string.h>

void procesoInicializar(Proceso *p, int tam) {
    p->capacidad = 20; // Capacidad inicial
    p->cantidad = 0;
    p->actual = 0;
    p->tamArreglo = tam;
    p->pasos = malloc(sizeof(int*) * p->capacidad);
}

void procesoAgregarPaso(Proceso *p, int *arreglo) {
    // Verificar si es necesario redimensionar
    if (p->cantidad >= p->capacidad) {
        p->capacidad *= 2;
        p->pasos = realloc(p->pasos, sizeof(int*) * p->capacidad);
    }
    // Hacer una copia del arreglo y almacenarla
    int *copia = malloc(sizeof(int) * p->tamArreglo);
    memcpy(copia, arreglo, sizeof(int) * p->tamArreglo);
    // Agregar la copia al proceso
    p->pasos[p->cantidad++] = copia;
}

// Obtener un paso específico
int* procesoObtenerPaso(Proceso *p, int indice) {
    if (indice < 0 || indice >= p->cantidad)
        return NULL;
    return p->pasos[indice];
}

void procesoReset(Proceso *p){
    p->actual = 0; // Reiniciar al primer paso
}

void procesoLiberar(Proceso *p) {
    // Liberar cada paso almacenado
    for (int i = 0; i < p->cantidad; i++)
        free(p->pasos[i]);
    // Liberar el arreglo de pasos
    free(p->pasos);
    p->pasos = NULL;
    p->cantidad = 0;
    p->capacidad = 0;
    p->actual = 0;
}
