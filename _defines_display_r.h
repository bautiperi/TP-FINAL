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
#define FLICK_OPTION mapa[0][6]
#define CLOSE_GAME mapa[6][0]

#endif /* _DEFINES_DISPLAY_R_H */
