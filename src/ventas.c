/*
 * ventas.c
 *
 *  Created on: 7 oct. 2022
 *      Author: fsuarez
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "articulos.h"
#include "validaciones.h"
#include "ventas.h"
#define ID_MAXIMO 20
#define ID_NO_ENCONTRADO "El ID de la venta no fue encontrado.\n"
#define ERROR_NO_EXISTEN_ARTICULOS "Error. No se puede hacer esta acción si no hay articulos registrados.\n"
#define ERROR_NO_EXISTEN_VENTAS "Error. No se puede hacer esta acción si no hay ventas registradas.\n"
#define MODIFICACION_EXITOSA "Se modificó exitosamente.\n"

int inicializarVentas(eVenta ventas[], int largo) {
	int ret = -1;

	if (ventas != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			// True 1 para "esta vacio" y false 0 para "no está vacío"
			ventas[i].estaVacio = 1;
		}
		ret = 0;
	}
	return ret;
}

static int buscarItemVacio(eVenta ventas[], int largo) {
	int ret = -1;
	if (ventas != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			if (ventas[i].estaVacio == 1) {
				// Si está vacío retornamos la posición del item.
				ret = i;
				break;
			}
		}
	}
	return ret;
}

static int buscarVentaPorId(eVenta ventas[], int largo, int id) {
	int retorno = -1;

	if (ventas != NULL && largo > 0 && id > 0) {
		for (int i = 0; i < largo; i++) {
			if (ventas[i].estaVacio == 0 && ventas[i].idVenta == id) {
				retorno = i;
				break;
			}
		}
	}

	return retorno;
}

int darAltaVentas(eVenta ventas[], int largoV, eArticulo articulos[],
		int largoA) {
	int ret = -1;
	int posicionVacia = buscarItemVacio(ventas, largoV);
	int posicionArticulo = -1;
	int esCantidadValida = -1;
	static int idVenta = 20000;
	eVenta auxVenta;

	if ((ventas != NULL && largoV > 0) && (articulos != NULL && largoA > 0)
			&& posicionVacia != -1
			&& existenArticulos(articulos, largoA) == 0) {
		while (posicionArticulo == -1) {
			if (obtenerNumero(&auxVenta.articuloId,
					"Ingrese el ID del articulo que va a registrarse en ventas:\n",
					"Error. El ID tiene que ser numérico y no tiene decimales.\n",
					1, ID_MAXIMO) == 0) {
				posicionArticulo = buscarArticuloPorId(articulos, largoA,
						auxVenta.articuloId);
				if (posicionArticulo == -1) {
					printf("Articulo no encontrado.\n");
				}
			}
		}

		esCantidadValida =
				obtenerNumero(&auxVenta.cantidad,
						"Ingrese la cantidad (no puede ser mayor a 10.000):\n",
						"Error. La cantidad no pueden ser mayores a 10000, menores a 0 ó escribirse en decimales.\n",
						1, 10000);

		if (esCantidadValida == 0) {
			auxVenta.precioTotal = articulos[posicionArticulo].precio
					* auxVenta.cantidad;
		}
		obtenerFecha(&auxVenta.fecha);
		auxVenta.idVenta = idVenta;
		auxVenta.estaVacio = 0;
		ventas[posicionVacia] = auxVenta;

		printf(
				"Venta dada de alta exitosamente! El número de identificador de esta es: %d.\n",
				idVenta);
		idVenta++;
		ret = 0;
	} else {
		printf(ERROR_NO_EXISTEN_ARTICULOS);
	}
	return ret;
}

static int existenVentas(eVenta ventas[], int largo) {
	int retorno = -1;

	if (ventas != NULL && largo > 0) {
		for (int i = 0; i < largo; i++) {
			if (ventas[i].estaVacio == 0) {
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

static void mostrarVentas(eVenta item) {
	printf("- ID de Venta: %d\n", item.idVenta);
	printf("- Articulo ID: %d\n", item.articuloId);
	printf("- Cantidad: %d\n", item.cantidad);
	printf("- Precio total: %d\n", item.precioTotal);
	printf("- Fecha: %d/%d/%d\n", item.fecha.dia, item.fecha.mes,
			item.fecha.anio);
	printf("----------\n");
}

int listarVentas(eVenta ventas[], int largoV) {
	int ret = -1;

	if (existenVentas(ventas, largoV) != 0) {
		printf(ERROR_NO_EXISTEN_VENTAS);
	} else if (ventas != NULL && largoV > 0) {
		printf("Listado de ventas:\n");
		for (int i = 0; i < largoV; i++) {
			if (ventas[i].estaVacio == 0) {
				mostrarVentas(ventas[i]);
			}
		}
		ret = 0;
	}
	return ret;
}

static void mostrarVentasPorFecha(eVenta ventas[], int largo) {
	int seEncontro = 0;
	eFecha auxFecha;

	if (existenVentas(ventas, largo) != 0) {
		printf(ERROR_NO_EXISTEN_VENTAS);
	} else {
		if (ventas != NULL && largo > 0) {
			obtenerFecha(&auxFecha);
			printf("Lista de ventas efectuadas en esa fecha:\n");
			for (int i = 0; i < largo; i++) {
				if (ventas[i].estaVacio == 0
						&& (ventas[i].fecha.dia == auxFecha.dia
								&& ventas[i].fecha.mes == auxFecha.mes
								&& ventas[i].fecha.anio == auxFecha.anio)) {
					mostrarVentas(ventas[i]);
					seEncontro = 1;
				}
			}
			if (seEncontro == 0) {
				printf(
						"No se encontraron ventas efectuadas en la fecha seleccionada.\n");
			}
		}
	}
}

static void mostrarTotalVentasArticulo(eVenta ventas[], int largoV,
		eArticulo articulos[], int largoA) {
	int id;
	int posicionEncontrada;

	if (existenArticulos(articulos, largoA) != 0) {
		printf(ERROR_NO_EXISTEN_ARTICULOS);
	} else if (existenVentas(ventas, largoV) != 0) {
		printf(ERROR_NO_EXISTEN_VENTAS);
	} else {
		if ((ventas != NULL && largoV > 0)
				&& (articulos != NULL && largoA > 0)) {
			obtenerNumero(&id, "Ingrese el ID del articulo:\n",
					"Error. El ID tiene que ser numérico y no tiene decimales.\n",
					1,
					ID_MAXIMO);
			posicionEncontrada = buscarArticuloPorId(articulos, largoA, id);
			if (posicionEncontrada != -1) {
				for (int i = 0; i < largoV; i++) {
					if (ventas[i].articuloId == id) {
						printf("- Importe total: %d\n", ventas[i].precioTotal);
					}
				}
			}
		}
	}
}

void mostrarPorRubroYFecha(eVenta ventas[], int largoV, eArticulo articulos[],
		int largoA, int idRubro, eFecha fecha) {
	int contador = 0;
	int idsArticulos[largoA];
	int rubroExiste = 0;
	int totalFinal = 0;

	if ((ventas != NULL && largoV > 0) && (articulos != NULL && largoA > 0)) {
		for (int i = 0; i < largoA; i++) {
			// Primero buscamos articulos que tengan el rubro
			if (articulos[i].estaVacio == 0
					&& articulos[i].rubroId.idRubro == idRubro) {
				idsArticulos[contador] = articulos[i].idArticulo;
				rubroExiste = 1;
				contador++;
			}
		}
		for (int i = 0; i < largoV; i++) {
			// Luego buscamos las ventas que tengan el id del articulo
			// y coincidan con la fecha
			if (ventas[i].estaVacio == 0
					&& ventas[i].articuloId == idsArticulos[i]
					&& (ventas[i].fecha.dia == fecha.dia
							&& ventas[i].fecha.mes == fecha.mes
							&& ventas[i].fecha.anio == fecha.anio)) {
				totalFinal = totalFinal + ventas[i].precioTotal;
			}
		}
		// Si hay articulos que tengan el rubro seleccionado, imprimimos las ventas que existan en la fecha dada.
		if (rubroExiste == 1) {
			if (totalFinal == 0) {
				printf("No hay ventas que coincidan con esa fecha.\n");

			} else {
				printf("- Importe total: %d\n", totalFinal);
			}
		} else {
			printf("No hay articulos registrados con ese rubro.\n");
		}
	}
}

int mostrarTotalVentasRubro(eVenta ventas[], int largoV, eArticulo articulos[],
		int largoA) {
	int ret = -1;
	int idRubro;
	int rubroSeleccionado;
	eFecha fecha;

	if (existenArticulos(articulos, largoA) != 0) {
		printf(ERROR_NO_EXISTEN_ARTICULOS);
	} else if (existenVentas(ventas, largoV) != 0) {
		printf(ERROR_NO_EXISTEN_VENTAS);
	} else {
		if ((ventas != NULL && largoV > 0)
				&& (articulos != NULL && largoA > 0)) {
			obtenerNumero(&idRubro,
					"Ingrese el rubro del articulo:\n1- ELECTRÓNICA, 2- BLANCO, 3- AUDIO, 4- VIDEO\n",
					"Error. Opción inválida, marque un número del 1 al 4 (1- ELECTRÓNICA, 2-BLANCO, 3- AUDIO, 4- VIDEO).\n",
					1, 4);
			obtenerFecha(&fecha);
			switch (idRubro) {
			case 1:
				rubroSeleccionado = 1000;
				break;
			case 2:
				rubroSeleccionado = 1001;
				break;
			case 3:
				rubroSeleccionado = 1002;
				break;
			case 4:
				rubroSeleccionado = 1003;
				break;
			}
			mostrarPorRubroYFecha(ventas, largoV, articulos, largoA,
					rubroSeleccionado, fecha);
			ret = 0;
		}
	}
	return ret;
}

int mostrarInformes(eVenta ventas[], int largoV, eArticulo articulos[],
		int largoA) {
	int ret = -1;
	int mostrarSubmenu = 1;
	int opcion;

	if ((ventas != NULL && largoV > 0) && (articulos != NULL && largoA > 0)) {
		while (mostrarSubmenu == 1) {
			obtenerNumero(&opcion,
					"Ingrese una opción:\n1. Mostrar artículos de un rubro seleccionado.\n2. Mostrar todas las ventas efectuadas en una fecha seleccionada.\n3. Informar importe total de las ventas realizadas de un artículo seleccionado.\n4. Informar importe total de todas las ventas de un rubro en una fecha seleccionada.\n5. Salir\n",
					"Error. Opción inválida, opciones disponibles: 1, 2, 3, 4 o 5.\n",
					1, 5);

			switch (opcion) {
			case 1:
				mostrarPorRubro(articulos, largoA);
				break;
			case 2:
				mostrarVentasPorFecha(ventas, largoV);
				break;
			case 3:
				mostrarTotalVentasArticulo(ventas, largoV, articulos, largoA);
				break;
			case 4:
				mostrarTotalVentasRubro(ventas, largoV, articulos, largoA);
				break;
			case 5:
				mostrarSubmenu = 0;
				printf("Menu de informes cerrado.\n");
				break;
			}
			ret = 0;
		}
	}

	return ret;
}

// Funciones que no estan en el menu pero pidieron para cada entidad:
int darBajaVenta(eVenta ventas[], int largo) {
	int ret = -1;
	int id;
	int indice;
	int esValido;
	int hayVentas = existenVentas(ventas, largo);

	if (hayVentas != 0) {
		printf(ERROR_NO_EXISTEN_VENTAS);
	} else {
		if (ventas != NULL && largo > 0 && hayVentas == 0) {
			esValido =
					obtenerNumero(&id,
							"Ingrese el ID de la venta que va a dar de baja:\n",
							"Error. El ID tiene que ser numérico y no tiene decimales.\n",
							1, ID_MAXIMO);
			indice = buscarVentaPorId(ventas, largo, id);

			if (indice != -1 && esValido == 0) {
				ventas[indice].estaVacio = 1;
				printf("Venta dada de baja exitosamente!\n");
				ret = 0;
			} else {
				printf(ID_NO_ENCONTRADO);
			}
		}
	}

	return ret;
}

static int modificarVentaSubmenu(eVenta ventas[], int indice) {
	int ret = -1;
	int mostrarSubmenu = 1;
	int opcion;

	while (mostrarSubmenu == 1) {
		obtenerNumero(&opcion,
				"Ingrese una opción:\n1. Modificar cantidad.\n2. Modifcar precio total.\n3. Modificar cantidad y precio total.\n4. Salir.\n",
				"Error. Opción inválida, opciones disponibles: 1, 2, 3 o 4.\n",
				1, 4);

		switch (opcion) {
		case 1:
			obtenerNumero(&ventas[indice].cantidad,
					"Ingrese la cantidad (no puede ser mayor a 10.000):\n",
					"Error. La cantidad no pueden ser mayores a 10000, menores a 0 ó escribirse en decimales.\n",
					1, 10000);
			printf(MODIFICACION_EXITOSA);
			break;
		case 2:
			obtenerNumero(&ventas[indice].precioTotal,
					"Ingrese el precio final de la venta (no puede ser superior a 10000):\n",
					"Error. El precio de la venta no puede ser superior a 10000, menor a 0 ó escribirse en decimales.\n",
					1, 10000);
			printf(MODIFICACION_EXITOSA);
			break;
		case 3:
			obtenerNumero(&ventas[indice].cantidad,
					"Ingrese la cantidad (no puede ser mayor a 10.000):\n",
					"Error. La cantidad no pueden ser mayores a 10000, menores a 0 ó escribirse en decimales.\n",
					1, 10000);
			obtenerNumero(&ventas[indice].precioTotal,
					"Ingrese el precio final de la venta (no puede ser superior a 10000):\n",
					"Error. El precio de la venta no puede ser superior a 10000, menor a 0 ó escribirse en decimales.\n",
					1, 10000);
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

int modificarVenta(eVenta ventas[], int largo) {
	int ret = -1;
	int id;
	int indice;
	int esValido;
	int hayVentas = existenVentas(ventas, largo);

	if (ventas != NULL && largo > 0 && hayVentas == 0) {
		esValido = obtenerNumero(&id,
				"Ingrese el ID de la venta que va a modificar:\n",
				"Error. El ID tiene que ser numérico y no tiene decimales.\n",
				1, ID_MAXIMO);
		indice = buscarVentaPorId(ventas, largo, id);

		if (indice != -1 && esValido == 0) {
			ret = modificarVentaSubmenu(ventas, indice);
		} else {
			printf(ID_NO_ENCONTRADO);
		}
	} else {
		printf(ERROR_NO_EXISTEN_VENTAS);
	}

	return ret;
}

