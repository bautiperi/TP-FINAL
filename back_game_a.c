#include "back_game_a.h"

static void alien_movement_v(int mapa[][COL], int fil, int col);
static void swap(int mapa[][COL], int fil1, int col1, int fil2, int col2);

void alien_movement_h(int mapa[][COL], int fil, int col)
{
    int x, y;
    static int dir = 1;
    // se mueve hacia la derecha
    if (dir == 1)
    {
        for (y = fil; y < 15; y++)
        {
            for (x = col; x < COL - 1; x++)
            {
                swap(mapa, y, x, y, x + 1);
            }
        }
        dir *= -1;
        // alien_movement_v(mapa, fil, col);
    }
    else
    { // se mueve hacia la izquierda
        for (y = col; y <= 5; y++)
        {
            for (x = COL - 1; x >= 0; x -= 2)
            {
                swap(mapa, y, x, y, x - 1);
            }
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
static void alien_movement_v(int mapa[][COL], int fil, int col)
{
    int x, y;
    // se mueve hacia abajo
    for (y = fil; y < COL; y++)
    {
        for (x = col; x < 22; x -= 2)
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
}

static void swap(int mapa[][COL], int fil1, int col1, int fil2, int col2)
{
    int aux = mapa[fil1][col1];
    mapa[fil1][col1] = mapa[fil2][col2];
    mapa[fil2][col2] = aux;
}
