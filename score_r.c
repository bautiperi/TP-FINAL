//-----------------------------------------------------------------------------------------------------//
// INCLUDE HEADER FILES
#include "score_r.h"
#include "aux_r.h"
#include "_defines.h"

// LIBRERIAS
#include "disdrv.h"
#include <stdio.h>

// PROTOTIPOS DE FUNCIONES

/*FUNCION NUM_VIS
brief: se encarga de mostrar un digito a la vez
num: (int) digito
coor: (dcoord_t) coordenada de arriba a la izquierda en donde empieza la visualizacion (cuadrado de 3x5)
return: void
*/
static void num_vis(int num, dcoord_t coor);

/*FUNCION SCORE_WRD_VIS
brief: se encarga de mostrar la parabra "SCORE"
return: void
*/
static void score_wrd_vis(void);

void score_vis(int score)
{
    dcoord_t coor_ini = {13, 8}; // coordenada inicial (superior izquierda del ultimo digito)
    shutdown_disp();

    // determina el número de dígitos
    int tempNum = score;
    int digit;
    do
    {
        digit = tempNum % 10;
        tempNum /= 10;

        // muestra el dígito
        num_vis(digit, coor_ini);
        // se guarda cada digito en el buffer del display
        coor_ini.x -= 3; // cada numero tiene un espacio de 3x5

    } while (tempNum > 0);

    score_wrd_vis(); // muestro "SCORE"
    disp_update();   // actualizo el display
}

static void num_vis(int num, dcoord_t coor)
{
    // Dependiendo del numero, se guardan en el buffer los leds indicados
    int i;
    switch (num)
    {
    case 1:
    {
        coor.x++;
        coor.y = 8;
        dcoord_t arr1[5] = {coor, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}};
        for (i = 0; i < 5; i++)
        {
            disp_write(arr1[i], D_ON);
        }
        break;
    }
    case 2:
    {
        dcoord_t arr2[11] = {coor, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {--coor.x, coor.y}, {--coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {++coor.x, coor.y}, {++coor.x, coor.y}};
        for (i = 0; i < 11; i++)
        {
            disp_write(arr2[i], D_ON);
        }
        break;
    }
    case 3:
    {
        dcoord_t arr3[11] = {coor, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {--coor.x, coor.y}, {--coor.x, coor.y}};
        coor.y += 2;
        arr3[7] = coor;
        coor.x++;
        arr3[8] = coor;
        coor.x++;
        arr3[9] = coor;
        coor.y--;
        arr3[10] = coor;
        for (i = 0; i < 11; i++)
        {
            disp_write(arr3[i], D_ON);
        }
        break;
    }
    case 4:
    {
        dcoord_t arr4[9] = {coor, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}};
        coor.y = 8;
        arr4[7] = coor;
        coor.y++;
        arr4[8] = coor;
        for (i = 0; i < 9; i++)
        {
            disp_write(arr4[i], D_ON);
        }
        break;
    }
    case 5:
    {
        coor.x += 2;
        dcoord_t arr5[11] = {coor, {--coor.x, coor.y}, {--coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {--coor.x, coor.y}, {--coor.x, coor.y}};
        for (i = 0; i < 11; i++)
        {
            disp_write(arr5[i], D_ON);
        }
        break;
    }
    case 6:
    {
        coor.x += 2;
        dcoord_t arr6[12] = {coor, {--coor.x, coor.y}, {--coor.x, coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {coor.x, ++coor.y}, {++coor.x, coor.y}, {++coor.x, coor.y}, {coor.x, --coor.y}, {coor.x, --coor.y}, {--coor.x, coor.y}};
        for (i = 0; i < 12; i++)
        {
            disp_write(arr6[i], D_ON);
        }
        break;
    }
    case 7:
    {
        dcoord_t arr7[7] = {
            coor,
            {++coor.x, coor.y},
            {++coor.x, coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y}};

        for (i = 0; i < 7; i++)
        {
            disp_write(arr7[i], D_ON);
        }
        break;
    }
    case 8:
    {
        dcoord_t arr8[13] = {
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
            disp_write(arr8[i], D_ON);
        }
        break;
    }
    case 9:
    {
        dcoord_t arr9[12] = {
            coor,
            {++coor.x, coor.y},
            {++coor.x, coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {coor.x, ++coor.y},
            {--coor.x, coor.y},
            {--coor.x, coor.y},
            {coor.x, (coor.y -= 2)},
            {++coor.x, coor.y},
            {--coor.x, --coor.y}};

        for (i = 0; i < 12; i++)
        {
            disp_write(arr9[i], D_ON);
        }
        break;
    }
    case 0:
    {
        dcoord_t arr0[12] = {
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
            disp_write(arr0[i], D_ON);
        }
        break;
    }
    default: // si llega al default es que el numero recibido no es un digito
        fprintf(stderr, "EL NUMERO A VISUALIZAR ES > 10.");
        break;
    }
}

static void score_wrd_vis(void)
{
    int i;

    // COORDENADAS
    dcoord_t score_wrd[55] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {13, 0}, {14, 0}, {15, 0}, {0, 1}, {3, 1}, {6, 1}, {8, 1}, {9, 1}, {11, 1}, {13, 1}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {6, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {13, 2}, {14, 2}, {15, 2}, {2, 3}, {3, 3}, {6, 3}, {8, 3}, {9, 3}, {11, 3}, {13, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4}};

    for (i = 0; i < 55; i++)
    {
        disp_write(score_wrd[i], D_ON);
    }
}
