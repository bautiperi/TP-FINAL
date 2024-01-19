/*
 * map.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Grupo 5
 */

#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>

//TAMAÑO DE LA MATRIZ
#define COL 32
#define FIL 32

//DIFICULTAD
#define RASP 0
#define EASY 1

//CONSTANTES
#define SPACE 0

//DEFINICIÓN DE COORDENADAS

typedef struct {
	unsigned int x;
	unsigned int y;
} coord_t;

/*FUNCION MAPDEF
brief: Se encarga de crear la matriz donde las funciones actualizan el estado del juego
diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
return: (void)
*/
void map_def(const int diff, int mapa [][COL]);

#endif /* MAP_H_ */
