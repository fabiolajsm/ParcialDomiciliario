/*
 * articulos.c
 *
 *  Created on: 1 oct. 2022
 *      Author: fsuarez
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "articulos.h"
#include "validaciones.h"
#define ID_MAXIMO 21
#define LARGO_DESCRIPCION 31
#define MEDIDA_MAXIMA 100
#define PRECIO_MAXIMO 10000
#define ID_NOENCONTRADO "El ID del artículo no fue encontrado.\n"
#define MODIFICACION_EXITOSA "Se modificó exitosamente.\n"
#define ERROR_NO_EXISTE_ARTICULO "Error. No hay articulos ingresados, intente yendo a la opción 1.\n"

int inicializarArticulos(articulo articulos[], int largo) {
	int ret = -1;

	if (articulos != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			// True 1 para "esta vacio" y false 0 para "no está vacío"
			articulos[i].estaVacio = 1;
		}
		ret = 0;
	}
	return ret;
}

static int buscarItemVacio(articulo articulos[], int largo) {
	int ret = -1;
	if (articulos != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			if (articulos[i].estaVacio == 1) {
				// Si está vacío retornamos la posición del item.
				ret = i;
				break;
			}
		}
	}
	return ret;
}

static int agregarRubro(int idRubro) {
	int ret = -1;
	if (idRubro) {
		switch (idRubro) {
		case 1:
			ret = 1000;
			break;
		case 2:
			ret = 1001;
			break;
		case 3:
			ret = 1002;
			break;
		case 4:
			ret = 1003;
			break;
		}
	}
	return ret;
}

int darAltaArticulos(articulo articulos[], int largo) {
	int ret = -1;
	int posicionVacia = buscarItemVacio(articulos, largo);
	articulo auxArticulo;
	static int idArticulo = 10;
	int idRubro;

	if (articulos != NULL && largo > 0 && posicionVacia != -1) {
		obtenerTexto(auxArticulo.descripcion, LARGO_DESCRIPCION,
				"Ingrese la descripción del articulo:\n",
				"Error. La descripcion no puede tener más de 30 caracteres alfabeticos.\n",
				1, 1, 30, 3);
		obtenerNumero(&auxArticulo.medida,
				"Ingrese la medida del articulo (no puede ser superior a 100cm):\n",
				"Error. La medidas no pueden ser mayores a 100cm, menores a 0 ó escribirse en decimales.\n",
				1, MEDIDA_MAXIMA, 3);
		obtenerNumero(&auxArticulo.precio,
				"Ingrese el precio del articulo (no puede ser superior a 10000):\n",
				"Error. El precio del articulo no puede ser superior a 10000, menor a 0 ó escribirse en decimales.\n",
				1, PRECIO_MAXIMO, 3);
		obtenerNumero(&idRubro,
				"Ingrese el rubro del articulo:\n1- ELECTRÓNICA, 2- BLANCO, 3- AUDIO, 4- VIDEO\n",
				"Error. Opción inválida, marque un número del 1 al 4 (1- ELECTRÓNICA, 2-BLANCO, 3- AUDIO, 4- VIDEO).\n",
				1, 4, 3);
		idRubro = agregarRubro(idRubro);
		if (idRubro != -1) {
			auxArticulo.rubroId = idRubro;
		}
		auxArticulo.idArticulo = idArticulo;
		auxArticulo.estaVacio = 0;
		articulos[posicionVacia] = auxArticulo;

		printf(
				"Articulo dado de alta exitosamente! El número de identificador de este articulo es: %d.\n",
				idArticulo);
		idArticulo++;
		ret = 0;
	}
	return ret;
}

static int buscarArticuloPorId(articulo articulos[], int largo, int id) {
	int retorno = -1;

	if (articulos != NULL && largo > 0 && id > 0) {
		for (int i = 0; i < largo; i++) {
			if (articulos[i].estaVacio == 0 && articulos[i].idArticulo == id) {
				retorno = i;
				break;
			}
		}
	}

	return retorno;
}

static int existenArticulos(articulo articulos[], int largo) {
	int retorno = -1;

	if (articulos != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			if (articulos[i].estaVacio == 0) {
				retorno = 0;
				break;
			}
		}
	}

	return retorno;
}

static int modificarArticuloSubmenu(articulo articulos[], int indice) {
	int ret = -1;
	int mostrarSubmenu = 1;
	int esOpcionValida;
	int opcion;

	while (mostrarSubmenu == 1) {
		esOpcionValida =
				obtenerNumero(&opcion,
						"Ingrese una opción:\n1. Modificar medida.\n2. Modifcar precio.\n3. Modificar medida y precio.\n4. Salir.\n",
						"Error. Opción inválida, opciones disponibles: 1, 2, 3 o 4.\n",
						1, 4, 3);
		if (esOpcionValida == 0) {
			switch (opcion) {
			case 1:
				obtenerNumero(&articulos[indice].medida,
						"Ingrese la medida del articulo (no puede ser superior a 100cm):\n",
						"Error. La medidas no pueden ser mayores a 100cm, menores a 0 ó escribirse en decimales.\n",
						1, MEDIDA_MAXIMA, 3);
				printf(MODIFICACION_EXITOSA);
				break;
			case 2:
				obtenerNumero(&articulos[indice].precio,
						"Ingrese el precio del articulo (no puede ser superior a 10000):\n",
						"Error. El precio del articulo no puede ser superior a 10000, menor a 0 ó escribirse en decimales.\n",
						1, PRECIO_MAXIMO, 3);
				printf(MODIFICACION_EXITOSA);
				break;
			case 3:
				obtenerNumero(&articulos[indice].medida,
						"Ingrese la medida del articulo (no puede ser superior a 100cm):\n",
						"Error. La medidas no pueden ser mayores a 100cm, menores a 0 ó escribirse en decimales.\n",
						1, MEDIDA_MAXIMA, 3);
				obtenerNumero(&articulos[indice].precio,
						"Ingrese el precio del articulo (no puede ser superior a 10000):\n",
						"Error. El precio del articulo no puede ser superior a 10000, menor a 0 ó escribirse en decimales.\n",
						1, PRECIO_MAXIMO, 3);
				printf(MODIFICACION_EXITOSA);
				break;
			case 4:
				mostrarSubmenu = 0;
				printf("Menu de opciones cerrado.\n");
				break;
				break;
			}
			ret = 0;
		}
	}
	return ret;
}

int modificarArticulo(articulo articulos[], int largo) {
	int ret = -1;
	int id;
	int indice;
	int esValido;
	int hayArticulos = existenArticulos(articulos, largo);

	if (articulos != NULL && largo > 0 && hayArticulos == 0) {
		esValido = obtenerNumero(&id,
				"Ingrese el ID del articulo que va a modificar:\n",
				"Error. El ID tiene que ser numérico y no tiene decimales.\n",
				1, ID_MAXIMO, 3);
		indice = buscarArticuloPorId(articulos, largo, id);

		if (indice != -1 && esValido == 0) {
			ret = modificarArticuloSubmenu(articulos, indice);
		} else {
			printf(ID_NOENCONTRADO);
		}
	} else {
		printf(ERROR_NO_EXISTE_ARTICULO);
	}

	return ret;
}

int darBajaArticulo(articulo articulos[], int largo) {
	int ret = -1;
	int id;
	int indice;
	int esValido;
	int hayArticulos = existenArticulos(articulos, largo);

	if (articulos != NULL && largo > 0 && hayArticulos == 0) {
		esValido = obtenerNumero(&id,
				"Ingrese el ID del articulo que va a dar de baja:\n",
				"Error. El ID tiene que ser numérico y no tiene decimales.\n",
				1, ID_MAXIMO, 3);
		indice = buscarArticuloPorId(articulos, largo, id);

		if (indice != -1 && esValido == 0) {
			articulos[indice].estaVacio = 1;
			printf("Artículo dado de baja exitosamente!\n");
			ret = 0;
		} else {
			printf(ID_NOENCONTRADO);
		}
	} else {
		printf(ERROR_NO_EXISTE_ARTICULO);
	}

	return ret;
}

static void mostrarArticulo(articulo item) {
	char rubro[31];
	switch (item.rubroId) {
	case 1000:
		strcpy(rubro, "ELECTRÓNICA:\n");
		break;
	case 1001:
		strcpy(rubro, "BLANCO:\n");
		break;
	case 1002:
		strcpy(rubro, "AUDIO:\n");
		break;
	case 1003:
		strcpy(rubro, "VIDEO:\n");
		break;
	}
	printf("%s", rubro);
	printf("- ID Articulo: %d\n", item.idArticulo);
	printf("- Descripcion: %s\n", item.descripcion);
	printf("- Medida: %d\n", item.medida);
	printf("- Precio: %d\n", item.precio);
	printf("- Rubro ID: %d\n", item.rubroId);
}

static int mostrarArticulos(articulo articulos[], int largo) {
	int ret = -1;

	if (articulos != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			if (articulos[i].estaVacio == 0) {
				mostrarArticulo(articulos[i]);
			}
		}
	}
	return ret;
}

int listarArticulos(articulo articulos[], int largo) {
	int ret = -1;
	articulo aux;
	int hayArticulos = existenArticulos(articulos, largo);

	if (articulos != NULL && largo > 0 && hayArticulos == 0) {
		for (int i = 0; i < largo - 1; i++) {
			for (int j = 0; j < largo; j++) {
				if (articulos[i].estaVacio == 0
						&& articulos[j].estaVacio == 0) {
					// Primero ordeno por rubro de menor a mayor:
					if (articulos[i].rubroId < articulos[j].rubroId) {
						aux = articulos[i];
						articulos[i] = articulos[j];
						articulos[j] = aux;
					}
					// Luego si los rubros coinciden
					// ordeno alfabéticamente de A-Z (por descripción)
					if (articulos[i].rubroId == articulos[j].rubroId
							&& articulos[i].descripcion[0]
									< articulos[j].descripcion[0]) {
						aux = articulos[i];
						articulos[i] = articulos[j];
						articulos[j] = aux;
					}
				}
			}
		}
		mostrarArticulos(articulos, largo);
		ret = 0;
	} else {
		printf(ERROR_NO_EXISTE_ARTICULO);
	}

	return ret;
}
