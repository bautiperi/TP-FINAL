
#ifndef OBJ_R_H
#define OBJ_R_H

#include "libs/disdrv.h"
#include "libs/joydrv.h"

/***********************************  GAMER   ***********************************/

/*FUNCION GAMER_VIS
brief: se encarga de mostrar al jugador
ubi: (dcoord_t) coordenadas del LED de abajo a la izq
return: void
*/
void gamer_vis(dcoord_t ubi);

/***********************************  ALIENS   ***********************************/

/*******************************  THE FINAL BOSS  *********************************/

/*FUNCION FINAL_BOSS_VIS
brief: se encarga de mostrar al final boss
ubi: (dcoord_t) coordenadas del LED de arriba a la izq
return: void
*/
void final_boss_vis(dcoord_t ubi);

/***********************************  LIVES   ***********************************/

/*FUNCION SHIELDS_VIS
brief: se encarga de encender las vidas segun la cantidad indicada
coor: (int) cantidad de vidas
return: void
*/
void lives_vis(int cant);

/***********************************  SHIELDS  ***********************************/

/*FUNCION SHIELDS_VIS
brief se encarga de encender un escudo
coor: (dcoord_t) coordenada del led de abajo a la izquierda del shield
return: void
*/
void shields_vis(dcoord_t coor);

/*FUNCION SHIELDS_LIFE
brief: se encarga de la visualizacion de colisiones con los escudos
life_of_shield: (int) numero de colisiones hacia ese escudo y ese LED (a las 8 colisiones se muere el escudo, cada LED tiene 2 vidas)
coor_of_shield: (dcoord_t) escudo al que se le pego
return: void
*/
void shields_life(int life_of_shield, dcoord_t coor_of_shield);


#define DELAY 300000 //0.3 segundos

#define MAX_ITERATIONS 50

#endif