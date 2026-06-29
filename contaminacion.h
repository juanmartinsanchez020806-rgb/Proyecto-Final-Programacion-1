#ifndef CONTAMINACION_H
#define CONTAMINACION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "validaciones.h"

#define NUM_ZONAS 5
#define DIAS_HISTORIAL 30

#define LIMITE_PM25 25.0
#define LIMITE_CO2 400.0

typedef struct {
	char nombre[50];
	float pm25_actual;
	float co2_actual;
	float temperatura;
	float viento;
	float humedad;
	float historial_pm25[DIAS_HISTORIAL];
	float prom_historico_pm25;
	float prediccion_pm25;
} Zona;

void cargarHistorial(Zona *zonas);
void ingresarDatosActuales(Zona *zonas);
void calcularPromediosYPredicciones(Zona *zonas);
void emitirAlertasYRecomendaciones(Zona *zonas);
void guardarReporte(Zona *zonas);

#endif