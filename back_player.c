//------------------------------------------------------------------------------------//
#include "back_player.h"
#include "back_aux.h"
#include "back_score.h"
#include "back_enemy.h"

// LIBRERIAS
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

// VARIABLES EXTERNAS
// Variable global de main.c (flag para threads)
extern int flag_game_update;
#ifndef RASPBERRY
extern int is_shooting;
#endif

// Variable global que establece la cantidad de disparos que puede efectuar
int flag_gamer_shot = 1500;
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
    if (flag_gamer_shot <= 0 && flag_game_update != 0)
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

    int eureka = 1; //flag que indica si encuentra un objeto (alien, boss, disparo enemigo o shield)

#ifndef RASPBERRY
    is_shooting = 0; // Reset the shooting flag
#endif

    // Empieza a mover el disparo por el mapa, en caso de encontrar un obstáculo lo destruye y se elimina el disparo
    for (y--; y >= T_BORDER && eureka && mapa[y][pos_x] == FIRE_PL; y--)
    {
        usleep(150000);
        // Avanza el disparo por el mapa
        if ((mapa[y - 1][pos_x] == SPACE) && y > T_BORDER)
        {
            swap(mapa, pos_x, y, pos_x, y - 1);
        }
        // Encuentra algo!
        else if ((mapa[y - 1][pos_x] != SPACE) && (y > T_BORDER))
        {
            eureka = 0;
            // Si es una barrera, la destruye y borra al disparo del mapa
            if (mapa[y - 1][pos_x] == BARRIER)
            {
                // Destruye la barrera
                mapa[y - 1][pos_x] = SPACE;
                // Elimina el disparo
                mapa[y][pos_x] = SPACE;

                flag_gamer_shot++;
                pthread_exit(NULL);
            }
            // Si es un enemigo, destruye el disparo y llama a la función encargada de analizar si el enemigo se elimina o no
            // tmb llama a la función score_updater para sumarle los puntos al jugador
            else if ((mapa[y - 1][pos_x] != SPACE))
            {
                // Evita que se puedan mover los enemigos al momento de ser detectados, para lograr evitar errores
                flag_game_update = 0;

                // Muestra los impactos en pantalla en allegro
#ifndef RASPBERRY
                if (mapa[y - 1][pos_x] != 6)
                {
                    IMPACT_X = pos_x;
                    IMPACT_Y = y - 1;

                    //crea un thread con un contador para la visualizacion de impactos
                    pthread_t impact_up;
                    pthread_create(&impact_up, NULL, impact_updater, mapa);
                }
#endif

                score_updater(mapa, mapa[y - 1][pos_x]);

                enemy_life(pos_x, y - 1, mapa); // función que decide si se elimina o no el enemigo

                mapa[y][pos_x] = SPACE;

                flag_game_update = 1;

                // Habilita la creación de otra bala
                flag_gamer_shot++;
                pthread_exit(NULL);
            }
        }
        else if (y <= T_BORDER && mapa[y][pos_x] == FIRE_PL)
        {
            mapa[y][pos_x] = SPACE;
            flag_gamer_shot++;
            pthread_exit(NULL);
        }
    }

    flag_gamer_shot++;
    pthread_exit(NULL);
}
