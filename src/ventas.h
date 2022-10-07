/*
 * ventas.h
 *
 *  Created on: 7 oct. 2022
 *      Author: fsuarez
 */

#ifndef VENTAS_H_
#define VENTAS_H_
#include "articulos.h"

typedef struct {
	int dia;
	int mes;
	int anio;
} eFecha;

typedef struct {
	int idVenta; // Comienza en 20000
	int articuloId; // Validar que exista el articulo
	int cantidad;
	int precioTotal;
	eFecha fecha; // validar fecha correcta
	int estaVacio;
} eVenta;

/**
 * @fn int inicializarVentas(eVenta[], int)
 * @brief Esta función inicializa la data del array de ventas, poniendo todos los "estaVacio" en 1, para indicar que si está vacío.
 * @param ventas Dirección de memoria de la variable a inicializar.
 * @param largo Largo de la variable a inicializar.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int inicializarVentas(eVenta ventas[], int largo);
/**
 * @fn int darAltaVentas(eVenta[], int, eArticulo[], int)
 * @brief Esta función da de alta una venta pidiendo al usuario que ingrese el id de un articulo de la lista.
 * @param ventas Dirección de memoria de la variable en donde se va a guardar cada venta.
 * @param largoV Largo de la variable ventas.
 * @param articulos Variable que contiene los articulos.
 * @param largoA Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int darAltaVentas(eVenta ventas[], int largoV, eArticulo articulos[],
		int largoA);
/**
 * @fn int listarVentas(eVenta[], int, eArticulo[], int)
 * @brief Esta función lista todas las ventas hechas.
 * @param ventas Variable que contiene las ventas.
 * @param largoV Largo de la variable ventas.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int listarVentas(eVenta ventas[], int largoV);
/**
 * @fn int mostrarInformes(eVenta[], int, eArticulo[], int)
 * @brief Esta función muestra un submenu con opciones para mostrar la información de los articulos o ventas según rubro, fecha o articulo seleccionado.
 * @param ventas Variable que contiene las ventas.
 * @param largoV Largo de la variable ventas.
 * @param articulos Variable que contiene los articulos.
 * @param largoA Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int mostrarInformes(eVenta ventas[], int largoV, eArticulo articulos[],
		int largoA);

#endif /* VENTAS_H_ */
