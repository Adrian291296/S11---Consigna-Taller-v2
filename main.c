#include <stdio.h>
#include "biblioteca.h"
#include "validaciones.h"

void mostrarMenu()
{
    printf("\n--- Menu de la Biblioteca ---\n");
    printf("1. Registrar un nuevo libro\n");
    printf("2. Mostrar todos los libros\n");
    printf("3. Buscar un libro\n");
    printf("4. Actualizar estado de un libro\n");
    printf("5. Eliminar un libro\n");
    printf("0. Salir\n");
    printf("-----------------------------\n");
}

int main()
{
    Libro biblioteca[MAX_LIBROS];
    int numLibros = 0;
    int opcion;

    // Opcional: inicializar la biblioteca al inicio
    inicializarBiblioteca(biblioteca, &numLibros);

    do
    {
        mostrarMenu();
        opcion = obtenerEntero("Selecciona una opcion: ");

        switch (opcion)
        {
        case 1:
            registrarLibro(biblioteca, &numLibros);
            break;
        case 2:
            mostrarLibros(biblioteca, numLibros);
            break;
        case 3:
            buscarLibro(biblioteca, numLibros);
            break;
        case 4:
            actualizarEstado(biblioteca, numLibros);
            break;
        case 5:
            eliminarLibro(biblioteca, &numLibros);
            break;
        case 0:
            printf("Saliendo del programa. ¡Hasta luego!\n");
            break;
        default:
            printf("Opcion no válida. Por favor, intenta de nuevo.\n");
            break;
        }

        if (opcion != 0)
        {
            printf("\nPresiona Enter para continuar...");
            getchar(); // Espera a que el usuario presione Enter
        }

    } while (opcion != 0);

    return 0;
}
