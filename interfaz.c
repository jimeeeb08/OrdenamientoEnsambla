#include "interfaz.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Botones de control (vacios por ahora)
static void onAnterior(GtkButton *btn, gpointer user_data) {
    g_print("Anterior\n");
}

static void onPausa(GtkButton *btn, gpointer user_data) {
    g_print("Pausa\n");
}

static void onPlay(GtkButton *btn, gpointer user_data) {
    g_print("Reproducir\n");
}

static void onSig(GtkButton *btn, gpointer user_data) {
    g_print("Siguiente\n");
}


// Estructura privada para contener el estado de la aplicación ui
typedef struct {
    Arreglo arreglo;         
    GtkWidget *drawing_area;
    GtkWidget *entry;
    GtkWidget *combo;
    int pasoActual;
    int pasosTotales;
    int *steps_buffer;
    Proceso proceso; 
} DatosProyecto;

// Convierte la entrada de texto en un arreglo de enteros
int convertirEntradaAArreglo(const char *entrada, Arreglo *arreglo) {
    // Validar entrada
    if (!entrada || strlen(entrada) == 0)
        return 0;
    // Contar números
    char *copia = strdup(entrada);
    char *token = strtok(copia, " ");
    int contador = 0;
    
    while (token) {
        contador++;
        token = strtok(NULL, " ");
    }

    free(copia);
    copia = strdup(entrada);
    token = strtok(copia, " ");

    int *numeros = malloc(sizeof(int) * contador);
    int i = 0;

    while (token) {
        numeros[i++] = atoi(token);
        token = strtok(NULL, " ");
    }

    free(copia);

    arreglo->datos = numeros;
    arreglo->tam = contador;

    return contador;
}

// Parte que dibuja el arreglo en la interfaz
static void on_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    DatosProyecto *datos = (DatosProyecto*)user_data;

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    if (!datos->arreglo.datos || datos->arreglo.tam == 0) {
        cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 14.0);
        cairo_move_to(cr, 10, 20);
        cairo_show_text(cr, "Cargue una lista de números y presione 'Cargar Lista'.");
        return;
    }

    int n = datos->arreglo.tam;
    int *arr = datos->arreglo.datos;

    // Dibujar las barras del arreglo
    double margin = 10.0;
    double bar_space = (double)(width - 2*margin) / n;
    double bar_width = bar_space * 0.8;
    double max_val = 0.0;

    // Encontrar el valor máximo para escalar las barras
    for (int i = 0; i < n; ++i)
        if (arr[i] > max_val) max_val = arr[i];
    if (max_val <= 0) max_val = 1;

    for (int i = 0; i < n; ++i) {
        double x = margin + i * bar_space + (bar_space - bar_width) / 2.0;
        double h = ((double)arr[i] / max_val) * (height - 40);
        double y = height - h - 20;

        cairo_set_source_rgb(cr, 0.2, 0.6, 0.9);
        cairo_rectangle(cr, x, y, bar_width, h);
        cairo_fill(cr);

        char buf[32];
        snprintf(buf, sizeof(buf), "%d", arr[i]);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_font_size(cr, 12.0);
        cairo_move_to(cr, x + 2, y - 4);
        cairo_show_text(cr, buf);
    }
}

// Para cargar la lista desde la entrada de texto
void cargarLista(GtkButton *button, gpointer user_data)
{
    DatosProyecto *datos = (DatosProyecto*)user_data;

    const char *texto = gtk_editable_get_text(GTK_EDITABLE(datos->entry));

    Arreglo arrTemp = {0};

    int cantidad = convertirEntradaAArreglo(texto, &arrTemp);

    if (cantidad == 0) {
        g_print("Error: No ingresaste números válidos\n");
        return;
    }

    if (datos->arreglo.datos)
        free(datos->arreglo.datos);

    datos->arreglo = arrTemp;

    procesoLiberar(&datos->proceso);  // por si había un proceso previo
    procesoInicializar(&datos->proceso, datos->arreglo.tam);
    procesoAgregarPaso(&datos->proceso, datos->arreglo.datos);


    g_print("Arreglo cargado (%d elementos): ", datos->arreglo.tam);
    for (int i = 0; i < datos->arreglo.tam; i++)
        g_print("%d ", datos->arreglo.datos[i]);
    g_print("\n");

    gtk_widget_queue_draw(datos->drawing_area);
}

// Crear la interfaz gráfica
GtkWidget* crearInterfaz(GtkApplication *app)
{
    DatosProyecto *datos = g_malloc0(sizeof(DatosProyecto));

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Algoritmos de Ordenamiento");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    GtkWidget *hbox_input = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), hbox_input);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Ejemplo: 5 2 9 1 4");
    gtk_box_append(GTK_BOX(hbox_input), entry);
    datos->entry = entry;

    GtkWidget *btn_cargar = gtk_button_new_with_label("Cargar Lista");
    gtk_box_append(GTK_BOX(hbox_input), btn_cargar);

    GtkWidget *combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Burbuja");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Selección");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    gtk_box_append(GTK_BOX(hbox_input), combo);
    datos->combo = combo;

    GtkWidget *frame = gtk_frame_new("Visualización");
    gtk_widget_set_size_request(frame, 600, 400);
    gtk_box_append(GTK_BOX(vbox), frame);


    // Botones o controles de reproducción
    GtkWidget *hbox_controles = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(vbox), hbox_controles);

    GtkWidget *btnAnterior = gtk_button_new_with_label("Anterior");
    GtkWidget *btnPausa    = gtk_button_new_with_label("Pausa");
    GtkWidget *btnPlay     = gtk_button_new_with_label("Reproducir");
    GtkWidget *btnSig = gtk_button_new_with_label("Siguiente");

    gtk_box_append(GTK_BOX(hbox_controles), btnAnterior);
    gtk_box_append(GTK_BOX(hbox_controles), btnPausa);
    gtk_box_append(GTK_BOX(hbox_controles), btnPlay);
    gtk_box_append(GTK_BOX(hbox_controles), btnSig);

    // Callbacks vacíos por ahora (solo para compilar)
    g_signal_connect(btnAnterior, "clicked", G_CALLBACK(onAnterior), datos);
    g_signal_connect(btnPausa, "clicked", G_CALLBACK(onPausa), datos);
    g_signal_connect(btnPlay, "clicked", G_CALLBACK(onPlay), datos);
    g_signal_connect(btnSig, "clicked", G_CALLBACK(onSig), datos);

    // Parte de ilustración del algoritmo
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(drawing_area, TRUE);
    gtk_widget_set_vexpand(drawing_area, TRUE);

    // Asignar la función de dibujo
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), on_draw, datos, NULL);

    // frame para el área de dibujo
    gtk_frame_set_child(GTK_FRAME(frame), drawing_area);
    datos->drawing_area = drawing_area;

    g_signal_connect(btn_cargar, "clicked", G_CALLBACK(cargarLista), datos);

    return window;
}
