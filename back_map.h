#ifndef MAP_H_
#define MAP_H_

#include "_defines.h"

/*FUNCION MAPDEF
brief: Se encarga de crear la matriz donde las funciones actualizan el estado del juego
diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
return: (void)
*/
void map_def(const int diff, int mapa[][COL], int score);

/*FUNCION SHIPS_CREATE
 * BRIEF: Se encarga de posicionar los enemigos en el mapa
 * diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * Return: (void)
 */

#endif /* MAP_H_ */
