#ifndef BACK_SCORE_H_
#define BACK_SCORE_H_

#include "_defines.h"

/* FUNCIÓN SCORE_UPDATER
 * BRIEF: Actualiza el score actual del jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void score_updater(int mapa[][COL], int idetifier);

/* FUNCIÓN SCORE_SAVER
 * BRIEF: Guarda el score del jugador en un archivo, ordenandolo de mayor a menor puntaje
 * score: (int) Es el score del juego actual
 * return: (int) Devuelve 0 si no hubo errores y se pudo guardar el score del jugador, -1 caso contrario. Devuelve 1 si el jugador entró en el top
 */
int score_saver(int score);

// Estructura donde se guardan los nombres y scores de jugadores
typedef struct
{
    char name[50];
    int score;
} player_t;

#endif /* BACK_STORE_A_H_ */