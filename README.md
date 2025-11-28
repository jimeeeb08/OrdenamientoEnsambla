# Manual del Usuario
### Integrantes del grupo:
* Jimena Bejarano Sánchez C31074
* Melissa Garita Chacón C23186
* Stephanie Monge Ortiz C35035
* Andrés Ramírez Solís C36467

### Descripción del programa

El programa se basa en la ejecución de los algoritmos de ordenamiento _bubble sort_ y _selection sort_ implementados mediante lenguaje ensamblador, y la visualización de su funcionamiento graficada desde C, permitiéndole al usuario el manejo del arreglo a ordenar y seleccionar el método de ordenamiento que desea visualizar.

## Compilación y ejecución

Inicialmentese debe verificar si se tiene instalado los paquetes necesarios para compilar la biblioteca GTK 4, si no se tiene instalada, se debe ejecutar en la terminal los siguientes comandos:

* sudo apt update
* sudo apt install libgtk-4-dev


Para una sencilla compilación del programa se ha creado un Makefile donde se pueden seguir los siguientes comandos:

* _make_ para la compilación del programa
* _make run_ para la ejecución del programa
* _make clean_ para la limpieza de archivos objeto y ejecutables 
* _make mrproper_ para una limpieza completa (incluye archivos temporales)

## Uso del programa

Al ejecutar el programa se va a abrir una ventana con la interfaz y varias opciones de interacción.

En primer lugar, el usuario debe de ingresar una lista de números separados por espacio, en el espacio de la esquina superior izquierda. Una vez la lista ha sido ingresada, se debe de presionar el botón de "Cargar Lista", al hacer esto se van a mostrar en la ventana los valores ingresados gráficamente sin ordenar.

Para proceder con el ordenamiento, se debe seleccionar uno de los dos algoritmos disponibles en el menú desplegable ubicado a la derecha del botón "Ordenar". Ya con el algoritmo deseado seleccionado, se puede presionar "Ordenar" 

Para visualizar el ordenamiento gráficamente se utilizan los botones en la parte inferior de la ventana. Se puede utilizar el botón de "Reproducir" para una visualización automática de cada paso en orden, así como el botón "Pausar" para detener esta visualización. También es posible ver cada paso manualmente mediante los botones de "Anterior" y "Siguiente".

Para cerrar el programa se presiona la "X" en el borde superior de la ventana, y para cargar una lista nueva simplemente se repiten los pasos anteriores.