#include "conection_b_r.h"
#include <unistd.h>
#include <pthread.h>

/*IDENTIFICACIÓN EN EL MAPA:
- -1 (-2 en Rasp) = BARRERA
- 0 = Espacio
- 1  = Jugador
- 2 a 4 = Enemigo
- 5 = Boss
- 6(jugador) y 7(enemigos) = Disparos*/

void *obj_vis(void *arg)
{
    int(*mapa)[COL] = (int(*)[COL])arg;
    int gamer, shields, boss;
    unsigned int x, y;
    dcoord_t coords, aux;

    while (1)
    {
        // Pone el thread "en pausa"
        while (flag_game_update == 0)
        {
        }
        // Termina la ejecución del thread
        if (flag_game_update == 2)
        {
            return NULL;
        }

        shutdown_disp();
        gamer = 0;
        shields = 0;
        boss = 0;
        lives_vis(LIVES);
        for (x = 0; x < COL; x++)
        {
            for (y = 1; y < FIL; y++)
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
                    final_boss_vis(coords, mapa);
                    boss++;
                }
                else if (mapa[y][x] == -1 && shields <= 16)
                {
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
        if (IMPACT)
        {
            pthread_t colision;
            pthread_create(&colision, NULL, display_collision, mapa);
        }
        disp_update();
        usleep(33333);
    }
    pthread_exit(NULL);
}

void *display_collision(void *arg)
{
    int(*mapa)[COL] = (int(*)[COL])arg;
    int obj = mapa[IMPACT_Y][IMPACT_X];
    dcoord_t coord = {IMPACT_X, IMPACT_Y};
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