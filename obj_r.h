
#ifndef OBJ_R_H
#define OBJ_R_H

// INCLUDES NECESARIOS PARA PROTOTIPOS
#include "_defines.h"
#include "disdrv.h"

/***********************************  GAMER   ***********************************/

/*FUNCION GAMER_VIS
brief: se encarga de mostrar al jugador
ubi: (dcoord_t) coordenadas del LED de abajo al medio
return: void
*/
void gamer_vis(dcoord_t ubi);

/***********************************  ALIENS   ***********************************/

/*FUNCION ALIENS_VIS
brief: se encarga de mostrar a los aliens
coor_inicial: (dcoord_t) coordenadas del LED a prender
return: void
*/
void aliens_vis(dcoord_t coor_inicial);

/*******************************  THE FINAL BOSS  *********************************/

/*FUNCION FINAL_BOSS_VIS
brief: se encarga de mostrar al final boss
ubi: (dcoord_t) coordenadas del LED de arriba al medio
mapa: (matriz de int) matriz con la informacion de los objetos a mostrar
return: void
*/
void final_boss_vis(dcoord_t ubi, int mapa[][COL]);

/***********************************  LIVES   ***********************************/

/*FUNCION SHIELDS_VIS
brief: se encarga de encender las vidas segun la cantidad indicada
cant: (int) cantidad de vidas
return: void
*/
void lives_vis(int cant);

/***********************************  SHIELDS  ***********************************/

/*FUNCION SHIELDS_VIS
brief se encarga de encender un escudo
coor: (dcoord_t) coordenada del led a prender
return: void
*/
void shields_vis(dcoord_t coor);

/***********************************  GAME OVER   ***********************************/

/*FUNCION GAME_OVER
brief: apaga los leds del display y genera una cara triste indicando la finalizacion del juego
no recibe ni devuleve nada
*/
void game_over(void);

#endif /* OBJ_R_H */