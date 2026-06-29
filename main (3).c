#include <stdio.h>
#include "contaminacion.h"

int main() {
	Zona zonas[NUM_ZONAS] = {
		{"Norte (Industrial)"},
		{"Sur (Residencial)"},
		{"Centro (Comercial)"},
		{"Este (Valles)"},
		{"Oeste (Periferia)"}
	};

	printf("=== Sistema Integral de Gestion y Prediccion de Contaminacion ===\n\n");

	cargarHistorial(zonas);
	ingresarDatosActuales(zonas);

	calcularPromediosYPredicciones(zonas);
	emitirAlertasYRecomendaciones(zonas);
	guardarReporte(zonas);

	printf("\nProceso terminado. Datos salvados en el disco.\n");
	return 0;
}