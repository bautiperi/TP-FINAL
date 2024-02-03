#ifndef MENU_R_H
#define MENU_R_H

#include "_defines.h"

/***********************************  VISUALIZACION  ***********************************/
/*FUNCION MENU_VIS
brief: se encarga de la visualizacion del menu de juego
mapa: (matriz de int) ubicacion de los objetos
return: void
*/
void menu_vis(int mapa[][COL]);

/***********************************  VISUALIZACION  ***********************************/
/*FUNCION MENU_PRINCIPAL_VIS
brief: se encarga de la visualizacion del menu principal
mapa: (matriz de int) ubicacion de los objetos
return: void
*/
void menu_principal_vis(int mapa[][COL]);

#endif /* MENU_R_H */