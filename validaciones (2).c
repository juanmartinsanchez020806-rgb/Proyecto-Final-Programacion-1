#include "validaciones.h"
#include <stdio.h>

void limpiarBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int validarEntero(int valor, int min, int max) {
	return (valor >= min && valor <= max);
}

int validarDecimal(float valor, float min, float max) {
	return (valor >= min && valor <= max); // CORREGIDO: <= en lugar de =<
}

void leerEnteroValido(const char *mensaje, int min, int max,int *variable) {
	int num;
	char terminador;
	while(1) {
		printf("%s",mensaje);
		if (scanf("%d%c", &num, &terminador)!=2||terminador!='\n') {
			printf("Entrada invalida. Ingrese solo numeros enteros entre %d y %d\n",min,max);
			limpiarBuffer();
		} else if(!validarEntero(num,min,max)) {
			printf("Fuera de rango, ingrese un numero entre %d y %d\n",min,max);
		} else {
			*variable = num;
			break;
		}
	}
}

void leerFloatValido(const char *mensaje,float min, float max,float *variable) {
	float num;
	char terminador;
	while(1) {
		printf("%s",mensaje);
		if (scanf("%f%c", &num, &terminador)!=2||terminador!='\n') {
			printf("Entrada invalida. Ingrese solo numeros entre %.2f y %.2f\n",min,max);
			limpiarBuffer();
		} else if(!validarDecimal(num,min,max)) {
			printf("Fuera de rango, ingrese un numero entre %.2f y %.2f\n",min,max);
		} else {
			*variable = num;
			break;
		}
	}
}

void estandarizarCadena(char *cadena) {
	while (*cadena) {
		*cadena = toupper((unsigned char)*cadena);
		cadena++;
	}
}

int validarNombre(const char *cadena,int maxLongitud) {
	if(cadena==NULL||strlen(cadena)==0) {
		return 0;
	}
	if(strlen(cadena)>maxLongitud) {
		return 0;
	}
	while (*cadena) {
		if(!isalpha((unsigned char)*cadena)&& *cadena!=' ') {
			return 0;
		}
		cadena++;
	}
	return 1;
}

void leerNombreValido(const char *mensaje, char *destino, int maxLongitud) {
	int i;
	do {
		printf("%s", mensaje);
		fgets(destino, maxLongitud, stdin);

		int longitud = strlen(destino);
		if (longitud > 0 && destino[longitud - 1] == '\n') {
			destino[longitud - 1] = '\0';
			i = validarNombre(destino, maxLongitud - 1);
			if (i == 0) {
				printf("El nombre debe contener unicamente letras\n");
			}
		}
		else {
			printf("Error: El texto es demasiado largo (Maximo %d caracteres).\n", maxLongitud - 1);
			limpiarBuffer();
			i = 0;
		}
	} while (i != 1);
}

int validarNombreNum(const char *cadena,int maxLongitud, int minLongitud) {
	if(cadena==NULL||strlen(cadena)==0) {
		return 0;
	}
	if(strlen(cadena)>maxLongitud+1||strlen(cadena)<minLongitud) {
		return 0;
	}
	while (*cadena) {
		if((isalpha(*cadena))||!isalpha((*cadena))) {
			return 1;
		}
		cadena++;
	}
	return 1;
}

void leerNombreNumValido(const char *mensaje, char *destino,int maxLongitud, int minLongitud) {
	int i;
	do {
		printf("%s", mensaje);
		fgets(destino, maxLongitud, stdin);

		int longitud = strlen(destino);
		if (longitud > 0 && destino[longitud - 1] == '\n') {
			destino[longitud - 1] = '\0';
			i = validarNombreNum(destino, maxLongitud,minLongitud-1);
			if (i == 0) {
				printf("El nombre debe solo contener numero o letras,entre %d y %d caracteres\n",minLongitud-1,maxLongitud-2);
			}
		}
		else {
			printf("Error: El texto es demasiado largo (Maximo %d caracteres).\n", maxLongitud - 2);
			limpiarBuffer();
			i = 0;
		}
	} while (i != 1);
}