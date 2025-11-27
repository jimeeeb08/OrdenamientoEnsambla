# Nombre del ejecutable
TARGET = proyecto

# Archivos fuente C
SRC_C = main.c interfaz.c proceso.c integracion.c

# Archivos fuente ASM
SRC_ASM = algBurbuja.asm algSeleccion.asm

# Archivos objeto generados
OBJ_C = $(SRC_C:.c=.o)
OBJ_ASM = $(SRC_ASM:.asm=.o)
OBJ = $(OBJ_C) $(OBJ_ASM)

# Compiladores
CC = gcc
NASM = nasm

# Flags de GTK4 obtenidos automáticamente con pkg-config
GTK_CFLAGS = `pkg-config --cflags gtk4`
GTK_LIBS = `pkg-config --libs gtk4`

# Flags de compilación
CFLAGS = -Wall -Wno-deprecated-declarations -g $(GTK_CFLAGS)
NASMFLAGS = -f elf64 -g -F dwarf
.SILENT:
# Regla por defecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(GTK_LIBS)

# Regla para compilar archivos .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar archivos .asm a .o
%.o: %.asm
	$(NASM) $(NASMFLAGS) $< -o $@

# Limpieza de archivos objeto y ejecutable
clean:
	rm -f $(OBJ) $(TARGET)

# Limpieza completa (incluye archivos temporales)
mrproper: clean
	rm -f *~ *.swp

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Prevenir que Make trate estos nombres como archivos
.PHONY: all clean mrproper run
