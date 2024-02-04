#ifndef MAP_H_
#define MAP_H_

//INCLUDE HEADER FILES
#include "_defines.h"

// PROTOTIPO DE FUNCIONES

/*FUNCION MAPDEF
brief: Se encarga de crear la matriz donde las funciones actualizan el estado del juego
diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
mapa: (int) es la matriz donde se desarrolla el juego
score: (int) puntaje
return: (void)
*/
void map_def(const int diff, int mapa[][COL], int score);

#endif /* MAP_H_ */