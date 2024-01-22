#ifndef BACK_GAME_A_H_
#define BACK_GAME_A_H_

#include "map.h"

/* FUNCIÓN ALIEN_MOVEMENT
 * BRIEF: mueve horizontalmente a los aliens
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void alien_movement(int mapa[][COL]);

/* FUNCIÓN FINAL_BOSS_CREATION
 * BRIEF: crea al final boss y llama a la funcion de su movimiento
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void final_boss_creation(int mapa[][COL]);

/* FUNCIÓN GAMER_MOVEMENT
 * BRIEF: mueve el gamer en la matriz
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * dir: (int) Indica la direccion del movimiento (si dir > 0 => hacia der \\\ si dir < 0 => hacia izq \\\ si dir = 0 o 0 <= x + dir < COL no se mueve)
 * return: (void)
 */
void gamer_movement(int mapa[][COL], int dir);

#endif /* BACK_GAME_A_H_ */
