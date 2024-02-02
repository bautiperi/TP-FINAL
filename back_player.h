/*
 * back_player.h
 *
 *  Created on: Jan 28, 2024
 *      Author: bauti
 */

#ifndef BACK_PLAYER_H_
#define BACK_PLAYER_H_

#include "_defines.h"

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
void *gamer_fire(void *arg);

/* FUNCIÓN LIFE_UPDATER
 * BRIEF: Actualiza la cantidad de vidas que tiene el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) Devuelve 0 si el jugador todavía tiene vidas, caso contrario devuelve 1
 */
int life_updater(int mapa[][COL]);

// VARIABLES EXTERNAS
// Variable global de main.c (flag para threads)
extern int flag_game_update;
#ifndef RASPBERRY
extern int is_shooting;
#endif

#endif /* BACK_PLAYER_H_ */