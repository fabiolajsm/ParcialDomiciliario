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
#include "ventas.h"

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
		int minimo, int maximo) {
	int ret = -1;
	int esValido = 0;
	int num;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (esValido == 0) {
			printf("%s", mensaje);
			if (obtenerInt(&num) == 0) {
				if (num <= maximo && num >= minimo) {
					*pResultado = num;
					ret = 0;
					esValido = 1;
					break;
				}
			}
			printf("%s", mensajeError);
		}
	}
	return ret;
}

int obtenerNumeroConIntentos(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int intentos) {
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
		int tieneCondicion, int minCaracteres, int maxCaracteres) {
	int retorno = -1;
	int esTextoValido = 0;
	char auxTexto[1024];

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (esTextoValido == 0) {
			printf("%s", mensaje);
			if (obtenerString(auxTexto, sizeof(auxTexto)) == 0) {
				int caracteres = strnlen(auxTexto, sizeof(auxTexto));
				if (tieneCondicion == 1) {
					if (caracteres <= maxCaracteres
							&& caracteres >= minCaracteres) {
						strncpy(pResultado, auxTexto, largo);
						esTextoValido = 1;
						retorno = 0;
						break;
					}
				} else {
					strncpy(pResultado, auxTexto, largo);
					esTextoValido = 0;
					retorno = 0;
					break;
				}
			}
			printf("%s", mensajeError);
		}
	}
	return retorno;
}

static int esFechaCorrecta(int dia, int mes, int anio) {
	int ret = -1;

	if (dia < 1) {
		printf("Error, el día no puede ser menor a 1.\n");
	} else if (mes > 12 || mes < 1) {
		printf("Error, el mes no puede ser menor a 1 ni mayor a 12.\n");
	} else if (anio < 1 && anio > 2022) {
		printf(
				"Error, el año no puede ser menor a 1 ni mayor al año actual (2022).\n");
	}

	switch (mes) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (dia > 31) {
			printf("Error, este mes no tiene más de 31 días.\n");
		} else {
			ret = 0;
		}
		break;
	case 2:
		if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
			if (dia > 0 && dia < 30) {
				ret = 0;
			} else {
				printf("Error, este mes no tiene más de 29 días.\n");
			}
		} else {
			if (dia > 0 && dia < 29) {
				ret = 0;
			} else {
				printf("Error, este mes no tiene más de 28 días.\n");
			}
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (dia > 30) {
			printf("Error, este mes no tiene más de 30 días.\n");
		} else {
			ret = 0;
		}
		break;
	}

	return ret;
}

int obtenerFecha(eFecha *pFecha) {
	int ret = -1;
	int esFechaValida = -1;
	int dia;
	int mes;
	int anio;
	eFecha aux;

	if (pFecha != NULL) {
		while (esFechaValida == -1) {
			printf("Ingrese día:\n");
			obtenerInt(&dia);
			printf("Ingrese mes:\n");
			obtenerInt(&mes);
			printf("Ingrese año:\n");
			obtenerInt(&anio);
			esFechaValida = esFechaCorrecta(dia, mes, anio);
		}
		if (esFechaValida == 0) {
			aux.dia = dia;
			aux.mes = mes;
			aux.anio = anio;
			*pFecha = aux;
			ret = 0;
		}
	}
	return ret;
}

