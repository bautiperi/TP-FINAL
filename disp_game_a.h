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
 * score: (int) Recibe el score del juego actual para visualizar en pantalla
 * lives: (int) Recibe la cantidad de vidas que tiene el jugador actualmente para mostrarlo en pantalla
 * return: (int) En caso de haber un error devuelve -1
 *  */
int display_game (const int mapa[][COL], int score, int lives);

#endif /* DISP_GAME_A_H_ */