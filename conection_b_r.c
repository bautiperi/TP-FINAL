#include "conection_b_r.h"
#include <unistd.h>

/*IDENTIFICACIÓN EN EL MAPA:
- -1 (-2 en Rasp) = BARRERA
- 0 = Espacio
- 1  = Jugador
- 2 a 4 = Enemigo
- 5 = Boss
- 6(jugador) y 7(enemigos) = Disparos*/

void obj_vis(int mapa[][COL], int vidas)
{
    int gamer, shields, boss;
    unsigned int x, y;
    dcoord_t coords, aux;

    while (1)
    {
        gamer = 0;
        shields = 0;
        boss = 0;
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
                else if (mapa[y][x] == 4 || mapa[y][x] == 3 || mapa[y][x] == 2)
                {
                    aliens_vis(coords);
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
}

void display_collision(coord_t coord_1, int obj)
{
    dcoord_t coord;
    coord.x = coord_1.x;
    coord.y = coord_1.y;
    // vidas de los escudos (2 cada uno)
    static int barrier_1 = 2, barrier_2 = 2, barrier_3 = 2, barrier_4 = 2;
    switch (obj)
    {
    case BARRIER:         // BARRERA: -1
        if (coord.x == 1) // BARRERA 1
        {
            barrier_1--; // resta una vida
            shields_life(barrier_1, coord);
        }
        else if (coord.x == 5) // BARRERA 2
        {
            barrier_2--;
            shields_life(barrier_2, coord);
        }
        else if (coord.x == 9) // BARRERA 3
        {
            barrier_3--;
            shields_life(barrier_3, coord);
        }
        else if (coord.x == 13) // BARRERA 4
        {
            barrier_4--;
            shields_life(barrier_4, coord);
        }
        break;
    case JUGADOR: // JUGADOR: 1
        gamer_shot(coord);
        break;
    case ALIEN_2: // ALIEN
    case ALIEN_3: // ALIEN
    case ALIEN_4: // ALIEN
        aliens_death(coord);
        break;
    case BOSS: // BOSS: 5
        final_boss_shot(coord);
        break;
    default:
        break;
    }
}