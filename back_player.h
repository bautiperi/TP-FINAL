#ifndef BACK_PLAYER_H_
#define BACK_PLAYER_H_

// INCLUDE HEADER FILES
#include "_defines.h"

// PROTOTIPOS DE FUNCIONES

/* FUNCIÓN GAMER_MOVEMENT
 * BRIEF: mueve el gamer en la matriz
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * dir: (int) Indica la direccion del movimiento (si dir > 0 => hacia der \\\ si dir < 0 => hacia izq \\\ si dir = 0 o 0 <= x + dir < COL no se mueve)
 * return: (void)
 */
void gamer_movement(int mapa[][COL], int dir);

/* FUNCIÓN GAMER_FIRE
 * BRIEF: Es llamada al momento del que el jugador dispara, se encarga de "llevar" el disparo por el mapa y detectar si hubo una colisión
 * arg: (*void) puntero a la matriz donde se desarrolla el juego
 * return: (void)
 */
void *gamer_fire(void *arg);

#endif /* BACK_PLAYER_H_ */