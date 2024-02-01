#include "score_r.h"

#include <stdio.h>

static void num_vis(int num, dcoord_t coor);
static void score_wrd_vis(void);

void score_vis(int num)
{
    int value;
    dcoord_t coor_ini = {0, 8};
    shutdown_disp();
    if (num / 10000 > 0)
    {
        for (value = 10000; num >= 0; value /= 10, coor_ini.x += 3)
        {
            int aux = num;
            num /= value;
            num_vis(num, coor_ini);
            num *= value;
            aux -= num;
            num = aux;
        }
    }
    else if (num / 1000 > 0)
    {
        for (value = 1000; num >= 0; value /= 10, coor_ini.x += 3)
        {
            int aux = num;
            num /= value;
            num_vis(num, coor_ini);
            num *= value;
            aux -= num;
            num = aux;
        }
    }
    else if (num / 100 > 0)
    {
        for (value = 100; num >= 0; value /= 10, coor_ini.x += 3)
        {
            int aux = num;
            num /= value;
            num_vis(num, coor_ini);
            num *= value;
            aux -= num;
            num = aux;
        }
    }
    else if (num / 10 > 0)
    {
        for (value = 10; num >= 0; value /= 10, coor_ini.x += 3)
        {
            int aux = num;
            num /= value;
            num_vis(num, coor_ini);
            num *= value;
            aux -= num;
            num = aux;
        }
    }
    else
    {
        num_vis(num, coor_ini);
    }
    score_wrd_vis();
    disp_update();
}

static void num_vis(int num, dcoord_t coor)
{
    dcoord_t coor_inicial = coor;
    int i;
    switch (num)
    {
    case 1:
        coor.x++;
        coor.y = 8;
        dcoord_t arr[5] = {coor, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}};
        for (i = 0; i < 5; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 2:
        dcoord_t arr[11] = {coor, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {--coor.x, coor.y}, {--coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {++coor.x, coor.y}, {++coor.x, coor.y}};
        for (i = 0; i < 11; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 3:
        dcoord_t arr[11] = {coor, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {--coor.x, coor.y}, {--coor.x, coor.y}};
        coor.y += 2;
        arr[7] = coor;
        coor.x++;
        arr[8] = coor;
        coor.x++;
        arr[9] = coor;
        coor.y++;
        arr[10] = coor;
        for (i = 0; i < 11; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 4:
        dcoord_t arr[9] = {coor, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}};
        coor.y = 8;
        arr[7] = coor;
        coor.y--;
        arr[8] = coor;
        for (i = 0; i < 9; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 5:
        coor.x += 2;
        dcoord_t arr[11] = {coor, {--coor.x, coor.y}, {--coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {--coor.x, coor.y}, {--coor.x, coor.y}};
        for (i = 0; i < 11; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 6:
        coor.x += 2;
        dcoord_t arr[12] = {coor, {--coor.x, coor.y}, {--coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {--coor.x, coor.y}};
        for (i = 0; i < 12; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 7:
        dcoord_t arr[7] = {
            coor,
            {++coor.x, coor.y},
            {++coor.x, coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y}};

        for (i = 0; i < 7; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 8:
        dcoord_t arr[13] = {
            coor,
            {++coor.x, coor.y},
            {++coor.x, coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {--coor.x, coor.y},
            {--coor.x, coor.y},
            {coor.x, --coor.y},
            {coor.x, --coor.y},
            {++coor.x, coor.y},
            {--coor.x, --coor.y},
        };

        for (i = 0; i < 13; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 9:
        dcoord_t arr[10] = {
            coor,
            {++coor.x, coor.y},
            {++coor.x, coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {--coor.x, (coor.y - 2)},
            {--coor.x, coor.y},
            {coor.x, --coor.y}};

        for (i = 0; i < 10; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    case 0:
        dcoord_t arr[12] = {
            coor,
            {++coor.x, coor.y},
            {++coor.x, coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {--coor.x, coor.y},
            {--coor.x, coor.y},
            {coor.x, --coor.y},
            {coor.x, --coor.y},
            {coor.x, --coor.y}};

        for (i = 0; i < 12; i++)
        {
            disp_write(arr[i], D_ON);
        }
        break;
    default:
        fprintf(stderr, "EL NUMERO A VISUALIZAR ES > 10.");
        break;
    }
}

static void score_wrd_vis(void)
{
    shutdown_disp();

    int i;

    // COORDENADAS
    dcoord_t score_wrd[54] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {13, 0}, {14, 0}, {15, 0}, {0, 1}, {3, 1}, {6, 1}, {8, 1}, {9, 1}, {11, 1}, {13, 1}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {6, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {13, 2}, {14, 2}, {15, 2}, {2, 3}, {3, 3}, {6, 3}, {8, 3}, {9, 3}, {11, 3}, {13, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4}};

    for (i = 0; i < 54; i++)
    {
        disp_write(score_wrd[i], D_ON);
    }
}