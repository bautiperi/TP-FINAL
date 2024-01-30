/*
 * map.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Grupo 5
 */

#ifndef BACK_MAP_H_
#define BACK_MAP_H_

#include <stdio.h>

#include "_defines.h"

/*FUNCION MAPDEF
brief: Se encarga de crear la matriz donde las funciones actualizan el estado del juego
diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
score: (int) Score del jugador (Al inicializar por primera vez, solo pasarle 0)
return: (void)
*/
void map_def(const int diff, int mapa [][COL], int score);

#endif /* BACK_MAP_H_ */