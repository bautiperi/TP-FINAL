#include "menu_r.h"
#include <unistd.h>

void menu_vis(joyinfo_t ubi)
{
    while (ubi.y >= -70)
    {
        disp_write({15, 0}, D_ON);
        disp_update();

        usleep(300000);

        disp_write({15, 0}, D_OFF);
        disp_update();
    }
    if (ubi.y < -70)
    {
        menu_options();
    }
}

void menu_options(void)
{
    shutdown_disp();

    int i;

    // COORDENADAS DE CADA COSA
    dcoord_t menu_wrd[42] = {{0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 14}, {1, 13}, {2, 11}, {2, 10}, {2, 11}, {2, 12}, {2, 13}, {2, 14}, {4, 10}, {4, 11}, {4, 12}, {4, 13}, {4, 14}, {5, 14}, {5, 12}, {5, 10}, {7, 10}, {7, 11}, {7, 12}, {7, 13}, {7, 14}, {8, 13}, {9, 12}, {10, 10}, {10, 11}, {10, 12}, {10, 13}, {10, 14}, {12, 11}, {12, 12}, {12, 13}, {12, 14}, {13, 10}, {14, 10}, {15, 11}, {15, 12}, {15, 13}, {15, 14}};
    dcoord_t continue_btn[9] = {{2, 7}, {2, 6}, {2, 5}, {2, 4}, {2, 3}, {3, 6}, {3, 5}, {3, 4}, {4, 5}};
    dcoord_t exit_btn[10] = {{9, 5}, {10, 5}, {11, 5}, {12, 5}, {13, 5}, {14, 5}, {12, 7}, {12, 3}, {13, 6}, {13, 4}};

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

    disp_update();
}