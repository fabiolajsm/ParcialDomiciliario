/*
 * validaciones.c
 *
 *  Created on: 1 oct. 2022
 *      Author: fsuarez
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

static int esNumero(char cadena[]) {
	int i = 0;
	int retorno = 1;
	if (cadena != NULL && strlen(cadena) > 0) {
		while (cadena[i] != '\0') {
			if (cadena[i] < '0' || cadena[i] > '9') {
				retorno = 0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

static int obtenerInt(int *pResultado) {
	int ret = -1;
	char buffer[1024];

	fgets(buffer, sizeof(buffer), stdin);
	buffer[strlen(buffer) - 1] = '\0';

	if (esNumero(buffer) == 1) {
		*pResultado = atoi(buffer);
		ret = 0;
	}
	return ret;
}

int obtenerNumero(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int intentos, int validarDisponible) {
	int ret = -1;
	int num;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (intentos > 0) {
			printf("%s", mensaje);
			if (obtenerInt(&num) == 0) {
				if (num <= maximo && num >= minimo) {
					*pResultado = num;
					ret = 0;
					break;
				}
			}
			intentos--;
			printf("%s", mensajeError);
		}
	}
	return ret;
}

static int esTexto(char *cadena) {
	int i = 0;
	int retorno = 1;

	if (cadena != NULL && strlen(cadena) > 0) {
		for (i = 0; cadena[i] != '\0' && i < sizeof(cadena); i++) {
			if ((cadena[i] < 'A' || cadena[i] > 'Z')
					&& (cadena[i] < 'a' || cadena[i] > 'z')) {
				// Acá no es texto
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

static int obtenerString(char *pResultado, int longitud) {
	int retorno = -1;
	char buffer[1024];
	fgets(buffer, sizeof(buffer), stdin);

	if (pResultado != NULL && longitud > 0) {
		if (buffer[strnlen(buffer, sizeof(buffer)) - 1] == '\n') {
			buffer[strnlen(buffer, sizeof(buffer)) - 1] = '\0';
		}
		if (strnlen(buffer, sizeof(buffer)) <= longitud && esTexto(buffer)) {
			strncpy(pResultado, buffer, longitud);
			retorno = 0;

		}
	}
	return retorno;
}

int obtenerTexto(char *pResultado, int largo, char *mensaje, char *mensajeError,
		int tieneCondicion, int minCaracteres, int maxCaracteres, int intentos) {
	int retorno = -1;
	char auxTexto[1024];

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (intentos > 0) {
			printf("%s", mensaje);
			if (obtenerString(auxTexto, sizeof(auxTexto)) == 0) {
				int caracteres = strnlen(auxTexto, sizeof(auxTexto));
				if (tieneCondicion == 1) {
					if (caracteres <= maxCaracteres
							&& caracteres >= minCaracteres) {
						strncpy(pResultado, auxTexto, largo);
						retorno = 0;
						break;
					}
				} else {
					strncpy(pResultado, auxTexto, largo);
					retorno = 0;
					break;
				}
			}
			printf("%s", mensajeError);
			intentos--;
		}
	}
	return retorno;
}
