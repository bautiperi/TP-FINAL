#include "conection_b_r.h"

/*IDENTIFICACIÓN EN EL MAPA:
- -1 (-2 en Rasp) = BARRERA
- 0 = Espacio
- 1  = Jugador
- 2 a 4 = Enemigo
- 5 = Boss
- 6(jugador) y 7(enemigos) = Disparos*/

void obj_vis(int mapa[][COL], int vidas)
{
    int gamer = 0, shields = 0, aliens = 0, boss = 0;
    unsigned int x, y;
    dcoord_t coords, aux;
    lives_vis(vidas);
    for (x = 0; x < COL; x++)
    {
        for (y = 0; y < FIL; y++)
        {
            coords.x = x;
            coords.y = y;
            if (mapa[y][x] == 1 && !gamer)
            {
                gamer_vis(coords);
                gamer++;
            }
            else if (mapa[y][x] == 4 && !aliens)
            {
                coords.y = y + 4;
                aliens_vis(coords);
                aliens++;
            }
            else if (mapa[y][x] == 5 && !boss)
            {
                final_boss_vis(coords);
                boss++;
            }
            else if (mapa[y][x] == -1 && !shields)
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
            else if (mapa[y][x] == 6 || mapa[y][x] == 7)
            {
                disp_write(coords, D_ON);
                aux = coords;
                if (mapa[y][x] == 6)
                {
                    aux.y++;
                    disp_write(aux, D_OFF);
                }
                else
                {
                    aux.y--;
                    disp_write(aux, D_OFF);
                }
            }
        }
    }
    disp_update();
}
