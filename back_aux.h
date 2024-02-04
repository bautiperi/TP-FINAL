#ifndef BACK_AUX_H_
#define BACK_AUX_H_

// INCLUDE HEADER FILES
#include "_defines.h"

// PROTOTIPOS DE FUNCIONES

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

/* FUNCIÓN ENEMY_CHECKER
 * BRIEF: Verifica que la celda tenga o no enemigos
 * x: (int) Coordenada x de la celda a analizar
 * y: (int) Coordenada y de la celda a analizar
 * return: (int) Valor de verdad de la proposición
 */
int enemy_checker(int x, int y, const int mapa[][COL]);

/* FUNCIÓN IMPACT_UPDATER
 * BRIEF: Función encargada de declarar al front que ocurrió un disparo
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void *)
 */
void *impact_updater(void *arg);

#endif /* BACK_AUX_H_ */