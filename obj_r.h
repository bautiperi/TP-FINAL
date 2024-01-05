
#ifndef OBJ_R_H
#define OBJ_R_H

#include "libs/disdrv.h"
#include "libs/joydrv.h"

/***********************************  LIVES   ***********************************/

/*FUNCION SHIELDS_VIS
brief: se encarga de encender las vidas segun la cantidad indicada
coor: (int) cantidad de vidas
return: void
*/
void lives_vis(int cant);

/***********************************  SHIELDS  ***********************************/

/*FUNCION SHIELDS_VIS
brief: se encarga de encender un escudo
coor: (dcoord_t) coordenada del led de abajo a la izquierda del shield
return: void
*/
void shields_vis(dcoord_t coor);

/*FUNCION SHIELDS_LIFE
brief: se encarga de las vidas de los escudos
life_of_shield: (int) numero de colisiones hacia ese escudo (a las 10 colisiones se muere el escudo)
coor_of_shield: (dcoord_t) escudo al que se le pego
return: void
*/
void shields_life(int life_of_shield, dcoord_t coor_of_shield);

#endif