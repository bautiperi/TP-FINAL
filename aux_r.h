#ifndef AUX_R_H
#define AUX_R_H

#include "libs/disdrv.h"
#include "libs/joydrv.h"

/***********************************  FUNCIONES   ***********************************/

/*FUNCION LED_FLICK
brief: se encarga de hacer titilar un LED (sirve para los shields)
coor_shield: (dcoord_t) la coordenada del LED que recibio el impacto y tiene que titilar
return: void
*/
void led_flick(dcoord_t coor_shield);

/*FUNCION MULTP_FLICK
brief: se encarga de hacer titilar varios LEDs al mismo tiempo (sirve para el gamer y the final boss)
coor_shield: (dcoord_t) array de las coordenadas de los LEDs que tienen que titilar
cant: (int) cantidad de LEDs en el array
return: void
*/
void multp_flick(dcoord_t coords[], int cant);

// DEFINES
#define DELAY 300000 // 0.3 segundos

#define MAX_ITERATIONS 50

#endif