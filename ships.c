#include "ships.h"

void ships_gen(int mapa[][COL], int diff)
{
    int x, y, value;
    for (x = 2; x < 14; x++)
    {
        for (y = 3, value = ALIEN_4; y <= 7; y += 2, value--)
        {
            mapa[y][x] = value;
        }
    }
}
