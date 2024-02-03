// INCLUDES
#include "menu_r.h"
#include "aux_r.h"
#include "_defines_display_r.h"

// LIBRERIAS
#include "disdrv.h"
#include <unistd.h>

void menu_vis(int mapa[][COL])
{
    shutdown_disp();

    int i;

    // COORDENADAS DE CADA BTN/WRD
    dcoord_t menu_wrd[41] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {5, 1}, {5, 3}, {5, 5}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {8, 2}, {9, 3}, {10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {12, 1}, {12, 2}, {12, 3}, {12, 4}, {13, 5}, {14, 5}, {15, 1}, {15, 2}, {15, 3}, {15, 4}};

    dcoord_t continue_btn[9] = {{2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {3, 9}, {3, 10}, {3, 11}, {4, 10}};

    dcoord_t exit_btn[10] = {{9, 10}, {10, 10}, {11, 10}, {12, 10}, {13, 10}, {14, 10}, {12, 8}, {12, 12}, {13, 9}, {13, 11}};

    // LINEAS DE SELECCION
    dcoord_t linea_opt0[5] = {{1, 13}, {2, 13}, {3, 13}, {4, 13}, {5, 13}};

    dcoord_t linea_opt1[6] = {{9, 13}, {10, 13}, {11, 13}, {12, 13}, {13, 13}, {14, 13}};

    // VISUALIZACIONES
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
        for (i = 0; i < 5; i++)
        {
            disp_write(linea_opt0[i], D_ON);
        }
        for (i = 0; i < 6; i++)
        {
            disp_write(linea_opt1[i], D_OFF);
        }
    }
    if (FLICK_OPTION == 1)
    {
        for (i = 0; i < 5; i++)
        {
            disp_write(linea_opt0[i], D_OFF);
        }
        for (i = 0; i < 6; i++)
        {
            disp_write(linea_opt1[i], D_ON);
        }
    }
    dcoord_t led = {0, 0};
    disp_write(led, D_OFF);
    disp_update();
}

void menu_principal_vis(int mapa[][COL])
{
    // COORDENADAS DE CADA BTN/WRD
    dcoord_t start_wrd[51] = {{2, 1}, {1, 1}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {1, 5}, {0, 5}, {3, 1}, {4, 1}, {5, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {7, 1}, {7, 3}, {8, 1}, {8, 3}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}, {10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {11, 1}, {11, 3}, {11, 4}, {12, 1}, {12, 2}, {12, 3}, {12, 5}, {13, 1}, {14, 1}, {15, 1}, {14, 2}, {14, 3}, {14, 4}, {14, 5}};

    dcoord_t continue_btn[16] = {{2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12}, {2, 13}, {2, 14}, {3, 9}, {3, 10}, {3, 11}, {3, 12}, {3, 13}, {4, 10}, {4, 11}, {4, 12}, {5, 11}};

    dcoord_t power_off_btn[16] = {{11, 9}, {11, 10}, {11, 11}, {9, 10}, {10, 10}, {12, 10}, {13, 10}, {9, 11}, {9, 12}, {9, 13}, {13, 11}, {13, 12}, {13, 13}, {10, 13}, {11, 13}, {12, 13}};

    // LINEAS DE SELECCION
    dcoord_t linea_opt0[6] = {{1, 15}, {2, 15}, {3, 15}, {4, 15}, {5, 15}, {6, 15}};

    dcoord_t linea_opt1[5] = {{9, 15}, {10, 15}, {11, 15}, {12, 15}, {13, 15}};

    int i;

    shutdown_disp();

    // VISUALIZACIONES
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

    // Segun el flag de FLICK_OPTION titila la opcion seleccionada
    if (FLICK_OPTION == 0)
    {
        for (i = 0; i < 6; i++)
        {
            disp_write(linea_opt0[i], D_ON);
        }
        for (i = 0; i < 5; i++)
        {
            disp_write(linea_opt1[i], D_OFF);
        }
    }
    if (FLICK_OPTION == 1)
    {
        for (i = 0; i < 6; i++)
        {
            disp_write(linea_opt0[i], D_OFF);
        }
        for (i = 0; i < 5; i++)
        {
            disp_write(linea_opt1[i], D_ON);
        }
    }

    disp_update();
}
