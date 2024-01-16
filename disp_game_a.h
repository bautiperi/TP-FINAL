/*
 * disp_a.h
 *
 *  Created on: Jan 5, 2024
 *      Author: grupo 5
 */

#ifndef DISP_GAME_A_H_
#define DISP_GAME_A_H_

#include "map.h"

/* FUNCIÓN DISPLAY_GAME
 * BRIEF: Se encarga de actualizar la pantalla dentro del juego
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) En caso de haber un error devuelve -1
 *  */
int display_game (const int mapa[][COL]);

#endif /* DISP_GAME_A_H_ */
