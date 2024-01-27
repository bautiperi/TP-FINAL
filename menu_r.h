#ifndef MENU_R_H
#define MENU_R_H

#include "defines.h"
#include "disdrv.h"
#include "joydrv.h"
#include "aux_r.h"

/***********************************  VISUALIZACION   ***********************************/
/*FUNCION MENU_VIS
brief: se encarga de la visualizacion de colisiones con los escudos
ubi: (joyinfo_t) ubicacion del joystick
return: void
*/
void menu_vis(int mapa[][COL]);

void menu_principal_vis(int mapa[][COL]);

#endif /* MENU_R_H */