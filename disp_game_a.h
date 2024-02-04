#ifndef DISP_GAME_A_H_
#define DISP_GAME_A_H_

#include <allegro5/allegro.h>

// INCLUDES HEADER FILES
#include "_defines.h"

// PROTOTIPOS DE FUNCIONES

/* FUNCIÓN DISPLAY_GAME
 * BRIEF: Se encarga de actualizar la pantalla dentro del juego
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * display: (puntero ALLEGRO_DISPLAY) Puntero del display
 * return: (int) En caso de haber un error devuelve -1
 *  */
int display_game (const int mapa[][COL], ALLEGRO_DISPLAY * display);

#endif /* DISP_GAME_A_H_ */
