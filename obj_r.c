//-----------------------------------------------------------------------------------------------------//
// INCLUDE HEADER FILES
#include "obj_r.h"
#include "aux_r.h"
#include "_defines_display_r.h"

// LIBRERIAS
#include <unistd.h>
#include <stdio.h>

/***********************************  GAMER  ***********************************/

void gamer_vis(dcoord_t ubi)
{
    int i;
    ubi.x++;
    // coordenadas de lo que se tiene que prender
    dcoord_t arr[4] = {ubi, {--ubi.x, --ubi.y}, {ubi.x, ++ubi.y}, {--ubi.x, ubi.y}};
    for (i = 0; i < 4; i++) // prende todas las coordenadas
    {
        if (arr[i].x <= 15 && arr[i].x >= 0 && arr[i].y <= 15 && arr[i].y >= 0) // evita errores de display
        {
            disp_write(arr[i], D_ON);
        }
    }
}

/***********************************  ALIENS  ***********************************/

void aliens_vis(dcoord_t coor_inicial)
{
    if (coor_inicial.x <= 15 && coor_inicial.x >= 0 && coor_inicial.y <= 15 && coor_inicial.y >= 0)
    {
        disp_write(coor_inicial, D_ON); // prende el led de cada alien
    }
}

/*******************************  THE FINAL BOSS  *********************************/

void final_boss_vis(dcoord_t ubi, int mapa[][COL])
{
    int i;
    dcoord_t ubi_inicial = ubi;
    int flag = DIRECCION;
    // CASO CUANDO EL BOSS SALE DE PANTALLA LADO DERECHO
    if (mapa[1][14] == BOSS && flag > 0)
    {
        for (i = ubi_inicial.x; i < ubi_inicial.x + 2; i++)
        {
            ubi.x = i;

            if (i == ubi_inicial.x + 1)
            {
                if (ubi.x <= 15 && ubi.x >= 0 && ubi.y <= 15 && ubi.y >= 0)
                {
                    disp_write(ubi, D_ON);
                }
                ubi.y++;
                if (ubi.x <= 15 && ubi.x >= 0 && ubi.y <= 15 && ubi.y >= 0)
                {
                    disp_write(ubi, D_ON);
                }
                ubi.y--;
            }
            else
            {
                if (ubi.x <= 15 && ubi.x >= 0 && ubi.y <= 15 && ubi.y >= 0)
                {
                    disp_write(ubi, D_ON);
                }
            }
        }
    }
    // CASO CUANDO EL BOSS SALE DE PANTALLA LADO DERECHO
    else if (mapa[1][15] == BOSS && flag > 0)
    {
        if (ubi.x <= 15 && ubi.x >= 0 && ubi.y <= 15 && ubi.y >= 0)
        {
            disp_write(ubi, D_ON);
        }
    }
    // CASO CUANDO EL BOSS SALE DE PANTALLA LADO IZQUIERDO
    else if (mapa[1][0] == BOSS && flag < 0)
    {
        usleep(500000);
        ubi_inicial.x = 0;
        ubi_inicial.y = 1;
        if (ubi_inicial.x <= 15 && ubi_inicial.x >= 0 && ubi_inicial.y <= 15 && ubi_inicial.y >= 0)
        {
            disp_write(ubi_inicial, D_ON);
        }
        ubi_inicial.y++;
        if (ubi_inicial.x <= 15 && ubi_inicial.x >= 0 && ubi_inicial.y <= 15 && ubi_inicial.y >= 0)
        {
            disp_write(ubi_inicial, D_ON);
        }
        ubi_inicial.y--;
        ubi_inicial.x++;
        if (ubi_inicial.x <= 15 && ubi_inicial.x >= 0 && ubi_inicial.y <= 15 && ubi_inicial.y >= 0)
        {
            disp_write(ubi_inicial, D_ON);
        }
        usleep(500000);
        if (ubi_inicial.x <= 15 && ubi_inicial.x >= 0 && ubi_inicial.y <= 15 && ubi_inicial.y >= 0)
        {
            disp_write(ubi_inicial, D_OFF);
        }
        ubi_inicial.y++;
        ubi_inicial.x--;
        if (ubi_inicial.x <= 15 && ubi_inicial.x >= 0 && ubi_inicial.y <= 15 && ubi_inicial.y >= 0)
        {
            disp_write(ubi_inicial, D_OFF);
        }
        usleep(500000);
        ubi_inicial.y--;
        if (ubi_inicial.x <= 15 && ubi_inicial.x >= 0 && ubi_inicial.y <= 15 && ubi_inicial.y >= 0)
        {
            disp_write(ubi_inicial, D_OFF);
        }
    }
    // CASO CUANDO EL BOSS SE MUEVE EN PANTALLA
    else
    {
        int i;
        ubi.x++;
        // coordenadas de lo que se tiene que prender
        dcoord_t arr[4] = {{ubi.x, ubi.y}, {--ubi.x, ++ubi.y}, {ubi.x, --ubi.y}, {--ubi.x, ubi.y}};
        for (i = 0; i < 4; i++) // prende todas las coordenadas
        {
            if (arr[i].x <= 15 && arr[i].x >= 0 && arr[i].y <= 15 && arr[i].y >= 0)
            {
                disp_write(arr[i], D_ON);
            }
        }
    }
}

/***********************************  LIVES   ***********************************/

void lives_vis(int cant)
{
    // coordenadas de la visualizacion de las vidas
    dcoord_t first_life = {1, 0}, second_life = {2, 0}, third_life = {3, 0};
    switch (cant) // segun la cantidad de vidas prende o apaga los leds correspondientes
    {
    case 0: // CASO 0 VIDAS: BORRA LA ULTIMA VIDA
        disp_write(first_life, D_OFF);
        disp_update();
        break;
    case 1: // CASO 1 VIDAS: BORRA LA SEGUNDA VIDA
        disp_write(first_life, D_ON);
        disp_write(second_life, D_OFF);
        disp_update();
        break;
    case 2: // CASO 2 VIDAS: BORRA LA TERCERA VIDA
        disp_write(second_life, D_ON);
        disp_write(first_life, D_ON);
        disp_write(third_life, D_OFF);
        disp_update();
        break;
    default: // CASO 3 VIDAS: PRENDE TODAS LAS VIDAS
        disp_write(third_life, D_ON);
        disp_write(second_life, D_ON);
        disp_write(first_life, D_ON);
        disp_update();
        break;
    }
}

/***********************************  SHIELDS  ***********************************/

void shields_vis(dcoord_t coor)
{
    if (coor.x <= 15 && coor.x >= 0 && coor.y <= 15 && coor.y >= 0)
    {
        disp_write(coor, D_ON); // prende el led correspondiente
    }
}
