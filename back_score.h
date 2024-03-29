#ifndef BACK_SCORE_H_
#define BACK_SCORE_H_

// INCLUDE HEADER FILES
#include "_defines.h"

// Estructura donde se guardan los nombres y scores de jugadores
typedef struct
{
    char name[50];
    int score;
} player_t;

// PROTOTIPO DE FUNCIONES

/* FUNCIÓN SCORE_UPDATER
 * BRIEF: Actualiza el score actual del jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * identifier: (int) tipo de enemigo al que se le disparó
 * return: (void)
 */
void score_updater(int mapa[][COL], int idetifier);

/* FUNCIÓN SCORE_SAVER
 * BRIEF: Guarda el score del jugador en un archivo, ordenandolo de mayor a menor puntaje
 * score: (int) Es el score del juego actual
 * return: (int) Devuelve 0 si no hubo errores y se pudo guardar el score del jugador, -1 caso contrario. Devuelve 1 si el jugador entró en el top
 */
int score_saver(int score);

/* FUNCIÓN LIFE_UPDATER
 * BRIEF: Actualiza la cantidad de vidas que tiene el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) Devuelve 0 si el jugador todavía tiene vidas, caso contrario devuelve 1
 */
int life_updater(int mapa[][COL]);

#endif /* BACK_STORE_A_H_ */