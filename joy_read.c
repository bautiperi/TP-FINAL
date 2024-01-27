#include "joy_read.h"

/*
STATUS es un flag
STATUS = 0 -> en el juego
STATUS = 1 -> en el menu
STATUS = 2 -> menu principal
*/

void joy_movement(int mapa[][COL])
{
    joyinfo_t coord = {0, 0, J_NOPRESS};
    int npos = 0;
    dcoord_t coords = {15, 0};
    FLICK_OPTION = 0; // flag para seleccion en el menu
    // JUEGO
    while (1)
    {
        if (STATUS == 0) // JUEGO
        {
            obj_vis(mapa, mapa[0][COL - 1]);
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
                STATUS = 0;
            }
            else
            { // sino, cambia al menu
                STATUS = 1;
            }
            gamer_movement(mapa, npos); // genera el movimiento del player
        }
        if (STATUS == 1) // MENU
        {
            menu_vis(mapa);
            if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
            {
                FLICK_OPTION = 1; // TITILA EL PLAY
            }
            else if (coord.x > THRESHOLD && coord.sw == J_PRESS)
            {
                STATUS = 2; // CAMBIA A MENU PRINCIPAL
            }
            if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
            {
                FLICK_OPTION = 0; // TITLA EL SALIR
            }
            else if (coord.x < -THRESHOLD && coord.sw == J_PRESS)
            {
                STATUS = 0; // VUELVE AL JUEGO
            }
        }
        if (STATUS == 2) // MENU PRINCIPAL
        {
            menu_principal_vis(mapa);
            if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
            {
                FLICK_OPTION = 1; // TITILA EL PLAY
            }
            else if (coord.x > THRESHOLD && coord.sw == J_PRESS)
            {
                shutdown_disp(); // APAGA EL DISPLAY
                END_GAME = 1;    // INDICA QUE SE TERMNINO EL JUEGO
            }
            if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
            {
                FLICK_OPTION = 0; // TITLA EL APAGAR
            }
            else if (coord.x < -THRESHOLD && coord.sw == J_PRESS)
            {
                STATUS = 0; // VUELVE AL JUEGO
            }
        }
    }
}