/*
 * articulos.h
 *
 *  Created on: 1 oct. 2022
 *      Author: fsuarez
 */

#ifndef ARTICULOS_H_
#define ARTICULOS_H_

typedef struct {
	int idRubro; // Se va a inicializar en 1000
	char descripcion[31];
} rubro;

typedef struct {
	int idArticulo;
	char descripcion[31];
	int medida;
	int precio;
	int rubroId;
	int estaVacio;
} articulo;

/**
 * @fn int inicializarArticulos(articulo[], int)
 * @brief Esta función inicializa la data del array de articulos, poniendo todos los "estaVacio" en 1, para indicar que si está vacío.
 * @param articulos Dirección de memoria de la variable a inicializar.
 * @param largo Largo de la variable a inicializar.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int inicializarArticulos(articulo articulos[], int largo);
/**
 * @fn int darAltaArticulos(articulo[], int, int*)
 * @brief Esta función da de alta un producto.
 * @param articulos Dirección de memoria de la variable en donde se va a guardar cada articulo.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int darAltaArticulos(articulo articulos[], int largo);
/**
 * @fn int modificarArticulo(articulo[], int, int)
 * @brief Esta función pide el ID de un articulo y si lo encuentra muestra un submenu que permite modificar medida y/o precio del articulo.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int modificarArticulo(articulo articulos[], int largo);
/**
 * @fn int darBajaArticulo(articulo[], int, int)
 * @brief Esta función pide el ID de un articulo y si lo encuentra lo da de baja.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int darBajaArticulo(articulo articulos[], int largo);
/**
 * @fn int listarArticulos(articulo[], int, int)
 * @brief Esta función lista todos los articulos ordenandolos por rubro y descripción.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int listarArticulos(articulo articulos[], int largo);

#endif /* ARTICULOS_H_ */
