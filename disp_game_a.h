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

/* FUNCIÓN DISPLAY_GAME
 * BRIEF: Se encarga de mostrar en pantalla cuando un disparo le pega a una barrera o a un alien
 * x: (int) Coordenada x donde ocurre el impacto
 * y: (int) Coordenada y donde ocurre el impacto
 * return: (int) En caso de haber un error devuelve -1
 *  */
void display_impact (int x, int y);

#endif /* DISP_GAME_A_H_ */
