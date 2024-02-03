#ifndef MAP_H_
#define MAP_H_

#include "_defines.h"

/*FUNCION MAPDEF
brief: Se encarga de crear la matriz donde las funciones actualizan el estado del juego
diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
return: (void)
*/
void map_def(const int diff, int mapa[][COL], int score);

#endif /* MAP_H_ */