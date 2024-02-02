//------------------------------------------------------------------------------------//
#include "back_player.h"
#include "back_aux.h"
#include "back_enemy.h"
#include "back_score.h"

// LIBRERIAS
#include <unistd.h>
#include <pthread.h>

// Variable global de main.c (flag para threads)
extern int flag_game_update;

// Variable global que establece la cantidad de disparos que puede efectuar
int flag_gamer_shot = 150;
//------------------------------------------------------------------------------------//

void gamer_movement(int mapa[][COL], int dir)
{
    int x, y = POS_Y_PL;

    for (x = 0; x < COL; x++)
    {
        if (mapa[y][x] == JUGADOR && mapa[y][x + dir] == FIRE_EN)
        {
            mapa[y][x] = 0;
            life_updater(mapa);
        }
        else if (mapa[y][x] == JUGADOR && (x + dir > 0) && (x + dir < R_BORDER))
        {
            swap(mapa, x, y, x + dir, y);
            x++;
#ifdef RASPBERRY
            usleep(80000);
#endif
        }
    }
}

void *gamer_fire(void *arg)
{
    if (flag_gamer_shot == 0)
    {
        return NULL;
    }
    else
    {
        flag_gamer_shot--;
    }

    int(*mapa)[COL] = (int(*)[COL])arg;

    int x, y = POS_Y_PL, stop = 1;
    int pos_x;

    // Busca la posición del jugador al momento del disparo, cuando lo encuentra, enciende un flag para detener el loop y guardar la posición
    for (x = 0; stop && x < COL; x++)
    {
        if (mapa[y][x] == JUGADOR)
        {
            mapa[y - 1][x] = FIRE_PL;
            stop = 0;
            pos_x = x;
        }
    }

    int eureka = 1;

    // Empieza a mover el disparo por el mapa, en caso de encontrar un obstáculo lo destruye y se elimina el disparo
    for (y--; y >= 1 && eureka; y--)
    {
        usleep(150000);

        if (mapa[y - 1][pos_x] == SPACE)
        {
            swap(mapa, pos_x, y, pos_x, y - 1);
        }
        else if (mapa[y - 1][pos_x] != SPACE)
        {
            eureka = 0;
            // Si es una barrera, la destruye y borra al disparo del mapa

            if (mapa[y - 1][pos_x] == BARRIER)
            {
                // Destruye la barrera
                mapa[y - 1][pos_x] = SPACE;
                // Elimina el disparo
                mapa[y][pos_x] = SPACE;
            }
            // Si es un enemigo, destruye el disparo y llama a la función encargada de analizar si el enemigo se elimina o no
            // tmb llama a la función score_updater para sumarle los puntos al jugador
            else if (mapa[y - 1][pos_x] != SPACE)
            {
                // Evita que se puedan mover los enemigos al momento de ser detectados, para lograr evitar errores
                flag_game_update = 0;

                IMPACT_X = pos_x;
                IMPACT_Y = y - 1;

                pthread_t impact_up;

                pthread_create(&impact_up, NULL, impact_updater, mapa);

                score_updater(mapa, mapa[y - 1][pos_x]);

                enemy_life(pos_x, y - 1, mapa); // función que decide si se elimina o no el enemigo

                mapa[y][pos_x] = SPACE;

                flag_game_update = 1;

                flag_gamer_shot++;
                pthread_exit(NULL);
            }
        }
        else if (y == 1 && mapa[y - 1][pos_x] == SPACE)
        {
            mapa[y][pos_x] = SPACE;
            flag_gamer_shot++;
            pthread_exit(NULL);
        }
    }

    flag_gamer_shot++;
    pthread_exit(NULL);
}

int life_updater(int mapa[][COL])
{
    LIVES--;
    if (LIVES == 0)
    {
        return 1;
    }
    else
    {
        SPAWN_POINT = JUGADOR;
        return 0;
    }
}