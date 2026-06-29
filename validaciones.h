#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string.h>
#include <ctype.h>

void limpiarBuffer();

int validarEntero(int valor, int min, int max);
void leerEnteroValido(const char *mensaje,int min, int max,int *variable);

int validarDecimal(float valor, float min, float max);
void leerFloatValido(const char *mensaje,float min, float max,float *variable);

void estandarizarCadena(char *cadena);
void leerNombreValido(const char *mensaje, char *destino, int maxLongitud);
int validarNombre(const char *cadena,int maxLongitud);

void leerNombreNumValido(const char *mensaje, char *destino,int maxLongitud, int minLongitud);
int validarNombreNum(const char *cadena,int maxLongitud,int minLongitud);

#endif
