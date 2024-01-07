// INCLUDES
#include "aux_r.h"

void led_flick(dcoord_t coor_)
{

    int i;
    int tiempo_espera = DELAY / 100;

    for (i = 0; i < MAX_ITERATIONS; i++)
    {
        // se enciende el led
        disp_write(coor_, D_ON);
        disp_update();

        // tiempo que esta apagado
        usleep(tiempo_espera);

        // apaga el LED en la posición especificada
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
            disp_write(coords[i], D_ON);
            disp_update();
        }

        // tiempo que esta apagado
        usleep(tiempo_espera);

        for (j = 0; j < cant; j++)
        {
            // apaga el LED en la posición especificada
            disp_write(coords[i], D_OFF);
            disp_update();
        }
    }
}