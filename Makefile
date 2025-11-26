# Nombre del ejecutable
TARGET = proyecto

# Archivos fuente
SRC = main.c interfaz.c proceso.c

# Compilador
CC = gcc

# Flags de GTK4 obtenidos automáticamente con pkg-config
GTK_FLAGS = `pkg-config --cflags --libs gtk4`

# Flags de compilación
CFLAGS = -Wall -g

# Regla por defecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(GTK_FLAGS)

# Limpieza
clean:
	rm -f $(TARGET)

# Limpieza completa (incluye archivos temporales)
mrproper: clean
	rm -f *.o
