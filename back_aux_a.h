/*
 * back_aux_a.h
 *
 *  Created on: Jan 22, 2024
 *      Author: bauti
 */

#ifndef BACK_AUX_A_H_
#define BACK_AUX_A_H_

#include "map.h"

/* FUNCIÓN SWAP
 * BRIEF: Cambia el contenido de dos celdas de la matriz
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * x1: (int) Coordenada x del primer elemento de la matriz a cambiar
 * y1: (int) Coordenada y del primer elemento
 * x2: (int) Coordenada x del segundo elemento a cambiar
 * y2: (int) Coordenada y del segundo elemento
 * return: (void)
 */
void swap(int mapa[][COL], int x1, int y1, int x2, int y2);

#endif /* BACK_AUX_A_H_ */
