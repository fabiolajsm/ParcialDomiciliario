/*
 * validaciones.h
 *
 *  Created on: 1 oct. 2022
 *      Author: fsuarez
 */

#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_

/**
 * @fn int obtenerNumero(int*, char *, char *, int , int , int)
 * @brief Esta función pide un número entero y verifica que sea válido.
 * @param pResultado Dirección de memoria donde va a ser guardado el número después de validar.
 * @param mensaje Mensaje a mostrar cuando la función pida el número.
 * @param mensajeError Mensaje a mostrar si lo ingresado no es válido.
 * @param minimo Mínimo número a ingresar.
 * @param maximo Máximo número a ingresar.
 * @param intentos Número de intentos para que ingrese un número válido.
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int obtenerNumero(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int intentos);
int obtenerTexto(char *pResultado, int largo, char *mensaje, char *mensajeError,
		int tieneCondicion, int minCaracteres, int maxCaracteres, int intentos);

#endif /* VALIDACIONES_H_ */
