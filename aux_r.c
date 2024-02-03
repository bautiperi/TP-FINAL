// INCLUDES
#include "aux_r.h"
#include "_defines_display_r.h"
#include "_defines.h"

// LIBRERIAS
#include "disdrv.h"

void shutdown_disp(void)
{
    int i, j;
    dcoord_t coor;

    // BOORO TODO
    for (i = 0; i < 16; i++)
    {
        coor.x = i;
        for (j = 0; j < 16; j++)
        {
            coor.y = j;
            disp_write(coor, D_OFF);
        }
    }
    disp_update();
}

/***********************************  GAME OVER  ***********************************/

void game_over(void)
{
    int i;
    // coordenadas de la carita triste
    dcoord_t coor[20] = {{5, 4}, {5, 5}, {5, 6}, {6, 4}, {6, 5}, {6, 6}, {9, 4}, {9, 5}, {9, 6}, {10, 4}, {10, 5}, {10, 6}, {4, 12}, {5, 11}, {6, 10}, {7, 10}, {8, 10}, {9, 10}, {10, 11}, {11, 12}};

    shutdown_disp(); // borra toda la visualizacion

    for (i = 0; i < 20; i++)
    {
        if (coor[i].x <= 15 && coor[i].x >= 0 && coor[i].y <= 15 && coor[i].y >= 0)
        {
            disp_write(coor[i], D_ON);
        } // prende los leds del array
    }

    disp_update();
}
