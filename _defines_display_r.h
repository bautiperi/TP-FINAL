#ifndef _DEFINES_DISPLAY_R_H
#define _DEFINES_DISPLAY_R_H

#include <stdint.h>

//DEFINES DISPLAY
#define DISPLAY_SIZE 960
#define DISPLAY_CENTRE DISPLAY_SIZE /2
#define SCALER 30
#define POS_X(x) ((x)* SCALER - SCALER/2)
#define POS_Y(y) ((y) * SCALER)

//DEFINES FONTS
#define FONT_SIZE 35
#define TITLE_SIZE 150
#define OPTIONS_SIZE 75

//DEFINES PARA MENU
#define TITLE_COLOR 254, 70, 165
#define BUTTON_COLOR 250, 218, 221
#define BUTTON_SEL_COLOR 233, 65, 150

// OPCIONES MENU
#define NEW_GAME 1
#define MAIN_MENU 2
#define HIGHSCORE 2
#define DIFFICULTY 3
#define QUIT 4

#endif /* _DEFINES_DISPLAY_R_H */

/*
FLAGS DEL JUEGO
mapa[0][4] es un flag que indica el momento de juego
mapa[0][4] = 0 -> en el juego
mapa[0][4]  = 1 -> en el menu
mapa[0][4]  = 2 -> menu principal

mapa[0][6]  es un flag para la visualización de la dirección
1  -> derecha
-1- > izquierda
*/