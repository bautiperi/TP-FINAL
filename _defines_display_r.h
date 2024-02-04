#ifndef _DEFINES_DISPLAY_R_H
#define _DEFINES_DISPLAY_R_H

#include <stdint.h>

// DEFINES TIEMPOS DE FLICKS
#define DELAY 300000 // 0.3 segundos
#define MAX_ITERATIONS 50

// JOYSTICK
#define THRESHOLD 40 // Límite a partir del cual se mueve el LED encendido

// FLAGS
#define STATUS mapa[0][4]
#define SELECT_OPTION mapa[0][5]
#define DIRECCION mapa[0][6]
#define CLOSE_GAME mapa[6][0]

#endif /* _DEFINES_DISPLAY_R_H */

/*
FLAGS DEL JUEGO
STATUS mapa[0][4]
STATUS es un flag que indica el momento de juego
STATUS = 0 -> en el juego
STATUS = 1 -> en el menu
STATUS = 2 -> menu principal
STATUS = 3 -> muestra el score

DIRECCION mapa[0][6]  es un flag para la visualización de la dirección
DIRECCION = 1  -> derecha
DIRECCION = -1- > izquierda
*/
