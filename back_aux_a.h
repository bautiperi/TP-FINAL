/*
 * back_aux_a.h
 *
 *  Created on: Jan 22, 2024
 *      Author: bauti
 */

#ifndef BACK_AUX_A_H_
#define BACK_AUX_A_H_

#include "_defines.h"

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

/* FUNCIÓN CELL_CMP
 * BRIEF: Compara si la celda de las coordenadas nro 2, coinciden con lo buscado, y si en la coordenada nro 1 hay un enemigo
 * x1: (int) Coordenada x del primer elemento
 * y1: (int) Coordenada y del primer elemento
 * x2: (int) Coordenada x del segundo elemento
 * y2: (int) Coordenada y del segundo elemento
 * return: (int) Valor de verdad de la proposición
 */
int enemy_checker (int x, int y, const int mapa[][COL]);

#endif /* BACK_AUX_A_H_ */
