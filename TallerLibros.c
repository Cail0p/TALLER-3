#include <stdio.h>

#define MAX_LIBROS 10

typedef struct     //Decidi usar typedef ya que es más limpio y no necesitas escribir tanto
{
    int id;
    char titulo[100];
    char autor[50];
    int year;
    char estado[12]; // "Disponible" o "Prestado"
} Libro;

Libro biblioteca[MAX_LIBROS];
int totalLibros = 0;

// Copiar cadena manualmente
int copiarCadena(char *destino, const char *origen) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

// Comparar cadenas (devuelve 1 si iguales)
int compararCadena(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return 0;
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

// Validar si un ID ya existe
int idExiste(int id) {
    for (int i = 0; i < totalLibros; i++) {
        if (biblioteca[i].id == id)
            return 1;
    }
    return 0;
}

// Registrar libro
int registrarLibro() {
    if (totalLibros >= MAX_LIBROS) {
        printf("No se pueden registrar más libros.\n");
        return;
    }

    int id;
    printf("Ingrese ID del libro: ");
    scanf("%d", &id);
    

    if (idExiste(id)) {
        printf("Error: El ID ya existe.\n");
        return;
    }

    biblioteca[totalLibros].id = id;

    printf("Ingrese título: ");
    scanf(" %s", biblioteca[totalLibros].titulo);

    printf("Ingrese autor: ");
    scanf(" %s", biblioteca[totalLibros].autor);

    printf("Ingrese año de publicación: ");
    scanf("%d", &biblioteca[totalLibros].year);
    

    copiarCadena(biblioteca[totalLibros].estado, "Disponible");
    totalLibros++;

    printf("Libro registrado exitosamente.\n");
}

// Mostrar todos los libros
int mostrarLibros() {
    printf("\n%-5s %-30s %-20s %-6s %-12s\n", "ID", "Título", "Autor", "Año", "Estado");
    for (int i = 0; i < totalLibros; i++) {
        printf("%-5d %-30s %-20s %-6d %-12s\n", biblioteca[i].id,
               biblioteca[i].titulo, biblioteca[i].autor,
               biblioteca[i].year, biblioteca[i].estado);
    }
}

// Buscar por ID o Título
int buscarLibro() {
    int opcion;
    printf("Buscar por: 1. ID | 2. Título\n");
    scanf("%d", &opcion);
  

    if (opcion == 1) {
        int id;
        printf("Ingrese ID: ");
        scanf("%d", &id);
       

        for (int i = 0; i < totalLibros; i++) {
            if (biblioteca[i].id == id) {
                printf("Libro encontrado: %s por %s (%d) [%s]\n", biblioteca[i].titulo,
                       biblioteca[i].autor, biblioteca[i].year, biblioteca[i].estado);
            
            }
        }
    } else if (opcion == 2) {
        char titulo[100];
        printf("Ingrese título: ");
        scanf(" %s ", titulo);

        for (int i = 0; i < totalLibros; i++) {
            if (compararCadena(biblioteca[i].titulo, titulo)) {
                printf("Libro encontrado: ID %d, %s por %s (%d) [%s]\n", biblioteca[i].id,
                       biblioteca[i].titulo, biblioteca[i].autor,
                       biblioteca[i].year, biblioteca[i].estado);
                
            }
        }
    }
    printf("Libro no encontrado.\n");
}

// Cambiar estado del libro
int actualizarEstado() {
    int id;
    printf("Ingrese ID del libro: ");
    scanf("%d", &id);
    

    for (int i = 0; i < totalLibros; i++) {
        if (biblioteca[i].id == id) {
            if (compararCadena(biblioteca[i].estado, "Disponible"))
                copiarCadena(biblioteca[i].estado, "Prestado");
            else
                copiarCadena(biblioteca[i].estado, "Disponible");

            printf("Estado actualizado a %s.\n", biblioteca[i].estado);
            
        }
    }
    printf("Libro no encontrado.\n");
}

// Eliminar libro por ID
int eliminarLibro() {
    int id;
    printf("Ingrese ID del libro a eliminar: ");
    scanf("%d", &id);
    

    for (int i = 0; i < totalLibros; i++) {
        if (biblioteca[i].id == id) {
            for (int j = i; j < totalLibros - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            totalLibros--;
            printf("Libro eliminado.\n");
            
        }
    }
    printf("Libro no encontrado.\n");
}

// Menú principal
int main() {
    int opcion;

    do {
        printf("\n=== Menú Biblioteca ===\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar estado\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1: registrarLibro(); break;
            case 2: mostrarLibros(); break;
            case 3: buscarLibro(); break;
            case 4: actualizarEstado(); break;
            case 5: eliminarLibro(); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n");
        }

    } while (opcion != 6);

    return 0;
}