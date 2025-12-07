#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Limpia el buffer de entrada (stdin) para evitar lecturas incorrectas.
void limpiarBufferEntrada();

// Solicita y lee un número entero de forma segura.
int obtenerEntero(const char *mensaje);

// Solicita y lee un número entero positivo (>0) de forma segura.
int obtenerEnteroPositivo(const char *mensaje);

// Solicita y lee una cadena de texto de forma segura.
void obtenerCadena(const char *mensaje, char *buffer, int tamano);

#endif // VALIDACIONES_H
