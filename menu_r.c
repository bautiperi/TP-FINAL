// INCLUDES
#include "menu_r.h"
#include "aux_r.h"

// DEFINES
#include "_defines_display_r.h"

// LIBRERIAS
#include "disdrv.h"
#include "joydrv.h"
#include <unistd.h>

void menu_vis(int mapa[][COL])
{
    shutdown_disp();

    int i;

    // COORDENADAS DE CADA COSA
    dcoord_t menu_wrd[41] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {5, 1}, {5, 3}, {5, 5}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {8, 2}, {9, 3}, {10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {12, 1}, {12, 2}, {12, 3}, {12, 4}, {13, 5}, {14, 5}, {15, 1}, {15, 2}, {15, 3}, {15, 4}};
    dcoord_t continue_btn[9] = {{2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {3, 9}, {3, 10}, {3, 11}, {4, 10}};
    dcoord_t exit_btn[10] = {{9, 10}, {10, 10}, {11, 10}, {12, 10}, {13, 10}, {14, 10}, {12, 8}, {12, 12}, {13, 9}, {13, 11}};

    for (i = 0; i < 42; i++)
    {
        disp_write(menu_wrd[i], D_ON);
    }

    for (i = 0; i < 9; i++)
    {
        disp_write(continue_btn[i], D_ON);
    }

    for (i = 0; i < 10; i++)
    {
        disp_write(exit_btn[i], D_ON);
    }

    // Segun el flag de FLICK_OPTION titila la opcion seleccionada
    if (FLICK_OPTION == 0)
    {
        
    }
    if (FLICK_OPTION == 1)
    {
    }

    disp_write({0, 0}, D_OFF);
    disp_update();
}

void menu_principal_vis(int mapa[][COL])
{
    dcoord_t start_wrd[51] = {{2, 1}, {1, 1}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {1, 5}, {0, 5}, {3, 1}, {4, 1}, {5, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {7, 1}, {7, 3}, {8, 1}, {8, 3}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}, {10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {11, 1}, {11, 3}, {11, 4}, {12, 1}, {12, 2}, {12, 3}, {12, 5}, {13, 1}, {14, 1}, {15, 1}, {14, 2}, {14, 3}, {14, 4}, {14, 5}};

    dcoord_t continue_btn[16] = {{2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {2, 13}, {2, 14}, {3, 9}, {3, 10}, {3, 11}, {3, 12}, {3, 13}, {4, 10}, {4, 11}, {4, 12}, {5, 11}};

    dcoord_t power_off_btn[16] = {{11, 9}, {11, 10}, {11, 11}, {9, 10}, {10, 10}, {12, 10}, {13, 10}, {9, 11}, {9, 12}, {9, 13}, {13, 11}, {13, 12}, {13, 13}, {10, 13}, {11, 13}, {12, 13}};

    int i;
    shutdown_disp();

    for (i = 0; i < 51; i++)
    {
        disp_write(start_wrd[i], D_ON);
    }

    for (i = 0; i < 16; i++)
    {
        disp_write(continue_btn[i], D_ON);
    }

    for (i = 0; i < 16; i++)
    {
        disp_write(power_off_btn[i], D_ON);
    }

    pthread_t flick;
    if (FLICK_OPTION == 0)
    {
        multp_cant = 16;
        pthread_create(flick, NULL, multp_flick, continue_btn);
        // multp_flick(continue_btn);
    }
    if (FLICK_OPTION == 1)
    {
        multp_cant = 16;
        pthread_create(flick, NULL, multp_flick, power_off_btn);
        // multp_flick(power_off_btn);
    }
    disp_update();
}
