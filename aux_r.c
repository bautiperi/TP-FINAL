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