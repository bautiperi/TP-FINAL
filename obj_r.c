
// INCLUDES
#include "obj_r.h"
#include <stdio.h>

// guardan las coordenadas del led de abajo a la izquierda
// static dcoord_t shield1 = {1, 12}, shield2 = {5, 12}, shield3 = {9, 12}, shield4 = {13, 12};

/***********************************  GAMER   ***********************************/

void gamer_vis(dcoord_t ubi)
{
    int i;
    dcoord_t ubi_inicial = ubi;

    for (i = ubi_inicial.x; i < ubi_inicial.x - 3; i--)
    {
        ubi.x = i;
        if (i == ubi_inicial.x - 1)
        {
            printf("EN GAMER_VIS 1: x: %d y: %d \n", ubi.x, ubi.y);
            disp_write(ubi, D_ON);
            ubi.y++;
            printf("EN GAMER_VIS 2: x: %d y: %d \n", ubi.x, ubi.y);
            disp_write(ubi, D_ON);
            ubi.y--;
            printf("EN GAMER_VIS 3: x: %d y: %d \n", ubi.x, ubi.y);
        }
        else
        {
            printf("EN GAMER_VIS 4: x: %d y: %d \n", ubi.x, ubi.y);
            disp_write(ubi, D_ON);
        }
    }
    // disp_update();
}

void gamer_shot(dcoord_t coord)
{
    int i;
    dcoord_t arr[4] = {coord, {++coord.x, coord.y}, {coord.x, --coord.y}, {++coord.x, ++coord.y}};
    for (i = 0; i < 4; i++)
    {
        printf("EN GAMER_SHOT %d: x: %d y: %d \n", i, arr[i].x, arr[i].y);
    }

    multp_flick(arr, 4);
}

/***********************************  ALIENS   ***********************************/

void aliens_vis(dcoord_t coor_inicial)
{
    int i, j;
    dcoord_t coor = coor_inicial;
    for (j = coor.y; j < coor.y - 4; j--)
    {
        if ((j % 2) == 0)
        {
            for (i = coor.x; i < coor.x + 13; i++)
            {
                printf("EN ALIEN_VIS A %d: x: %d y: %d \n", i, coor.x, coor.y);
                disp_write(coor, D_ON);
                ++coor.x;
                printf("EN ALIEN_VIS A %d: x: %d y: %d \n", i, coor.x, coor.y);
                disp_write(coor, D_OFF);
            }
        }
        else
        {
            for (i = coor.x + 1; i < coor.x + 14; i++)
            {
                printf("EN ALIEN_VIS B %d: x: %d y: %d \n", i, coor.x, coor.y);
                disp_write(coor, D_ON);
                ++coor.x;
                printf("EN ALIEN_VIS B %d: x: %d y: %d \n", i, coor.x, coor.y);
                disp_write(coor, D_OFF);
            }
        }
    }
    // disp_update();
}

void aliens_death(dcoord_t coord)
{
    disp_write(coord, D_OFF);
    printf("EN ALIEN_DEATH: x: %d y: %d \n", coord.x, coord.y);
    // disp_update();
}

/*******************************  THE FINAL BOSS  *********************************/

void final_boss_vis(dcoord_t ubi)
{
    int i;
    dcoord_t ubi_inicial = ubi;
    for (i = ubi_inicial.x; i < ubi_inicial.x + 3; i++)
    {
        ubi.x = i;
        if (i == ubi_inicial.x + 1)
        {
            printf("EN FINAL_BOSS_VIS 1: x: %d y: %d \n", ubi.x, ubi.y);
            disp_write(ubi, D_ON);
            ubi.y++;
            printf("EN FINAL_BOSS_VIS 2: x: %d y: %d \n", ubi.x, ubi.y);
            disp_write(ubi, D_ON);
            ubi.y--;
            printf("EN FINAL_BOSS_VIS 3: x: %d y: %d \n", ubi.x, ubi.y);
        }
        else
        {
            disp_write(ubi, D_ON);
            printf("EN FINAL_BOSS_VIS 4: x: %d y: %d \n", ubi.x, ubi.y);
        }
    }
    // disp_update();
}

void final_boss_shot(dcoord_t coord)
{
    int i;
    dcoord_t arr[4] = {coord, {++coord.x, coord.y}, {coord.x, ++coord.y}, {++coord.x, --coord.y}};
    for (i = 0; i < 4; i++)
    {
        printf("EN FINAL_BOSS_SHOT %d: x: %d y: %d \n", i, arr[i].x, arr[i].y);
    }
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
        printf("EN LIVES_VIS 0v: x: %d y: %d \n", first_life.x, first_life.y);
        disp_write(first_life, D_OFF);

        break;
    case 1: // CASO 1 VIDAS: BORRA LA SEGUNDA VIDA
        printf("EN LIVES_VIS 1v: x: %d y: %d \n", second_life.x, second_life.y);
        disp_write(second_life, D_OFF);
        // disp_update();
        break;
    case 2:
        printf("EN LIVES_VIS 2v: x: %d y: %d \n", third_life.x, third_life.y);
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
    printf("EN SHIELDS_VIS 1: x: %d y: %d \n", coor.x, coor.y);
    disp_write(coor, D_ON); // prendo led de abajo a la izq
    coor.y--;
    printf("EN SHIELDS_VIS 2: x: %d y: %d \n", coor.x, coor.y);
    disp_write(coor, D_ON); // prendo led de arriba a la izq
    coor.x++;
    printf("EN SHIELDS_VIS 3: x: %d y: %d \n", coor.x, coor.y);
    disp_write(coor, D_ON); // prendo led de arriba a la der
    coor.y++;
    printf("EN SHIELDS_VIS 4: x: %d y: %d \n", coor.x, coor.y);
    disp_write(coor, D_ON); // prendo led de abajo a la der
                            // disp_update();
}

void shields_life(int life_of_shield, dcoord_t coor_of_shield)
{
    // primera colision -> parpadea el led
    // segunda colision -> se apaga (2 vidas por cada led)
    if (life_of_shield == 1)
    {
        printf("EN SHIELDS_LIFE 1: x: %d y: %d \n", coor_of_shield.x, coor_of_shield.y);
        led_flick(coor_of_shield);
    }
    else
    {
        printf("EN SHIELDS_LIFE 2: x: %d y: %d \n", coor_of_shield.x, coor_of_shield.y);
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