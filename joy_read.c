#include "joy_read.h"

/*
mapa[4][0] es un flag
mapa[4][0] = 0 -> en el juego
mapa[4][0] = 1 -> en el menu
mapa[4][0] = 2 -> menu principal
*/

void joy_movement(int mapa[][COL])
{
    joyinfo_t coord = {0, 0, J_NOPRESS};
    int npos = 0;
    dcoord_t coords = {15, 0};
    mapa[5][0] = 0; // flag para seleccion en el menu
    // JUEGO
    while (1)
    {
        if (mapa[4][0] == 0) // JUEGO
        {
            coord = joy_read();
            if (coord.sw = J_PRESS) // dispara el player
            {
                gamer_fire(mapa);
            }
            if (coord.x > THRESHOLD) // movimiento a la derecha
            {
                npos++;
            }
            if (coord.x < -THRESHOLD) // movimiento a la izquierda
            {
                npos--;
            }

            if (coord.y <= THRESHOLD)
            { // si la coordenada en y no se movio hacia la seleccion del menu
                mapa[4][0] = 0;
            }
            else
            { // sino, cambia al menu
                mapa[4][0] = 1;
            }
            gamer_movement(mapa, npos); // genera el movimiento del player
        }
        if (mapa[4][0] == 1) // MENU
        {
            if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
            {
                mapa[5][0] = 1; // TITILA EL PLAY
            }
            else if (coord.x > THRESHOLD && coord.sw == J_PRESS)
            {
                mapa[4][0] = 2; // CAMBIA A MENU PRINCIPAL
            }
            if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
            {
                mapa[5][0] = 0; // TITLA EL SALIR
            }
            else if (coord.x < -THRESHOLD && coord.sw == J_PRESS)
            {
                mapa[4][0] = 0; // VUELVE AL JUEGO
            }
        }
        if (mapa[4][0] == 2) // MENU PRINCIPAL
        {
            menu_principal_vis(mapa);
        }
    }
}