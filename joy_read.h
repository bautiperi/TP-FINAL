#ifndef JOY_READ_H
#define JOY_READ_H

#include "joydrv.h"
#include "back_game_a.h"
#include "menu_r.h"
#include "conection_b_r.h"
#include "defines.h"

/* FUNCIÓN JOY_MOVEMENT
 * BRIEF: Registra el movimiento del joystick
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 */
void joy_movement(int mapa[][COL]);

#endif /* JOY_READ_H */