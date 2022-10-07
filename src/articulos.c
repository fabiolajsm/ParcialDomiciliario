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
#define ID_MAXIMO 20
#define LARGO_DESCRIPCION 31
#define MEDIDA_MAXIMA 100
#define PRECIO_MAXIMO 10000
#define ID_NO_ENCONTRADO "El ID del artículo no fue encontrado.\n"
#define MODIFICACION_EXITOSA "Se modificó exitosamente.\n"
#define ERROR_NO_EXISTE_ARTICULO "Error. No se puede hacer esta acción si no hay articulos registrados.\n"

int inicializarArticulos(eArticulo articulos[], int largo) {
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

static int buscarArticuloVacio(eArticulo articulos[], int largo) {
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

int darAltaArticulos(eArticulo articulos[], int largo) {
	int ret = -1;
	int posicionVacia = buscarArticuloVacio(articulos, largo);
	eArticulo auxArticulo;
	static int idArticulo = 10;
	int idRubro;

	if (articulos != NULL && largo > 0 && posicionVacia != -1) {
		obtenerTexto(auxArticulo.descripcion, LARGO_DESCRIPCION,
				"Ingrese la descripción del articulo:\n",
				"Error. La descripcion no puede tener más de 30 caracteres alfabeticos.\n",
				1, 1, 30);
		obtenerNumero(&auxArticulo.medida,
				"Ingrese la medida del articulo (no puede ser superior a 100cm):\n",
				"Error. La medidas no pueden ser mayores a 100cm, menores a 0 ó escribirse en decimales.\n",
				1, MEDIDA_MAXIMA);
		obtenerNumero(&auxArticulo.precio,
				"Ingrese el precio del articulo (no puede ser superior a 10000):\n",
				"Error. El precio del articulo no puede ser superior a 10000, menor a 0 ó escribirse en decimales.\n",
				1, PRECIO_MAXIMO);
		obtenerNumero(&idRubro,
				"Ingrese el rubro del articulo:\n1- ELECTRÓNICA, 2- BLANCO, 3- AUDIO, 4- VIDEO\n",
				"Error. Opción inválida, marque un número del 1 al 4 (1- ELECTRÓNICA, 2-BLANCO, 3- AUDIO, 4- VIDEO).\n",
				1, 4);
		// Asigno el rubro:
		switch (idRubro) {
		case 1:
			auxArticulo.rubroId.idRubro = 1000;
			strcpy(auxArticulo.rubroId.descripcion, "Electrónica");
			break;
		case 2:
			auxArticulo.rubroId.idRubro = 1001;
			strcpy(auxArticulo.rubroId.descripcion, "Blanco");
			break;
		case 3:
			auxArticulo.rubroId.idRubro = 1002;
			strcpy(auxArticulo.rubroId.descripcion, "Audio");
			break;
		case 4:
			auxArticulo.rubroId.idRubro = 1003;
			strcpy(auxArticulo.rubroId.descripcion, "Video");
			break;
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

int buscarArticuloPorId(eArticulo articulos[], int largo, int id) {
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

int existenArticulos(eArticulo articulos[], int largo) {
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

static int modificarArticuloSubmenu(eArticulo articulos[], int indice) {
	int ret = -1;
	int mostrarSubmenu = 1;
	int opcion;

	while (mostrarSubmenu == 1) {
		obtenerNumero(&opcion,
				"Ingrese una opción:\n1. Modificar medida.\n2. Modifcar precio.\n3. Modificar medida y precio.\n4. Salir.\n",
				"Error. Opción inválida, opciones disponibles: 1, 2, 3 o 4.\n",
				1, 4);

		switch (opcion) {
		case 1:
			obtenerNumero(&articulos[indice].medida,
					"Ingrese la medida del articulo (no puede ser superior a 100cm):\n",
					"Error. La medidas no pueden ser mayores a 100cm, menores a 0 ó escribirse en decimales.\n",
					1, MEDIDA_MAXIMA);
			printf(MODIFICACION_EXITOSA);
			break;
		case 2:
			obtenerNumero(&articulos[indice].precio,
					"Ingrese el precio del articulo (no puede ser superior a 10000):\n",
					"Error. El precio del articulo no puede ser superior a 10000, menor a 0 ó escribirse en decimales.\n",
					1, PRECIO_MAXIMO);
			printf(MODIFICACION_EXITOSA);
			break;
		case 3:
			obtenerNumero(&articulos[indice].medida,
					"Ingrese la medida del articulo (no puede ser superior a 100cm):\n",
					"Error. La medidas no pueden ser mayores a 100cm, menores a 0 ó escribirse en decimales.\n",
					1, MEDIDA_MAXIMA);
			obtenerNumero(&articulos[indice].precio,
					"Ingrese el precio del articulo (no puede ser superior a 10000):\n",
					"Error. El precio del articulo no puede ser superior a 10000, menor a 0 ó escribirse en decimales.\n",
					1, PRECIO_MAXIMO);
			printf(MODIFICACION_EXITOSA);
			break;
		case 4:
			mostrarSubmenu = 0;
			printf("Submenu de opciones cerrado.\n");
			break;
		}
		ret = 0;
	}
	return ret;
}

int modificarArticulo(eArticulo articulos[], int largo) {
	int ret = -1;
	int id;
	int indice;
	int esValido;
	int hayArticulos = existenArticulos(articulos, largo);

	if (articulos != NULL && largo > 0 && hayArticulos == 0) {
		esValido = obtenerNumero(&id,
				"Ingrese el ID del articulo que va a modificar:\n",
				"Error. El ID tiene que ser numérico y no tiene decimales.\n",
				1, ID_MAXIMO);
		indice = buscarArticuloPorId(articulos, largo, id);

		if (indice != -1 && esValido == 0) {
			ret = modificarArticuloSubmenu(articulos, indice);
		} else {
			printf(ID_NO_ENCONTRADO);
		}
	} else {
		printf(ERROR_NO_EXISTE_ARTICULO);
	}

	return ret;
}

int darBajaArticulo(eArticulo articulos[], int largo) {
	int ret = -1;
	int id;
	int indice;
	int esValido;
	int hayArticulos = existenArticulos(articulos, largo);

	if (articulos != NULL && largo > 0 && hayArticulos == 0) {
		esValido = obtenerNumero(&id,
				"Ingrese el ID del articulo que va a dar de baja:\n",
				"Error. El ID tiene que ser numérico y no tiene decimales.\n",
				1, ID_MAXIMO);
		indice = buscarArticuloPorId(articulos, largo, id);

		if (indice != -1 && esValido == 0) {
			articulos[indice].estaVacio = 1;
			printf("Artículo dado de baja exitosamente!\n");
			ret = 0;
		} else {
			printf(ID_NO_ENCONTRADO);
		}
	} else {
		printf(ERROR_NO_EXISTE_ARTICULO);
	}

	return ret;
}

static void mostrarArticulo(eArticulo item, int mostrarTitulo) {
	char rubro[31];
	if (mostrarTitulo == 1) {
		switch (item.rubroId.idRubro) {
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
	}
	printf("- ID Articulo: %d\n", item.idArticulo);
	printf("- Descripcion: %s\n", item.descripcion);
	printf("- Medida: %d\n", item.medida);
	printf("- Precio: %d\n", item.precio);
	printf("- Rubro ID: %d\n", item.rubroId.idRubro);
	printf("--------------\n");
}

static int mostrarArticulos(eArticulo articulos[], int largo) {
	int ret = -1;

	if (articulos != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			if (articulos[i].estaVacio == 0) {
				mostrarArticulo(articulos[i], 1);
			}
		}
	}
	return ret;
}

int listarArticulos(eArticulo articulos[], int largo) {
	int ret = -1;
	eArticulo aux;
	int hayArticulos = existenArticulos(articulos, largo);

	if (articulos != NULL && largo > 0 && hayArticulos == 0) {
		for (int i = 0; i < largo - 1; i++) {
			for (int j = 0; j < largo; j++) {
				if (articulos[i].estaVacio == 0
						&& articulos[j].estaVacio == 0) {
					// Primero ordeno por rubro de menor a mayor:
					if (articulos[i].rubroId.idRubro
							< articulos[j].rubroId.idRubro) {
						aux = articulos[i];
						articulos[i] = articulos[j];
						articulos[j] = aux;
					}
					// Luego si los rubros coinciden
					// ordeno alfabéticamente de A-Z (por descripción)
					if (articulos[i].rubroId.idRubro
							== articulos[j].rubroId.idRubro
							&& strcmp(articulos[i].descripcion,
									articulos[j].descripcion) < 0) {
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

int listarRubros(eArticulo articulos[], int largo) {
	int ret = -1;
	int hayArticulos = existenArticulos(articulos, largo);

	// banderas:
	int existeElectronica = 0;
	int existeBlanco = 0;
	int existeAudio = 0;
	int existeVideo = 0;

	if (articulos != NULL && largo > 0 && hayArticulos == 0) {
		printf("Rubros registrados:\n");
		for (int i = 0; i < largo; i++) {
			if (articulos[i].estaVacio == 0) {
				switch (articulos[i].rubroId.idRubro) {
				case 1000:
					if (existeElectronica == 0) {
						printf("- %s.\n", articulos[i].rubroId.descripcion);
						existeElectronica = 1;
					}
					break;
				case 1001:
					if (existeBlanco == 0) {
						printf("- %s.\n", articulos[i].rubroId.descripcion);
						existeBlanco = 1;
					}
					break;
				case 1002:
					if (existeAudio == 0) {
						printf("- %s.\n", articulos[i].rubroId.descripcion);
						existeAudio = 1;
					}
					break;
				case 1003:
					if (existeVideo == 0) {
						printf("- %s.\n", articulos[i].rubroId.descripcion);
						existeVideo = 1;
					}
					break;
				}
			}
		}
		ret = 0;
	} else {
		printf(ERROR_NO_EXISTE_ARTICULO);
	}
	return ret;
}

static int mostrarArticulosPorRubro(eArticulo articulos[], int largo,
		int idRubro) {
	int ret = -1;

	if (articulos != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			if (articulos[i].estaVacio == 0
					&& articulos[i].rubroId.idRubro == idRubro) {
				mostrarArticulo(articulos[i], 0);
				ret = 0;
			}
		}
	}
	return ret;
}

int mostrarPorRubro(eArticulo articulos[], int largo) {
	int ret = -1;
	int rubroId;
	char rubro[31];
	int rubroSeleccionado;
	int seMostraronArticulos;

	if (existenArticulos(articulos, largo) != 0) {
		printf(ERROR_NO_EXISTE_ARTICULO);
	} else {
		if (articulos != NULL && largo > 0) {
			obtenerNumero(&rubroId,
					"Ingrese el rubro del articulo:\n1- ELECTRÓNICA, 2- BLANCO, 3- AUDIO, 4- VIDEO\n",
					"Error. Opción inválida, marque un número del 1 al 4 (1- ELECTRÓNICA, 2-BLANCO, 3- AUDIO, 4- VIDEO).\n",
					1, 4);
			switch (rubroId) {
			case 1:
				strcpy(rubro, "ELECTRÓNICA");
				rubroSeleccionado = 1000;
				break;
			case 2:
				strcpy(rubro, "BLANCO");
				rubroSeleccionado = 1001;
				break;
			case 3:
				strcpy(rubro, "AUDIO");
				rubroSeleccionado = 1002;
				break;
			case 4:
				strcpy(rubro, "VIDEO");
				rubroSeleccionado = 1003;
				break;
			}
			printf("-> %s:\n", rubro);
			seMostraronArticulos = mostrarArticulosPorRubro(articulos, largo,
					rubroSeleccionado);
			if (seMostraronArticulos == -1) {
				printf("No hay articulos con este rubro.\n");
			}
			ret = 0;
		}
	}
	return ret;
}

