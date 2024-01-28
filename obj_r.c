
// INCLUDES
#include "obj_r.h"
#include <unistd.h>

// guardan las coordenadas del led de abajo a la izquierda
// static dcoord_t shield1 = {1, 12}, shield2 = {5, 12}, shield3 = {9, 12}, shield4 = {13, 12};

/***********************************  GAMER   ***********************************/

void gamer_vis(dcoord_t ubi)
{
    int i;
    dcoord_t ubi_inicial = ubi;

    for (i = ubi_inicial.x; i < ubi_inicial.x + 3; i++)
    {
        ubi.x = i;
        if (i == ubi_inicial.x + 1)
        {
            disp_write(ubi, D_ON);
            ubi.y--;
            disp_write(ubi, D_ON);
            ubi.y++;
        }
        else
        {
            disp_write(ubi, D_ON);
        }
    }
    // disp_update();
}

void gamer_shot(dcoord_t coord)
{
    int i;
    dcoord_t arr[4] = {coord, {++coord.x, coord.y}, {coord.x, --coord.y}, {++coord.x, ++coord.y}};

    multp_flick(arr, 4);
}

/***********************************  ALIENS   ***********************************/

void aliens_vis(dcoord_t coor_inicial)
{
    disp_write(coor_inicial, D_ON);
}

void aliens_death(dcoord_t coord)
{
    disp_write(coord, D_OFF);
    // disp_update();
}

/*******************************  THE FINAL BOSS  *********************************/

void final_boss_vis(dcoord_t ubi, int mapa[][COL])
{
    int i;
    dcoord_t ubi_inicial = ubi;
    int flag = mapa[0][6];
    if (mapa[1][14] == BOSS && flag > 0)
    {
        for (i = ubi_inicial.x; i < ubi_inicial.x + 2; i++)
        {
            ubi.x = i;

            if (i == ubi_inicial.x + 1)
            {
                disp_write(ubi, D_ON);
                ubi.y++;
                disp_write(ubi, D_ON);
                ubi.y--;
            }
            else
            {
                disp_write(ubi, D_ON);
            }
        }
    }
    else if (mapa[1][15] == BOSS && flag > 0)
    {
        disp_write(ubi, D_ON);
    }
    else if (mapa[1][0] == BOSS && flag < 0)
    {
        usleep(500000);
        ubi_inicial.x = 0;
        ubi_inicial.y = 1;
        disp_write(ubi_inicial, D_ON);
        ubi_inicial.y++;
        disp_write(ubi_inicial, D_ON);
        ubi_inicial.y--;
        ubi_inicial.x++;
        disp_write(ubi_inicial, D_ON);
        usleep(500000);
        disp_write(ubi_inicial, D_OFF);
        ubi_inicial.y++;
        ubi_inicial.x--;
        disp_write(ubi_inicial, D_OFF);
        usleep(500000);
        ubi_inicial.y--;
        disp_write(ubi_inicial, D_OFF);
    }
    else
    {
        for (i = ubi_inicial.x; i < ubi_inicial.x + 3; i++)
        {
            ubi.x = i;

            if (i == ubi_inicial.x + 1)
            {
                disp_write(ubi, D_ON);
                ubi.y++;
                disp_write(ubi, D_ON);
                ubi.y--;
            }
            else
            {
                disp_write(ubi, D_ON);
            }
        }
    }

    // disp_update();
}

void final_boss_shot(dcoord_t coord)
{
    int i;
    dcoord_t arr[4] = {coord, {++coord.x, coord.y}, {coord.x, ++coord.y}, {++coord.x, --coord.y}};
    multp_flick(arr, 4);
}

/***********************************  LIVES   ***********************************/

void lives_vis(int cant)
{
    // coordenadas de la visualizacion de las vidas
    dcoord_t first_life = {1, 0}, second_life = {2, 0}, third_life = {3, 0};
    switch (cant)
    {
    case 0: // CASO 0 VIDAS: BORRA LA ULTIMA VIDA
        disp_write(first_life, D_OFF);

        break;
    case 1: // CASO 1 VIDAS: BORRA LA SEGUNDA VIDA
        disp_write(second_life, D_OFF);
        // disp_update();
        break;
    case 2:
        disp_write(third_life, D_OFF);
        // disp_update();
        break;
    default:
        disp_write(third_life, D_ON);
        disp_write(second_life, D_ON);
        disp_write(first_life, D_ON);
        break;
    }
    // disp_update();
}

/***********************************  SHIELDS  ***********************************/

void shields_vis(dcoord_t coor)
{
    disp_write(coor, D_ON);
}

void shields_life(int life_of_shield, dcoord_t coor_of_shield)
{
    // primera colision -> parpadea el led
    // segunda colision -> se apaga (2 vidas por cada led)
    if (life_of_shield == 1)
    {
        led_flick(coor_of_shield);
    }
    else
    {
        disp_write(coor_of_shield, D_OFF);
        disp_update();
    }
}

/***********************************  GAME OVER  ***********************************/

void game_over(void)
{
    int i;
    // coordenadas de la carita triste
    dcoord_t coor[20] = {{5, 4}, {5, 5}, {5, 6}, {6, 4}, {6, 5}, {6, 6}, {9, 4}, {9, 5}, {9, 6}, {10, 4}, {10, 5}, {10, 6}, {4, 12}, {5, 11}, {6, 10}, {7, 10}, {8, 10}, {9, 10}, {10, 11}, {11, 12}};

    shutdown_disp();

    for (i = 0; i < 20; i++)
    {
        disp_write(coor[i], D_ON);
    }

    disp_update();
}