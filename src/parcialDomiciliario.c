/*
 ============================================================================
 Name        : ParcialDomiciliario.c
 Author      : fsuarez
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "articulos.h"
#include "validaciones.h"
#include "ventas.h"
#define CANTIDAD_ARTICULOS 10
#define CANTIDAD_VENTAS 10
#define MENSAJE_MENU "MENU DE OPCIONES:\n1. Alta de articulos.\n2. Modificar articulos.\n3. Baja de articulos.\n4. Listar articulos.\n5. Listar rubros.\n6. Alta de ventas.\n7. Listar ventas.\n8. Informes.\n9. Salir.\n"
#define ERROR_MENU "Error. No ingresó una opción válida, tiene que ser un número del 1 al 9."

int main(void) {
	int opcion;
	int esOpcionValida;
	int mostrarMenu = 1;
	eArticulo articulos[CANTIDAD_ARTICULOS];
	inicializarArticulos(articulos, CANTIDAD_ARTICULOS);
	eVenta ventas[CANTIDAD_VENTAS];
	inicializarVentas(ventas, CANTIDAD_VENTAS);

	while (mostrarMenu) {
		// Pedimos al usuario que ingrese una opción:
		esOpcionValida = obtenerNumero(&opcion, MENSAJE_MENU, ERROR_MENU, 1, 9);
		if (esOpcionValida == 0) {
			switch (opcion) {
			case 1:
				darAltaArticulos(articulos, CANTIDAD_ARTICULOS);
				break;
			case 2:
				modificarArticulo(articulos, CANTIDAD_ARTICULOS);
				break;
			case 3:
				darBajaArticulo(articulos, CANTIDAD_ARTICULOS);
				break;
			case 4:
				listarArticulos(articulos, CANTIDAD_ARTICULOS);
				break;
			case 5:
				listarRubros(articulos, CANTIDAD_ARTICULOS);
				break;
			case 6:
				darAltaVentas(ventas, CANTIDAD_VENTAS, articulos,
				CANTIDAD_ARTICULOS);
				break;
			case 7:
				listarVentas(ventas, CANTIDAD_VENTAS);
				break;
			case 8:
				mostrarInformes(ventas, CANTIDAD_VENTAS, articulos,
				CANTIDAD_ARTICULOS);
				break;
			case 9:
				mostrarMenu = 0;
				printf("Menu de opciones cerrado.\n");
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}
