#ifndef MENU_R_H
#define MENU_R_H

// INCLUDES HEADER FILES
#include "_defines.h"

// PROTOTIPOS DE FUNCIONES

/***********************************  VISUALIZACION  ***********************************/
/*FUNCION MENU_VIS
brief: se encarga de la visualizacion del menu de juego (en pausa)
mapa: (matriz de int) ubicacion de los objetos
return: void
*/
void menu_vis(int mapa[][COL]);


/*FUNCION MENU_PRINCIPAL_VIS
brief: se encarga de la visualizacion del menu principal
mapa: (matriz de int) ubicacion de los objetos
return: void
*/
void menu_principal_vis(int mapa[][COL]);

#endif /* MENU_R_H */