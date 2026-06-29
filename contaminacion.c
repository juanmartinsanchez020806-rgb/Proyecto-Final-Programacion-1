#include "contaminacion.h"
void cargarHistorial(Zona *zonas) {
	FILE *archivo = fopen("historial_zonas.txt", "r");
	if (archivo == NULL) {
		printf("\n[ERROR CRITICO] No se encontro el archivo 'historial_zonas.txt'.\n");
		printf("Por favor, asegurese de colocar el archivo de datos en la misma carpeta que el ejecutable.\n");
		exit(EXIT_FAILURE);
	}

	printf("Cargando historial de 30 dias desde 'historial_zonas.txt'...\n");
	char buffer[50];
	for (int i = 0; i < NUM_ZONAS; i++) {
		fscanf(archivo, "%s", buffer); // Lee el nombre de la zona (ej. "Norte")
		for (int j = 0; j < DIAS_HISTORIAL; j++) {
			fscanf(archivo, "%f", &zonas[i].historial_pm25[j]);
		}
	}
	fclose(archivo);
	printf("[OK] Historial cargado exitosamente.\n");
}

void ingresarDatosActuales(Zona *zonas) {
	printf("\n==================================================\n");
	printf("   INGRESO DE DATOS ACTUALES (ULTIMO DIA) \n");
	printf("==================================================\n");

	for (int i = 0; i < NUM_ZONAS; i++) {
		printf("\n>>> ZONA: %s <<<\n", zonas[i].nombre);

		leerFloatValido(" Ingrese el nivel de PM2.5 (ug/m3): ", 0.0, 500.0, &zonas[i].pm25_actual);
		leerFloatValido(" Ingrese el nivel de CO2 (ppm): ", 300.0, 2000.0, &zonas[i].co2_actual);
		leerFloatValido(" Ingrese la temperatura (Celsius): ", -10.0, 50.0, &zonas[i].temperatura);
		leerFloatValido(" Ingrese la velocidad del viento (km/h): ", 0.0, 150.0, &zonas[i].viento);
		leerFloatValido(" Ingrese el porcentaje de humedad (%): ", 0.0, 100.0, &zonas[i].humedad);
	}
	printf("\n[OK] Todos los datos actuales han sido validados y guardados.\n");
}

void calcularPromediosYPredicciones(Zona *zonas) {
	for (int i = 0; i < NUM_ZONAS; i++) {
		float suma_historico = 0;
		float suma_recientes = 0;

		for (int j = 0; j < DIAS_HISTORIAL; j++) {
			suma_historico += zonas[i].historial_pm25[j];
			if (j >= DIAS_HISTORIAL - 5) {
				suma_recientes += zonas[i].historial_pm25[j];
			}
		}
		zonas[i].prom_historico_pm25 = suma_historico / DIAS_HISTORIAL;

		float factor_clima = 1.0;
		if (zonas[i].viento < 10.0) factor_clima += 0.1;
		if (zonas[i].humedad > 70.0) factor_clima -= 0.05;

		float base_prediccion = ((suma_recientes / 5) * 0.6) + (zonas[i].prom_historico_pm25 * 0.4);
		zonas[i].prediccion_pm25 = base_prediccion * factor_clima;
	}
}

void emitirAlertasYRecomendaciones(Zona *zonas) {
	printf("\n==================================================\n");
	printf("           ALERTAS Y RECOMENDACIONES \n");
	printf("==================================================\n");
	for (int i = 0; i < NUM_ZONAS; i++) {
		printf("\nZona: %s\n", zonas[i].nombre);
		printf(" -> PM2.5 Actual: %.2f | Prediccion proxima 24h: %.2f\n", zonas[i].pm25_actual, zonas[i].prediccion_pm25);

		if (zonas[i].pm25_actual > LIMITE_PM25 || zonas[i].prediccion_pm25 > LIMITE_PM25) {
			printf(" [ALERTA PREVENTIVA] Se superan los limites permisibles de la OMS.\n");
			printf("  Medidas de mitigacion inmediatas:\n");
			printf("   - Restriccion vehicular y reduccion del trafico en la zona.\n");
			printf("   - Suspender actividades de educacion fisica y recreativas al aire libre.\n");
			if (zonas[i].prediccion_pm25 > LIMITE_PM25 + 15.0) {
				printf("   - ALERTA CRITICA: Sugerir el cierre temporal de las industrias del sector.\n");
			}
		} else {
			printf(" [INFO] Condiciones estables y niveles dentro del rango aceptable.\n");
		}
	}
}

void guardarReporte(Zona *zonas) {
	FILE *archivo = fopen("reporte_contaminacion.txt", "w");
	if (archivo == NULL) {
		printf("Error al generar el archivo de reporte.\n");
		return;
	}

	fprintf(archivo, "REPORTE DE CONTAMINACION Y PREDICCIONES URBANAS\n");
	fprintf(archivo, "==================================================\n\n");

	for (int i = 0; i < NUM_ZONAS; i++) {
		fprintf(archivo, "Zona: %s\n", zonas[i].nombre);
		fprintf(archivo, " - Promedio Historico de 30 dias (PM2.5): %.2f ug/m3\n", zonas[i].prom_historico_pm25);
		fprintf(archivo, " - Registro del Ultimo Dia (PM2.5): %.2f ug/m3\n", zonas[i].pm25_actual);
		fprintf(archivo, " - Prediccion de Alerta para las 24h (PM2.5): %.2f ug/m3\n", zonas[i].prediccion_pm25);
		if (zonas[i].prediccion_pm25 > LIMITE_PM25) {
			fprintf(archivo, " * ESTADO DE EMERGENCIA: Requiere aplicacion de politicas de mitigacion.\n");
		} else {
			fprintf(archivo, " * ESTADO: Estable.\n");
		}
		fprintf(archivo, "\n");
	}

	fclose(archivo);
	printf("\n[REPORTE] Archivo 'reporte_contaminacion.txt' actualizado exitosamente.\n");
}