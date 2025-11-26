#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "proceso.h"

#include <gtk/gtk.h>

// Estructura Arreglo usada por todo el proyecto
typedef struct {
    int *datos;
    int tam;
} Arreglo;

GtkWidget *crearInterfaz(GtkApplication *app);

#endif
