#include "back_game_a.h"

#include <unistd.h>

static void alien_movement_v(int mapa[][COL]);
static void swap(int mapa[][COL], int fil1, int col1, int fil2, int col2);

void alien_movement_h(int mapa[][COL])
{
    int x, y, col = COL;
    static int dir = 1;
    // se mueve hacia la derecha
    if (dir == 1)
    {
        while (col)
        {
            for (y = 1; y < FIL; y++)
            {
                for (x = 0; x < COL - 1; x++)
                {
                    if (mapa[y][x + 1] == -1 && mapa[y][x] == 2)
                    {
                        mapa[y][x + 1] = 0;
                        swap(mapa, y, x, y, x + 1);
                    }
                    else if (mapa[y][x + 1] == 0 && mapa[y][x] == 2)
                    {
                        swap(mapa, y, x, y, x + 1);
                    }
                }
            }
            col--;

            usleep(1000000);
        }
        dir *= -1;
        alien_movement_v(mapa);
    }
    else
    { // Se mueve hacia la izquierda
        while (col)
        {
            for (y = 1; y <= 5; y++)
            {
                for (x = COL - 1; x >= 0; x -= 2)
                {
                    if (mapa[y][x - 1] == -1 && mapa[y][x] == 2)
                    {
                        mapa[y][x + 1] = 0;
                        swap(mapa, y, x, y, x - 1);
                    }
                    else if (mapa[y][x - 1] == 0 && mapa[y][x] == 2)
                    {
                        swap(mapa, y, x, y, x - 1);
                    }
                }
            }
            col--;
            usleep(1000000);
        }
        dir *= -1;
        alien_movement_v(mapa, fil, col);
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
    for (y = fil; y < COL; y++)
    {
        for (x = col; x < 22; x -= 2)
        {
            if (mapa[y + 1][x] == -1 && mapa[y][x] == 2)
            {
                mapa[y + 1][x] = 0;
                swap(mapa, y, x, y + 1, x);
            }
            else if (mapa[y + 1][x] == 0 && mapa[y][x] == 2)
            {
                swap(mapa, y, x, y + 1, x + 1);
            }
        }
    }
    usleep(1000000);
}

static void swap(int mapa[][COL], int fil1, int col1, int fil2, int col2)
{
    int aux = mapa[fil1][col1];
    mapa[fil1][col1] = mapa[fil2][col2];
    mapa[fil2][col2] = aux;
}
