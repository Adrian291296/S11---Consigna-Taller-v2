#include <stdio.h>
#include <string.h>
#include <ctype.h> // Para isspace
#include "validaciones.h"

void limpiarBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int obtenerEntero(const char *mensaje)
{
    int valor;
    int resultado;
    do
    {
        printf("%s", mensaje);
        resultado = scanf("%d", &valor);
        limpiarBufferEntrada();
        if (resultado != 1)
        {
            printf("Error: Por favor, introduce un numero entero valido.\n");
        }
    } while (resultado != 1);
    return valor;
}

int obtenerEnteroPositivo(const char *mensaje)
{
    int valor;
    int resultado;
    do
    {
        printf("%s", mensaje);
        resultado = scanf("%d", &valor);
        limpiarBufferEntrada();
        if (resultado != 1)
        {
            printf("Error: Por favor, introduce un numero entero valido.\n");
        }
        else if (valor <= 0)
        {
            printf("Error: El numero debe ser positivo (mayor que cero).\n");
        }
    } while (resultado != 1 || valor <= 0);
    return valor;
}

// Función auxiliar para verificar si una cadena está vacía o solo contiene espacios.
int esCadenaVacia(const char *cadena)
{
    while (*cadena)
    {
        if (!isspace((unsigned char)*cadena))
        {
            return 0; // No está vacía
        }
        cadena++;
    }
    return 1; // Está vacía
}

void obtenerCadena(const char *mensaje, char *buffer, int tamano)
{
    do
    {
        printf("%s", mensaje);
        if (fgets(buffer, tamano, stdin) != NULL)
        {
            // Eliminar el salto de línea final si existe
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n')
            {
                buffer[len - 1] = '\0';
            }
            else
            {
                // Si no había salto de línea, el buffer de entrada puede tener caracteres extra.
                limpiarBufferEntrada();
            }
        }

        if (esCadenaVacia(buffer))
        {
            printf("Error: La entrada no puede estar vacia. Inténtalo de nuevo.\n");
        }
    } while (esCadenaVacia(buffer));
}
