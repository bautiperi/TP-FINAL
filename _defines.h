#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

#ifndef RASP

//TAMAÑO DE LA MATRIZ
#define COL 32
#define FIL 32

//DIFICULTAD
#define RASP 0
#define EASY 1

//CONSTANTES
#define SPACE 0

// VALOR DE OBJETOS
#define BOSS 5
#define ALIEN_4 4
#define ALIEN_3 3
#define ALIEN_2 2
#define JUGADOR 1
#define SPACE 0
#define BARRIER -1
#define FIRE_PL 6
#define FIRE_EN 7

//DEFINICIÓN DE COORDENADAS

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
