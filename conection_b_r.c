// INCLUDES
#include "conection_b_r.h"
#include "_defines.h"
#include "_defines_display_r.h"
#include "obj_r.h"
#include "aux_r.h"

// LIBRERIAS
#include <unistd.h>
#include <pthread.h>
#include "joydrv.h"
#include "disdrv.h"

/*IDENTIFICACIÓN EN EL MAPA:
- -1 = BARRERA
- 0 = Espacio
- 1  = Jugador
- 2 a 4 = Enemigo
- 5 = Boss
- 6(jugador) y 7(enemigos) = Disparos*/

void *obj_vis(void *arg)
{
    int(*mapa)[COL] = (int(*)[COL])arg;
    int gamer, shields, boss; // variables de confirmacion de visualizacion para que no hayan dos de lo mismo
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
        lives_vis(LIVES); // visualizacion de vidas
        for (x = 0; x < COL; x++)
        {
            for (y = 1; y < FIL; y++) // no analiza y = 0 porque ahi se guardan algunos flags
            {
                coords.x = x;
                coords.y = y;
                // PLAYER
                if (mapa[y][x] == JUGADOR && !gamer && x != 15 && x != 0)
                {
                    gamer_vis(coords);
                    gamer++;
                }
                // ALIENS
                else if ((mapa[y][x] == ALIEN_4 || mapa[y][x] == ALIEN_3 || mapa[y][x] == ALIEN_2) && x < COL && x >= 0 && y < FIL && y > 0)
                {
                    aliens_vis(coords);
                }
                // BOSS
                else if (mapa[y][x] == BOSS && !boss)
                {
                    final_boss_vis(coords, mapa);
                    boss++;
                }
                // BARRERAS
                else if (mapa[y][x] == BARRIER && shields <= 16 && x < COL && x >= 0 && y < FIL && y > 0)
                {
                    shields_vis(coords);
                    shields++;
                }
                // DISPAROS
                else if (mapa[y][x] == FIRE_PL || mapa[y][x] == FIRE_EN)
                {
                    disp_write(coords, D_ON);
                    aux = coords;
                    if (mapa[y][x] == FIRE_PL)
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
        usleep(66666);
    }
    pthread_exit(NULL);
}
