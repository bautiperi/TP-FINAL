#ifndef DISP_SCOREBOARD_A_H_
#define DISP_SCOREBOARD_A_H_

// PROTOTIPOS DE FUNCIONES

/* FUNCIÓN DISPLAY_SCOREBOARD
 * BRIEF: Se encarga de mostrar los jugadores que forman parte del scoreboard y se encarga de que funcione
 * la interacción con el usuario dentro del scoreboard
 * return: (void)
 *  */
int display_scoreboard (void);

/* FUNCIÓN DISP_NAME_AND_CHAR
 * BRIEF: Se encarga de mostrar una pantalla donde el jugador debe ingresar su nombre y luego de elegir su personake Barbie
 * return: (int) Devuelve 0 cuando el jugador ingresó el nombre
 *  */
int disp_name_and_char (void);

/* FUNCIÓN DISPLAY_GAME_OVER
 * BRIEF: Se encarga de mostrar en pantalla cuando el jugador perdió, también muestra su score final y si entró al scoreboard
 * score: (int) Score final del jugador
 * return: (void)
 *  */
void display_game_over (const int score);

#endif /* DISP_SCOREBOARD_A_H_ */
