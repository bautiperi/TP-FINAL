#ifndef BACK_GAME_A_H_
#define BACK_GAME_A_H_

#include "map.h"

/* FUNCIÓN ALIEN_MOVEMENT_H
 * BRIEF: mueve horizontalmente a los aliens
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void alien_movement_h(int mapa[][COL]);

/* FUNCIÓN ALIEN_MOVEMENT_H
 * BRIEF: mueve horizontalmente a el final boss
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void final_boss_movement(mapa[][COL]);

#endif /* BACK_GAME_A_H_ */