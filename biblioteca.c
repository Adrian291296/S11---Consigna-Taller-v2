#include <stdio.h>
#include <string.h>
#include <ctype.h> // Para toupper
#include "biblioteca.h"
#include "validaciones.h"

// --- Funciones Auxiliares (privadas al módulo) ---

// Busca un libro por su ID y devuelve su índice en el array.
// Devuelve -1 si no se encuentra.
int buscarIndicePorId(const Libro *biblioteca, int numLibros, int id)
{
    for (int i = 0; i < numLibros; i++)
    {
        if (biblioteca[i].id == id)
        {
            return i; // Devuelve el índice del libro encontrado
        }
    }
    return -1; // No encontrado
}

// Muestra la información de un solo libro.
void mostrarUnLibro(const Libro *libro)
{
    printf("| %-5d | %-30s | %-20s | %-4d | %-12s |\n",
           libro->id, libro->titulo, libro->autor, libro->anio, libro->estado);
}

// --- Implementación de Funciones Públicas ---

void inicializarBiblioteca(Libro *biblioteca, int *numLibros)
{
    *numLibros = 0;
    // Opcional: limpiar la memoria del array de libros
    for (int i = 0; i < MAX_LIBROS; i++)
    {
        biblioteca[i].id = 0;
    }
    printf("Biblioteca inicializada.\n");
}

void registrarLibro(Libro *biblioteca, int *numLibros)
{
    if (*numLibros >= MAX_LIBROS)
    {
        printf("Error: La biblioteca esta llena. No se pueden agregar mas libros.\n");
        return;
    }

    Libro nuevoLibro;
    int id;

    // Validar ID único
    do
    {
        id = obtenerEnteroPositivo("Introduce el ID del libro: ");
        if (buscarIndicePorId(biblioteca, *numLibros, id) != -1)
        {
            printf("Error: El ID %d ya existe. Por favor, introduce un ID unico.\n", id);
        }
    } while (buscarIndicePorId(biblioteca, *numLibros, id) != -1);

    nuevoLibro.id = id;

    obtenerCadena("Introduce el titulo del libro: ", nuevoLibro.titulo, MAX_TITULO);
    obtenerCadena("Introduce el autor del libro: ", nuevoLibro.autor, MAX_AUTOR);
    nuevoLibro.anio = obtenerEnteroPositivo("Introduce el año de publicacion: ");
    strcpy(nuevoLibro.estado, "Disponible"); // Por defecto, un libro nuevo está disponible

    biblioteca[*numLibros] = nuevoLibro;
    (*numLibros)++;

    printf("\n¡Libro registrado con exito!\n");
}

void mostrarLibros(const Libro *biblioteca, int numLibros)
{
    if (numLibros == 0)
    {
        printf("No hay libros registrados en la biblioteca.\n");
        return;
    }

    printf("\n--- Lista Completa de Libros ---\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-30s | %-20s | %-4s | %-12s |\n", "ID", "Titulo", "Autor", "Año", "Estado");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < numLibros; i++)
    {
        mostrarUnLibro(&biblioteca[i]);
    }
    printf("------------------------------------------------------------------------------------------\n");
}

void buscarLibro(const Libro *biblioteca, int numLibros)
{
    if (numLibros == 0)
    {
        printf("No hay libros para buscar.\n");
        return;
    }

    printf("\n--- Busqueda de Libros ---\n");
    printf("Buscar por (I)D o por (T)itulo?: ");
    char opcion;
    scanf(" %c", &opcion);
    limpiarBufferEntrada();

    int encontrados = 0;

    if (toupper(opcion) == 'I')
    {
        int id = obtenerEntero("Introduce el ID a buscar: ");
        int indice = buscarIndicePorId(biblioteca, numLibros, id);
        if (indice != -1)
        {
            printf("\nLibro encontrado:\n");
            printf("------------------------------------------------------------------------------------------\n");
            mostrarUnLibro(&biblioteca[indice]);
            printf("------------------------------------------------------------------------------------------\n");
            encontrados++;
        }
    }
    else if (toupper(opcion) == 'T')
    {
        char tituloBusqueda[MAX_TITULO];
        obtenerCadena("Introduce el titulo a buscar: ", tituloBusqueda, MAX_TITULO);

        printf("\nResultados de la busqueda para \"%s\":\n", tituloBusqueda);
        printf("------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < numLibros; i++)
        {
            // strstr busca una subcadena, lo que hace la búsqueda más flexible
            if (strstr(biblioteca[i].titulo, tituloBusqueda) != NULL)
            {
                if (encontrados == 0)
                { // Imprimir cabecera solo la primera vez
                    printf("| %-5s | %-30s | %-20s | %-4s | %-12s |\n", "ID", "Titulo", "Autor", "Año", "Estado");
                    printf("------------------------------------------------------------------------------------------\n");
                }
                mostrarUnLibro(&biblioteca[i]);
                encontrados++;
            }
        }
        if (encontrados > 0)
        {
            printf("------------------------------------------------------------------------------------------\n");
        }
    }
    else
    {
        printf("Opcion no valida.\n");
    }

    if (encontrados == 0)
    {
        printf("No se encontro ningún libro con ese criterio.\n");
    }
}

void actualizarEstado(Libro *biblioteca, int numLibros)
{
    if (numLibros == 0)
    {
        printf("No hay libros para actualizar.\n");
        return;
    }

    mostrarLibros(biblioteca, numLibros);
    int id = obtenerEntero("\nIntroduce el ID del libro para actualizar su estado: ");

    int indice = buscarIndicePorId(biblioteca, numLibros, id);

    if (indice == -1)
    {
        printf("Error: No se encontro ningún libro con el ID %d.\n", id);
        return;
    }

    // Puntero al libro que vamos a modificar
    Libro *libroAActualizar = &biblioteca[indice];

    printf("El estado actual del libro \"%s\" es: %s\n", libroAActualizar->titulo, libroAActualizar->estado);

    if (strcmp(libroAActualizar->estado, "Disponible") == 0)
    {
        strcpy(libroAActualizar->estado, "Prestado");
    }
    else
    {
        strcpy(libroAActualizar->estado, "Disponible");
    }

    printf("El estado del libro ha sido actualizado a: %s\n", libroAActualizar->estado);
}

void eliminarLibro(Libro *biblioteca, int *numLibros)
{
    if (*numLibros == 0)
    {
        printf("No hay libros para eliminar.\n");
        return;
    }

    mostrarLibros(biblioteca, *numLibros);
    int id = obtenerEntero("\nIntroduce el ID del libro que deseas eliminar: ");

    int indice = buscarIndicePorId(biblioteca, *numLibros, id);

    if (indice == -1)
    {
        printf("Error: No se encontro ningun libro con el ID %d.\n", id);
        return;
    }

    char confirmacion;
    printf("¿Estas seguro de que quieres eliminar el libro \"%s\" (ID: %d)? (S/N): ", biblioteca[indice].titulo, id);
    scanf(" %c", &confirmacion);
    limpiarBufferEntrada();

    if (toupper(confirmacion) == 'S')
    {
        // Para eliminar, movemos todos los elementos posteriores una posición hacia adelante
        for (int i = indice; i < (*numLibros - 1); i++)
        {
            biblioteca[i] = biblioteca[i + 1];
        }
        (*numLibros)--; // Decrementamos el contador de libros
        printf("Libro eliminado con exito.\n");
    }
    else
    {
        printf("Operacion de eliminacion cancelada.\n");
    }
}
