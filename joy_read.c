#include "joy_read.h"
#include <pthread.h>

void *joy_reading(void *arg)
{
    int(*mapa)[COL] = (int(*)[COL])arg;
    joyinfo_t coord = {0, 0, J_NOPRESS};
    int npos = 0;
    dcoord_t coord_menu = {0, 15};
    FLICK_OPTION = 0; // flag para seleccion en el menu
    // JUEGO
    do
    {
        coord = joy_read();
        if (STATUS == 0) // JUEGO
        {
            led_flick(coord_menu);

            obj_vis(mapa, mapa[0][COL - 1]);
            if ((coord.sw) = (J_PRESS)) // dispara el player
            {
                pthread_t up_gamer_fire;
                pthread_create(&up_gamer_fire, NULL, gamer_fire, mapa);
            }
            if (coord.x > THRESHOLD) // movimiento a la derecha
            {
                npos = 1;
            }
            else if (coord.x < -THRESHOLD) // movimiento a la izquierda
            {
                npos = -1;
            }
            else
            {
                npos = 0;
            }

            if (coord.y >= THRESHOLD)
            { // si la coordenada en y no se movio hacia la seleccion del menu
                STATUS = 1;
                flag_game_update = 0;
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

            if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
            {
                FLICK_OPTION = 0; // TITLA EL SALIR
            }

            if (FLICK_OPTION == 1 && coord.sw == J_PRESS)
            {
                STATUS = 2; // CAMBIA A MENU PRINCIPAL
            }
            else if (FLICK_OPTION == 0 && coord.sw == J_PRESS)
            {
                STATUS = 0; // VUELVE AL JUEGO
                flag_game_update = 1;
            }
        }
        if (STATUS == 2) // MENU PRINCIPAL
        {
            menu_principal_vis(mapa);
            if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
            {
                FLICK_OPTION = 1; // TITILA EL APAGAR
            }

            if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
            {
                FLICK_OPTION = 0; // TITLA EL PLAY
            }

            if (FLICK_OPTION == 1 && coord.sw == J_PRESS)
            {
                shutdown_disp(); // APAGA EL DISPLAY
                flag_game_update = 0;
                END_GAME = 1; // INDICA QUE SE TERMNINO EL JUEGO
            }
            else if (FLICK_OPTION == 0 && coord.sw == J_PRESS)
            {
                STATUS = 0; // VUELVE AL JUEGO
                map_def(RASP, mapa);
                flag_game_update = 1;
            }
        }
    } while (END_GAME != 1);

    return NULL;
}