#include "back_game_a.h"

#include <unistd.h>
#include <time.h>
#include <stdlib.h>

static void alien_movement_v(int mapa[][COL]);
static void swap(int mapa[][COL], int x1, int y1, int x2, int y2);

void alien_movement_h(int mapa[][COL])
{
    int x, y;
    int dir = 1, flag = 0;
    // se mueve hacia la derecha
    usleep(2000000);

    while (1)
    {
        if (dir == 1)
        {

            for (y = 1; y < FIL; y++)
            {
                for (x = 0; x < COL; x++)
                {
                    // Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                    if (mapa[y][COL - 2] == 4)
                    {
                        dir = -1; // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                    }
                    // Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                    else if (mapa[y][x + 1] == -1 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        mapa[y][x + 1] = 0;
                        swap(mapa, x, y, x + 1, y);
                        x++;
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x + 1] == 0 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        swap(mapa, x, y, x + 1, y);
                        x++;
                    }
                }
            }
        }
        else if (flag == 1)
        {
            alien_movement_v(mapa);
            flag = 0;
        }
        else
        { // Se mueve hacia la izquierda
            for (y = 1; y < FIL; y++)
            {
                for (x = COL - 1; x >= 0; x--)
                {
                	// Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                	if (mapa[y][1] == 4)
                    {
                		dir = 1; // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                    }
                	// Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                	else if (mapa[y][x - 1] == -1 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        mapa[y][x - 1] = 0;
                        swap(mapa, x, y, x - 1, y);
                        x--;
                    }
                	// Cambia la posición del enemigo
                    else if (mapa[y][x - 1] == 0 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        swap(mapa, x, y, x - 1, y);
                        x--;
                    }
                }
            }
        }
        usleep(0500000);
    }
}

/* FUNCIÓN ALIEN_MOVEMENT_V
 * BRIEF: mueve verticalmente a los aliens
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * fil: (int) fila inicial
 * col: (int) columna inicial
 * return: (void)
 */
static void alien_movement_v(int mapa[][COL])
{
    int x, y;
    // se mueve hacia abajo
    for (x = 0; x < COL; x++)
    {
        for (y = 1; y < FIL; y ++)
        {
            if (mapa[y + 1][x] == -1 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
            {
                mapa[y + 1][x] = 0;
                swap(mapa, x, y, x, y + 1);
                y++;
            }
            else if (mapa[y + 1][x] == 0 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
            {
                swap(mapa, x, y, x, y + 1);
                y++;
            }
        }
    }
    usleep(1000000);
}

static void swap(int mapa[][COL], int x1, int y1, int x2, int y2)
{
    int aux = mapa[y1][x1];
    mapa[y1][x1] = mapa[y2][x2];
    mapa[y2][x2] = aux;
}

void final_boss_movement(int mapa[][COL])
{
    int x, y, dir = 5, flag = 0;
    //srand(time(NULL));
    //dir = rand() % 3 - 1;
    // se mueve hacia la derecha
    usleep(3000000);

    while (1)
    {
        if (dir >= 0)
        {

            for (y = 1; y < FIL; y++)
            {
                for (x = 0; x < COL; x++)
                {
                    // Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                    if (mapa[y][COL - 2] == 5 && !flag)
                    {
                        dir = -1; // Hace el cambio de dirección
                        flag++;   // hace que llegue al otro extremo y desaparezca
                    }
                    // Elimina al enemigo
                    else if (mapa[y][COL - 2] == 5 && flag)
                    {
                        mapa[y][COL - 2] = 0; // hace que no haya mas enemigo
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x] == 5)
                    {
                        swap(mapa, x, y, x + 1, y);
                        x++;
                    }
                }
            }
        }
        else
        { // Se mueve hacia la izquierda
            for (y = 1; y < FIL; y++)
            {
                for (x = COL - 1; x >= 0; x--)
                {
                    if (mapa[y][0] == 4 && !flag)
                    {
                        dir = 1;
                        flag++;
                    }
                    else if (mapa[y][0] == 5 && flag)
                    {
                        mapa[y][0] = 0;
                    }
                    else if (mapa[y][x] == 5)
                    {
                        swap(mapa, x, y, x - 1, y);
                        x--;
                    }
                }
            }
        }
        usleep(500000);
    }
}
