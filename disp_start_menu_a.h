/*
 * disp_start_menu_a.c
 *
 *  Created on: Jan 7, 2024
 *      Author: bauti
 */

#ifndef DISP_START_MENU_A_C_
#define DISP_START_MENU_A_C_

#include <allegro5/allegro.h>

/* FUNCIÓN DISPLAY_INIT
 * BRIEF: Se encarga de inicializar el display y las librerías que se utilizan
 * return: (Puntero ALLEGRO_DISPLAY) En caso de haber un error devuelve NULL, caso contrario, puntero al display
 *  */
ALLEGRO_DISPLAY * display_init (void);

/* FUNCIÓN DISPLAY_START_MENU
 * BRIEF: Se encarga de mostrar el menú de inicio en pantalla
 * return: (int) Devuelve lo que seleccionó el jugador: 1= Empezar el juego, 2= Scoreboard, 3= Salior del juego
 *  */
int display_start_menu(void);

#endif /* DISP_START_MENU_A_C_ */
