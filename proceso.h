#ifndef PROCESO_H
#define PROCESO_H

typedef struct {
    int **pasos;       // Cada paso del proceso del ordenamiento
    int cantidad;      // Cantidad real de pasos guardados
    int capacidad;     // Capacidad del arreglo de pasos
    int actual;        // Paso actual (para el boton de reproducir)
    int tamArreglo;   // Tamaño de cada paso (cantidad de elementos)
} Proceso;

void procesoInicializar(Proceso *p, int tam);
void procesoAgregarPaso(Proceso *p, int *arreglo);
int* procesoObtenerPaso(Proceso *p, int indice);
void procesoReset(Proceso *p);
void procesoLiberar(Proceso *p);

#endif
