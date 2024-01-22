#include "conection_b_r.h"

/*IDENTIFICACIÓN EN EL MAPA:
- -1 (-2 en Rasp) = BARRERA
- 0 = Espacio
- 1  = Jugador
- 2 a 4 = Enemigo
- 5 = Boss
- 6 y 7 = Disparos*/

void polling(int mapa[][COL])
{
    int x, y, gamer = 0, shields = 0, aliens = 0, boss = 0;
    dcoord_t coords;
    for (x = 0; x < COL; x++)
    {
        for (y = 0; y < FIL; y++)
        {
            coords = {x, y};
            if (mapa[y][x] == 1 && !gamer)
            {
                gamer_vis(coords);
                gamer++;
            }
            else if (mapa[x][y] == 4 && !aliens)
            {
                coords.y = y + 4;
                aliens_vis(coords);
                aliens++;
            }
            else if (mapa[x][y] == 5 && !boss)
            {
                final_boss_vis(coords);
                boss++;
            }
            else if (mapa[x][y] == -1 && !shields)
            {
                coords.y++;
                shields_vis(coords);
                coords.x += 4;
                shields_vis(coords);
                coords.x += 4;
                shields_vis(coords);
                coords.x += 4;
                shields_vis(coords);
                shields++;
            }
        }
    }
}
