#include "ships.h"

void ships_gen(int mapa[][COL], int diff)
{
    int x, y, value;
    if (diff == RASP)
    {
        for (x = 1; x < 14; x++)
        {
            if (x % 2 == 0)
            {
                for (y = 5, value = ALIEN - 1; y < 8; y += 2, value--)
                {
                    mapa[y][x] = value;
                }
            }
            else
            {
                for (y = 4, value = ALIEN; y < 9; y += 2, value--)
                {
                    mapa[y][x] = value;
                }
            }
        }
    }
    else if (diff == EASY)
    {
        // completar para allegro
    }
}
