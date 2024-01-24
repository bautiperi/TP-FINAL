#ifndef CONECTION_B_R_H
#define CONECTION_B_R_H

#include "defines.h"
#include "map.h"
#include "obj_r.h"
#include "aux_r.h"

/*FUNCION OBJ_VIS
brief: se encarga de analizar la matriz y llamar a las funciones pertinentes
mapa: (int **) matriz a analizar
vidas: (int)
return: void
*/
void obj_vis(int mapa[][COL], int vidas);

/*FUNCION DETECT_COLLISION
brief: dependiendo que objeto es impactado se llama a la funcion correspondiente para su display
coord: (coord_t) coordenada de abajo a la izquierda en donde se produce el impacto
obj: (int) numero que identifica el objeto impactado
diff: (int) indica la dificultad y si es para raspberry o allegro
mapa: (int **) matriz a analizar
return: void
*/
void display_collision(coord_t coord, int obj, int diff);

#endif /* CONECTION_B_R_H */