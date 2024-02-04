#ifndef DISP_START_MENU_A_C_
#define DISP_START_MENU_A_C_

// LIBRERÍAS
#include <allegro5/allegro.h>

// PROTOTIPOS DE FUNCIONES

/* FUNCIÓN DISPLAY_INIT
 * BRIEF: Se encarga de inicializar el display y las librerías que se utilizan
 * return: (Puntero ALLEGRO_DISPLAY) En caso de haber un error devuelve NULL, caso contrario, puntero al display
 *  */
ALLEGRO_DISPLAY * display_init (void);

/* FUNCIÓN DISPLAY_START_MENU
 * BRIEF: Se encarga de mostrar el menú de inicio en pantalla
 * dificultad: (puntero a int) Es la variable donde se almacena la dificultad en main (no en el mapa)
 * display: (Puntero a ALLEGRO_DISPLAY) Puntero que devuelve la función display_init
 * return: (int) Devuelve lo que seleccionó el jugador: 1= Empezar el juego, 2= Scoreboard, 3= Salior del juego
 *  */
int display_start_menu(int * dificultad, ALLEGRO_DISPLAY * display);

#endif /* DISP_START_MENU_A_C_ */
