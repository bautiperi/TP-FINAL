/*
 * map.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Grupo 5
 */

#ifndef MAP_H_
#define MAP_H_

//TAMAÑO DE LA MATRIZ
#define COL 16
#define FIL 16

//DIFICULTAD
#define EASY 1

//CONSTANTES
#define SPACE 0
#define BARRIER -2
#define BRO_BARRIER -1

/*FUNCION MAPDEF
brief: Se encarga de crear la matriz donde las funciones actualizan el estado del juego
diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
return: (void)
*/
void mapdef(const int diff, int mapa [][COL]);

#endif /* MAP_H_ */
