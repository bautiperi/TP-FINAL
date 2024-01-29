#ifndef BACK_ENEMY_H_
#define BACK_ENEMY_H_

#include "_defines.h"

/* FUNCIÓN ALIEN_MOVEMENT
 * BRIEF: mueve horizontalmente a los aliens
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void * alien_movement (void * arg);

/* FUNCIÓN FINAL_BOSS_CREATION
 * BRIEF: crea al final boss y llama a la funcion de su movimiento
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void * final_boss_creation(void * arg);

void * enemy_fire(void * arg);

#endif /* BACK_ENEMY_H_ */
