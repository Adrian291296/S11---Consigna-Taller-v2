#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// --- Constantes ---
#define MAX_LIBROS 10
#define MAX_TITULO 101 // 100 caracteres + terminador nulo '\0'
#define MAX_AUTOR 51   // 50 caracteres + terminador nulo '\0'
#define MAX_ESTADO 11  // "Disponible" (10) + terminador nulo '\0'

// --- Estructuras ---
typedef struct
{
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int anio;
    char estado[MAX_ESTADO]; // "Disponible" o "Prestado"
} Libro;

// --- Prototipos de Funciones ---

// Inicializa la biblioteca (opcional, buena práctica)
void inicializarBiblioteca(Libro *biblioteca, int *numLibros);

void registrarLibro(Libro *biblioteca, int *numLibros);
void mostrarLibros(const Libro *biblioteca, int numLibros);
void buscarLibro(const Libro *biblioteca, int numLibros);
void actualizarEstado(Libro *biblioteca, int numLibros);
void eliminarLibro(Libro *biblioteca, int *numLibros);

#endif // BIBLIOTECA_H
