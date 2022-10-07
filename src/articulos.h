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
} eRubro;

typedef struct {
	int idArticulo;
	char descripcion[31];
	int medida;
	int precio;
	eRubro rubroId;
	int estaVacio;
} eArticulo;

/**
 * @fn int inicializarArticulos(eArticulo[], int)
 * @brief Esta función inicializa la data del array de articulos, poniendo todos los "estaVacio" en 1, para indicar que si está vacío.
 * @param articulos Dirección de memoria de la variable a inicializar.
 * @param largo Largo de la variable a inicializar.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int inicializarArticulos(eArticulo articulos[], int largo);
/**
 * @fn int darAltaArticulos(eArticulo[], int)
 * @brief Esta función da de alta un producto.
 * @param articulos Dirección de memoria de la variable en donde se va a guardar cada articulo.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int darAltaArticulos(eArticulo articulos[], int largo);
/**
 * @fn int modificarArticulo(eArticulo[], int)
 * @brief Esta función pide el ID de un articulo y si lo encuentra muestra un submenu que permite modificar medida y/o precio del articulo.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int modificarArticulo(eArticulo articulos[], int largo);
/**
 * @fn int darBajaArticulo(eArticulo[], int)
 * @brief Esta función pide el ID de un articulo y si lo encuentra lo da de baja.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int darBajaArticulo(eArticulo articulos[], int largo);
/**
 * @fn int listarArticulos(eArticulo[], int)
 * @brief Esta función lista todos los articulos ordenandolos por rubro y descripción.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int listarArticulos(eArticulo articulos[], int largo);
/**
 * @fn int listarRubros(eArticulo[], int)
 * @brief Esta función lista todos los rubros que existen.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int listarRubros(eArticulo articulos[], int largo);
/**
 * @fn int buscarArticuloPorId(eArticulo[], int, int)
 * @brief Esta función busca un articulo por su id y retorna la posicion donde se ubica el articulo si lo encuentra.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @param id ID del articulo a buscar.
 * @return Retorna el numero de la posición del articulo si se encontró y -1 si no se encontró el articulo..
 * */
int buscarArticuloPorId(eArticulo articulos[], int largo, int id);
/**
 * @fn int existenArticulos(eArticulo[], int)
 * @brief Esta función indica si existen articulos.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si existen articulos y -1 si no existen.
 * */
int existenArticulos(eArticulo articulos[], int largo);
/**
 * @fn int mostrarPorRubro(eArticulo[], int)
 * @brief Esta función pide un rubro y lista todos los articulos que pertenezcan a este rubro.
 * @param articulos Variable que contiene los articulos.
 * @param largo Largo de la variable articulos.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int mostrarPorRubro(eArticulo articulos[], int largo);

#endif /* ARTICULOS_H_ */
