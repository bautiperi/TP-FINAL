#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

// TAMAÑO DE LA MATRIZ
#define COL 16
#define FIL 16

// DIFICULTAD
#define RASP 0
#define EASY 1

// DEFINICIÓN DE COORDENADAS GENERICAS
typedef struct
{
    uint8_t x;
    uint8_t y;
} coord_t;

// DEFINES TIEMPOS DE FLICKS
#define DELAY 300000 // 0.3 segundos
#define MAX_ITERATIONS 50

// VALOR DE OBJETOS
#define BOSS 5
#define ALIEN_4 4
#define ALIEN_3 3
#define ALIEN_2 2
#define JUGADOR 1
#define SPACE 0
#define BARRIER -1
#define FIRE_PL 6
// JOYSTICK
#define THRESHOLD 20 // Límite a partir del cual se mueve el LED encendido

// FLAGS
#define STATUS mapa[0][4]
#define FLICK_OPTION mapa[0][6]
#define END_GAME mapa[6][0]

// MAPA
#define SPACE 0
#define BARRIER -1

// JUGADOR
#define SPAWN_POINT mapa[15][6]
#define JUGADOR 1

// DISPAROS
#define FIRE_PL 6
#define FIRE_EN 7

// DEFINICIONES DE VALORES ESPECÍFICOS
#define LIVES mapa[0][COL - 1]
#define SCORE mapa[0][COL - 2]
#define IMPACT mapa[0][COL - 5]
#define IMPACT_X mapa[0][COL - 4]
#define IMPACT_Y mapa[0][COL - 3]


#endif /* DEFINES_H */
