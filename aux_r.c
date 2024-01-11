// INCLUDES
#include "aux_r.h"
#include <unistd.h>
#include <stdio.h>

void led_flick(dcoord_t coor_)
{

    int i;
    int tiempo_espera = DELAY / 100;

    for (i = 0; i < MAX_ITERATIONS; i++)
    {
        // se enciende el led
        printf("EN LED_FLICK: x: %d y: %d \n", coor_.x, coor_.y);
        disp_write(coor_, D_ON);
        disp_update();

        // tiempo que esta apagado
        usleep(tiempo_espera);

        // apaga el LED en la posición especificada
        printf("EN LED_FLICK: x: %d y: %d \n", coor_.x, coor_.y);
        disp_write(coor_, D_OFF);
        disp_update();
    }
}

void multp_flick(dcoord_t coords[], int cant)
{
    int i, j;
    int tiempo_espera = DELAY / 100;

    for (i = 0; i < MAX_ITERATIONS; i++)
    {

        for (j = 0; j < cant; j++)
        {
            // se enciende el led
            printf("EN MULTP_FLICK: x: %d y: %d \n", coords[j].x, coords[j].y);
            disp_write(coords[j], D_ON);
            disp_update();
        }

        // tiempo que esta apagado
        usleep(tiempo_espera);

        for (j = 0; j < cant; j++)
        {
            printf("EN MULTP_FLICK: x: %d y: %d \n", coords[j].x, coords[j].y);
            // apaga el LED en la posición especificada
            disp_write(coords[j], D_OFF);
            disp_update();
        }
    }
}

void shutdown_disp(void)
{
    int i, j;
    disp_clear();
    dcoord_t coor;

    // BOORO TODO
    for (i = 0; i < 16; i++)
    {
        coor.x = i;
        for (j = 0; j < 16; j++)
        {
            coor.y = j;
            printf("EN SHUTDOWN_DISP: x: %d y: %d \n", coor.x, coor.y);
            disp_write(coor, D_OFF);
        }
    }
    disp_update();
}