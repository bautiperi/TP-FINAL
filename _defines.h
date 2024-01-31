#ifndef _DEFINES_H
#define _DEFINES_H

#include <stdint.h>

#ifndef RASPBERRY

// TAMAÑO DE LA MATRIZ
#define COL 32
#define FIL 32

#define R_BORDER COL - 2
#define L_BORDER 1

// JUGADOR
#define POS_Y_PL 28
#define SPAWN_POINT mapa[POS_Y_PL][COL / 2 - 1]

#else

// TAMAÑO DE LA MATRIZ
#define COL 16
#define FIL 16

#define R_BORDER COL - 1
#define L_BORDER 0

// JUGADOR
#define POS_Y_PL FIL - 1
#define SPAWN_POINT mapa[POS_Y_PL][COL / 2 - 1]

#endif /* RASP */

// DIFICULTAD
#define RASP 0
#define NORMAL 1
#define HARD 2
#define EXTREME 3

// JUGADOR
#define JUGADOR 1

// DISPAROS
#define FIRE_PL 6
#define FIRE_EN 7

// VALOR DE ENEMIGOS
#define BOSS 5
#define ALIEN_4 4
#define ALIEN_3 3
#define ALIEN_2 2

// MAPA
#define SPACE 0
#define BARRIER -1

// DEFINICIONES DE VALORES ESPECÍFICOS
#define DIFICULTAD mapa[0][0]
#define LIVES mapa[0][COL - 1]
#define SCORE mapa[0][COL - 2]
#define IMPACT mapa[0][COL - 5]
#define IMPACT_X mapa[0][COL - 4]
#define IMPACT_Y mapa[0][COL - 3]

// DEFINICIÓN DE COORDENADAS GENERICAS
typedef struct
{
    uint8_t x;
    uint8_t y;
} coord_t;

#endif /* DEFINES_H */
