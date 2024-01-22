/*
 * back_store_a.h
 *
 *  Created on: Jan 22, 2024
 *      Author: bauti
 */

#ifndef BACK_SCORE_A_H_
#define BACK_SCORE_A_H_

#include "map.h"

/* FUNCIÓN SCORE_UPDATER
 * BRIEF: Actualiza el score actual del jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void score_updater (int mapa[][COL], int idetifier);

/* FUNCIÓN GAMER_MOVEMENT
 * BRIEF: Guarda el score del jugador en un archivo, ordenandolo de mayor a menor puntaje
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void score_saver (int mapa[][COL]);

#endif /* BACK_STORE_A_H_ */
