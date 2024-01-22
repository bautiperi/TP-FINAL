#include "menu_r.h"
#include <unistd.h>
#include <stdio.h>

void menu_vis(joyinfo_t ubi)
{
    dcoord_t coord = {15, 0};
    while (ubi.y >= -70)
    {
        printf("EN MENU_VIS -> UBI: x: %d y: %d \n", ubi.x, ubi.y);
        printf("EN MENU_VIS -> COORD: x: %d y: %d \n", coord.x, coord.y);
        disp_write(coord, D_ON);
        disp_update();

        usleep(300000);

        disp_write(coord, D_OFF);
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
    dcoord_t menu_wrd[41] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {4, 1}, {4, 2}, {4, 3}, {4, 5}, {4, 5}, {5, 1}, {5, 3}, {5, 5}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {8, 2}, {9, 3}, {10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {12, 1}, {12, 2}, {12, 3}, {12, 4}, {13, 5}, {14, 5}, {15, 1}, {15, 2}, {15, 3}, {15, 4}};
    dcoord_t continue_btn[9] = {{2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {3, 9}, {3, 10}, {3, 11}, {4, 10}};
    dcoord_t exit_btn[10] = {{9, 10}, {10, 10}, {11, 10}, {12, 10}, {13, 10}, {14, 13}, {12, 8}, {12, 12}, {13, 9}, {13, 11}};

    for (i = 0; i < 42; i++)
    {
        printf("EN MENU_OPTIONS -> MENU: x: %d y: %d \n", menu_wrd[i].x, menu_wrd[i].y);
        disp_write(menu_wrd[i], D_ON);
    }

    for (i = 0; i < 9; i++)
    {
        printf("EN MENU_OPTIONS -> CONTINUE: x: %d y: %d \n", continue_btn[i].x, continue_btn[i].y);
        disp_write(continue_btn[i], D_ON);
    }

    for (i = 0; i < 10; i++)
    {
        printf("EN MENU_OPTIONS -> EXIT: x: %d y: %d \n", exit_btn[i].x, exit_btn[i].y);
        disp_write(exit_btn[i], D_ON);
    }

    disp_update();
}