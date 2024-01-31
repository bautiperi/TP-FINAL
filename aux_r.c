// INCLUDES
#include "aux_r.h"
#include "_defines_display_r.h"

// LIBRERIAS
#include <unistd.h>
#include "disdrv.h"
#include "joydrv.h"

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
            disp_write(coords[j], D_ON);
            disp_update();
        }

        // tiempo que esta apagado
        usleep(tiempo_espera);

        for (j = 0; j < cant; j++)
        {
            // apaga el LED en la posición especificada
            disp_write(coords[j], D_OFF);
            disp_update();
        }
    }
}

void shutdown_disp(void)
{
    int i, j;
    // disp_clear();
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