#ifndef BACK_GAME_A_H_
#define BACK_GAME_A_H_

#include "map.h"

/* FUNCIÓN ALIEN_MOVEMENT_H
 * BRIEF: mueve horizontalmente a los aliens
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * fil: (int) fila inicial
 * col: (int) columna inicial
 * return: (void)
 */
void alien_movement_h(int mapa[][COL], int fil, int col);

/* FUNCIÓN ALIEN_MOVEMENT_V
 * BRIEF: mueve verticalmente a los aliens
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * fil: (int) fila inicial
 * col: (int) columna inicial
 * return: (void)
 */
void alien_movement_v(int mapa[][COL], int fil, int col);

#endif /* BACK_GAME_A_H_ */