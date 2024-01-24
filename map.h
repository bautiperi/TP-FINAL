#ifndef MAP_H_
#define MAP_H_

#include "defines.h"
#include <stdio.h>
#include "ships.h"

/*FUNCION MAPDEF
brief: Se encarga de crear la matriz donde las funciones actualizan el estado del juego
diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
return: (void)
*/
void map_def(const int diff, int mapa[][COL]);

#endif /* MAP_H_ */