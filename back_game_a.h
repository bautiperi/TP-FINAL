#ifndef BACK_GAME_A_H_
#define BACK_GAME_A_H_

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

/* FUNCIÓN GAMER_MOVEMENT
 * BRIEF: mueve el gamer en la matriz
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * dir: (int) Indica la direccion del movimiento (si dir > 0 => hacia der \\\ si dir < 0 => hacia izq \\\ si dir = 0 o 0 <= x + dir < COL no se mueve)
 * return: (void)
 */
void gamer_movement(int mapa[][COL], int dir);

/* FUNCIÓN GAMER_FIRE
 * BRIEF: Es llamada al momento del que el jugador dispara, se encarga de "llevar" el disparo por el mapa y detectar si hubo una colisión
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void * gamer_fire(void * arg);

void * enemy_fire(void * arg);

//Declaración de variable global (flag)
extern int flag_game_update;

#endif /* BACK_GAME_A_H_ */
