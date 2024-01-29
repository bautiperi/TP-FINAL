/*
 * disp_scoreboard_a.h
 *
 *  Created on: Jan 10, 2024
 *      Author: bauti
 */

#ifndef DISP_SCOREBOARD_A_H_
#define DISP_SCOREBOARD_A_H_

/* FUNCIÓN DISPLAY_SCOREBOARD
 * BRIEF: Se encarga de mostrar los jugadores que forman parte del scoreboard y se encarga de que funcione
 * la interacción con el usuario dentro del scoreboard
 * return: (void)
 *  */
int display_scoreboard (void);

/* FUNCIÓN DISPLAY_SCORE_NAME
 * BRIEF: Se encarga de mostrar una pantalla donde el jugador debe ingresar su nombre
 * return: (int) Devuelve 0 cuando el jugador ingresó el nombre
 *  */
int display_score_name (void);

#endif /* DISP_SCOREBOARD_A_H_ */
