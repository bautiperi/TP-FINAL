#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

#ifndef RASP

// TAMAÑO DE LA MATRIZ
#define COL 32
#define FIL 32

// MAPA
#define SPACE 0
#define BARRIER -1

// DIFICULTAD
#define RASP 0
#define EASY 1

// JUGADOR
#define POS_Y_PL 28
#define SPAWN_POINT mapa[POS_Y_PL][COL/2 -1]
#define JUGADOR 1

// VALOR DE ENEMIGOS
#define BOSS 5
#define ALIEN_4 4
#define ALIEN_3 3
#define ALIEN_2 2

// DISPAROS
#define FIRE_PL 6
#define FIRE_EN 7

// DEFINICIONES DE VALORES ESPECÍFICOS
#define DIFICULTAD mapa[0][0]
#define LIVES mapa[0][COL-1]
#define SCORE mapa[0][COL-2]
#define IMPACT mapa[0][COL-5]
#define IMPACT_X mapa[0][COL-4]
#define IMPACT_Y mapa[0][COL-3]

// DEFINICIÓN DE COORDENADAS
typedef struct {
	unsigned int x;
	unsigned int y;
} coord_t;

#else

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

#endif /* RASP */

#endif /* DEFINES_H */
