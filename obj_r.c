
// INCLUDES
#include "obj_r.h"

// PROTOTYPES
static void led_flick(int grado, dcoord_t coor_shield);

// guardan las coordenadas del led de abajo a la izquierda
dcoord_t shield1 = {1, 4}, shield2 = {5, 4}, shield3 = {9, 4}, shield4 = {13, 4};

/***********************************  LIVES   ***********************************/

void lives_vis(int cant)
{
    dcoord_t first_life = {0, 0}, second_life = {1, 0}, third_life = {2, 0};
    switch (cant)
    {
    case 0:
        disp_write(first_life, D_OFF);
        break;
    case 1:
        disp_write(second_life, D_OFF);
        disp_update();
        break;
    case 2:
        disp_write(third_life, D_OFF);
        disp_update();
        break;
    default:
        disp_write(third_life, D_ON);
        disp_write(second_life, D_ON);
        disp_write(first_life, D_ON);
        disp_update();
        break;
    }
}

/***********************************  SHIELDS  ***********************************/

void shields_vis(dcoord_t coor)
{
    disp_write(coor, D_ON); // prendo led de abajo a la izq
    coor.y++;
    disp_write(coor, D_ON); // prendo led de arriba a la izq
    coor.x++;
    disp_write(coor, D_ON); // prendo led de arriba a la der
    coor.y--;
    disp_write(coor, D_ON); // prendo led de abajo a la der
    disp_update();
}

void shields_life(int life_of_shield, dcoord_t coor_of_shield)
{
    dcoord_t coor = coor_of_shield;
    // me fijo cuantas fueron las colisiones y voy haciendo titilar a los leds o los apago
    if (0 < life_of_shield <= 2)
    { // del 1 al 2 quedan cuatro leds prendidos (titila arr izq)
        coor.y = coor_of_shield.y + 1;
        led_flick(life_of_shield, coor);
    }
    else if (life_of_shield <= 4)
    { // del 3 al 4 quedan tres leds prendidos (titila arr der)
        disp_write(coor, D_OFF);
        disp_update();
        coor.x++;
        life_of_shield -= 2;
        led_flick(life_of_shield, coor);
    }
    else if (life_of_shield <= 6)
    { // del 5 al 6 quedan dos leds prendidos (titila ab izq)
        disp_write(coor, D_OFF);
        disp_update();
        coor.x--;
        coor.y--;
        life_of_shield -= 4;
        led_flick(life_of_shield, coor);
    }
    else
    { // del 7 al 8 queda un led prendido (titila ab der)
        disp_write(coor, D_OFF);
        disp_update();
        coor.x++;
        life_of_shield -= 6;
        led_flick(life_of_shield, coor);
    }
}

// FUNCION LED_FLICK
// Hace titilar al LED de la coordenada indicada (el grado indica que tan rapido titila)
static void led_flick(int grado, dcoord_t coor_shield)
{
}
