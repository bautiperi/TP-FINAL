//-----------------------------------------------------------------------------------------------------//
#include "back_enemy.h"
#include "back_map.h"
#include "back_aux.h"
#include "back_score.h"

// LIBRERIAS
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

// PROTOTIPOS FUNCIONES PRIVADAS
static void alien_movement_v(int mapa[][COL]);
/* FUNCIÓN FINAL_BOSS_MOVEMENT
 * BRIEF: Mueve horizontalmente a el final boss
 * mapa: (Matriz de ints) Es la matriz donde se desarrolla el juego
 * dir: (int) direccion del movimiento (izq = -1, der = 0 o 1)
 * return: (void)
 */
static void final_boss_movement(int mapa[][COL], int dir, int y);
/* FUNCIÓN SPAWN_GEN
 * BRIEF: Crea en el mapa los enemigos según la dificultad
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * ini: (coord_t) Esquina superior izquierda donde comienza a ubicarse los aliens
 * desp: (coord_t) Esquina inferior derecha, totaliza el desplazamiento de la ubicación de los aliens
 * type_of_enemy: (int) Es el tipo de enemigo a asignar en el espacio entre ini y desp
 * return: (void)
 */

// Variable global de main.c (flag para threads)
extern int flag_game_update;

//-----------------------------------------------------------------------------------------------------//

// Variable global que incrementa la dificultad dentro del juego
float harder = 1;

void *alien_movement(void *arg)
{
    int(*mapa)[COL] = (int(*)[COL])arg;

    int any_enemy;
    int x, y;
    int dir = 1, flag = 0;
    // se mueve hacia la derecha
    usleep(2000000 / harder);

    while (1)
    {

        // Pone el thread "en pausa"
        while (flag_game_update == 0)
        {
        }
        // Termina la ejecución del thread
        if (flag_game_update == 2)
        {
            pthread_exit(NULL);
        }

        any_enemy = 0; // Pone en 0 el contador

        if (flag == 1)
        {
            alien_movement_v(mapa);
            flag = 0;
            any_enemy++;
        }
        else if (dir == 1)
        {

            for (y = 1; y < FIL; y++)
            {
                for (x = 0; x < COL; x++)
                {
                    // Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                    if (enemy_checker(R_BORDER, y, mapa))
                    {
                        dir = -1; // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                        any_enemy++;
                    }
                    // Verifica si dos aliens se amontonan y los separa
                    else if ((enemy_checker(x, y, mapa)) && (enemy_checker(x, y + 1, mapa)))
                    {
                    	swap(mapa, x, y + 1, x, y + 2); // Separa los aliens
                    	swap(mapa, x, y, x + 1, y); // Mueve el alien de arriba a la derecha
                    	swap(mapa, x, y + 2, x + 1, y + 2); // Mueve el alien de abajo a la derecha
                    }
                    // Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                    else if (mapa[y][x + 1] == BARRIER && (enemy_checker(x, y, mapa)))
                    {
                        mapa[y][x + 1] = SPACE;
                        swap(mapa, x, y, x + 1, y);
                        x++;
                        any_enemy++;
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x + 1] == SPACE && (enemy_checker(x, y, mapa)))
                    {
                        swap(mapa, x, y, x + 1, y);
                        x++;
                        any_enemy++;
                    }
                    // Si al momento de querer cambiar de lugar el enemigo y justo pasa un disparo, elimina al enemigo y llama a score_updater
                    else if (mapa[y][x + 1] == FIRE_PL && (enemy_checker(x, y, mapa)))
                    {
                        flag_game_update = 0; // Para evitar errores, momentaneamente detiene el resto de threads
                        mapa[y][x + 1] = 0;     // Destruye la bala
                        score_updater(mapa, mapa[y][x]);
                        enemy_life(x, y, mapa); // Decide si el alien vive o no
                        swap(mapa, x, y, x + 1, y);
                        x++;
                        flag_game_update = 1; // Vuelve a habilitar los threads
                    }
                }
            }
        }
        else
        { // Se mueve hacia la izquierda
            for (y = 1; y < FIL; y++)
            {
                for (x = COL - 1; x >= 0; x--)
                {
                    // Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                    if (enemy_checker(L_BORDER, y, mapa))
                    {
                        dir = 1;  // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                        any_enemy++;
                    }
                    // Verifica si dos aliens se amontonan y los separa
                    else if ((enemy_checker(x, y, mapa)) && (enemy_checker(x, y + 1, mapa)))
                    {
                    	swap(mapa, x, y + 1, x, y + 2); // Separa los aliens
                    	swap(mapa, x, y, x - 1, y); // Mueve el alien de arriba a la izquierda
                    	swap(mapa, x, y + 2, x - 1, y + 2); // Mueve el alien de abajo a la izquierda
                    }
                    // Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                    else if (mapa[y][x - 1] == BARRIER && enemy_checker(x, y, mapa))
                    {
                        mapa[y][x - 1] = SPACE;
                        swap(mapa, x, y, x - 1, y);
                        x--;
                        any_enemy++;
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x - 1] == SPACE && enemy_checker(x, y, mapa))
                    {
                        swap(mapa, x, y, x - 1, y);
                        x--;
                        any_enemy++;
                    }
                    // Si al momento de querer cambiar de lugar el enemigo y justo pasa un disparo, elimina al enemigo y llama a score_updater
                    else if (mapa[y][x - 1] == FIRE_PL && (enemy_checker(x, y, mapa)))
                    {
                        flag_game_update = 0; // Para evitar errores, momentaneamente detiene el resto de threads
                        mapa[y][x - 1] = 0;
                        score_updater(mapa, mapa[y][x]);
                        enemy_life(x, y, mapa);
                        swap(mapa, x, y, x - 1, y);
                        x--;
                        flag_game_update = 1; // Vuelve a habilitar los threads
                    }
                }
            }
        }

        // Si al recorrer todo el mapa no se encontraron enemigos, se crean más y se incrementa la dificultad
        if (any_enemy == 0)
        {
            map_def(DIFICULTAD, mapa, SCORE);
            harder++;
        }
        else
        {
            any_enemy = 0;
        }

        usleep(1500000 / harder);
    }
}

/* FUNCIÓN ALIEN_MOVEMENT_V
 * BRIEF: mueve verticalmente a los aliens
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * fil: (int) fila inicial
 * col: (int) columna inicial
 * return: (void)
 */
static void alien_movement_v(int mapa[][COL])
{
    int x, y;

    // se mueve hacia abajo
    for (x = 0; x < COL; x++)
    {
        for (y = 1; y < FIL; y++)
        {
            // Si un enemigo llega a esta altura, el jugador ha perdido el juego
            if (y == FIL - 3 && enemy_checker(x, y, mapa))
            {
                LIVES = 0;
            }
            else if (mapa[y + 1][x] == BARRIER && enemy_checker(x, y, mapa))
            {
                mapa[y + 1][x] = SPACE;
                swap(mapa, x, y, x, y + 1);
                y++;
            }
            else if (mapa[y + 1][x] == SPACE && enemy_checker(x, y, mapa))
            {
                swap(mapa, x, y, x, y + 1);
                y++;
            }
        }
    }
    usleep(1000000 / harder);
}

void *final_boss_creation(void *arg)
{
    time_t t;
    srand((unsigned)time(&t));
    int(*mapa)[COL] = (int(*)[COL])arg;
    while (flag_game_update != 2) // Termina la ejecución del thread
    {
        // Pone el thread "en pausa"
        while (flag_game_update == 0)
        {
        }

        usleep((rand() % 6 + 10) * 1000000);

        int dir = rand() % 2;
        // si dir=0 el enemigo aparece a la izquierda del mapa en direccion a la derecha
        if (dir == 0)
        {
#ifdef RASPBERRY
            mapa[0][6] = 1;
            mapa[1][0] = BOSS;
            final_boss_movement(mapa, dir, 1);
#else
            mapa[3][0] = BOSS;
            final_boss_movement(mapa, dir, 3);
#endif
        }
        // si dir = 1 el enemigo aparece a la derecha del mapa en direccion a la izquierda
        else if (dir == 1)
        {
#ifdef RASPBERRY
            mapa[0][6] = 1;
            mapa[1][COL - 1] = BOSS;
            final_boss_movement(mapa, dir, 1);
#else
            mapa[3][COL - 1] = BOSS;
            final_boss_movement(mapa, dir, 3);
#endif
        }
    }
    pthread_exit(NULL);
}

/* FUNCIÓN FINAL_BOSS_MOVEMENT
 * BRIEF: Mueve horizontalmente a el final boss
 * mapa: (Matriz de ints) Es la matriz donde se desarrolla el juego
 * dir: (int) direccion del movimiento (izq = 1, der = 0)
 * return: (void)
 */
static void final_boss_movement(int mapa[][COL], int dir, int y)
{
    int x;

    //  se mueve hacia la derecha
    if (dir == 0)
    {

        for (x = 0; x < R_BORDER; x++)
        {
            // Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
            // Elimina al enemigo
            if (mapa[y][R_BORDER - 1] == BOSS)
            {
                mapa[y][R_BORDER - 1] = SPACE; // hace que no haya mas enemigo
#ifdef RASPBERRY
                mapa[0][6] = 0;
#endif
            }
            // Cambia la posición del enemigo
            else if (mapa[y][x] == BOSS && mapa[y][x + 1] == SPACE)
            {
                swap(mapa, x, y, x + 1, y);
            }
            else if (mapa[y][x] == BOSS && mapa[y][x + 1] == FIRE_PL)
            {
                flag_game_update = 0; 			// Para evitar errores, momentaneamente detiene el resto de threads
                score_updater(mapa, mapa[y][x]);
                mapa[y][x + 1] = 0; 			// Elimina el disparo
                mapa[y][x] = 0;					// Elimina el boss
                flag_game_update = 1; 			// Vuelve a habilitar los threads
            }
#ifdef RASPBERRY
            usleep((int)(450000 / (harder / 2)));
#else
            usleep((int)(150000 / (harder / 2)));
#endif
        }
    }
    else if (dir == 1)
    { // Se mueve hacia la izquierda

        for (x = COL - 1; x >= 0; x--)
        {
            if (x == 0 && mapa[y][x] == BOSS) //(mapa[y][0] == BOSS)
            {
                mapa[y][0] = SPACE;
#ifdef RASPBERRY
                mapa[0][6] = 0;
#endif
            }
            else if (mapa[y][x] == BOSS && mapa[y][x - 1] == SPACE)
            {
                swap(mapa, x, y, x - 1, y);
            }
            else if (mapa[y][x] == BOSS && mapa[y][x - 1] == FIRE_PL)
            {
                flag_game_update = 0; // Para evitar errores, momentaneamente detiene el resto de threads
                score_updater(mapa, mapa[y][x]);
                mapa[y][x - 1] = 0; // Elimina el disparo
                mapa[y][x] = 0; // Elimina el boss
                flag_game_update = 1; // Vuelve a habilitar los threads
            }
        }
    }
}

void *enemy_fire(void *arg) // Genera los disparos enemigos
{
    int(*mapa)[COL] = (int(*)[COL])arg;

    int x, y, shot, xb, eureka, recorre_fil, recorre_col;
    time_t t;
    srand((unsigned)time(&t));

    while (flag_game_update != 2) // Termina la ejecución del thread
    {
        // Pone el thread "en pausa"
        while (flag_game_update == 0)
        {
        }

        recorre_col = rand() % 4 + 1;
        for (x = 0; x < COL; x += recorre_col) // Recorre el area donde se encuentran los aliens
        {
            recorre_fil = rand() % 3 + 1;
            for (y = FIL; y > 0; y -= recorre_fil)
            {
                if (enemy_checker(x, y, mapa)) // Verifica que haya aliens para que disparen
                {
                    shot = rand() % 100 + 1;
                    if (shot < 15) // Genera disparos en una cantidad determinada de las iteraciones
                    {
                        mapa[y + 1][x] = FIRE_EN; // Crea la bala enemiga
                        xb = x;                   // Guarda la coordenada x del disparo
                        eureka = 1;               // Crea un flag

                        for (y++; y < FIL && eureka; y++) // Empieza a mover el disparo por el mapa
                        {
                            usleep(80000);

                            if (y + 1 == FIL) // Si la bala llega al borde inferior del mapa desaparece
                            {
                                mapa[y][xb] = SPACE;
                            }
                            else if (mapa[y + 1][xb - 1] == JUGADOR) // Si la bala impacta al jugador en el costado izquierdo
                            {
                            	eureka = 0;

                            	mapa[y][xb] = SPACE;
                                mapa[y + 1][xb - 1] = SPACE;

                                IMPACT_X = xb - 1;
                                IMPACT_Y = y + 1;

                                pthread_t impact_up;
                                pthread_create(&impact_up, NULL, impact_updater, mapa);

                                life_updater(mapa);
                            }
                            else if (mapa[y + 1][xb + 1] == JUGADOR) // Si la bala impacta al jugador en el costado derecho
                            {
                            	eureka = 0;

                            	mapa[y][xb] = SPACE;
                                mapa[y + 1][xb + 1] = SPACE;

                            	IMPACT_X = xb + 1;
                                IMPACT_Y = y + 1;

                                pthread_t impact_up;
                                pthread_create(&impact_up, NULL, impact_updater, mapa);

                                life_updater(mapa);
                            }
                            else if (mapa[y][xb] == JUGADOR) // Si el jugador impacta una bala por la derecha
                            {
                            	eureka = 0;

                            	mapa[y][xb] = SPACE;
                                mapa[y][xb + 1] = SPACE;

                            	IMPACT_X = xb;
                                IMPACT_Y = y +1;

                                pthread_t impact_up;
                                pthread_create(&impact_up, NULL, impact_updater, mapa);

                                life_updater(mapa);
                            }
                            else if (mapa[y + 1][xb] == SPACE) // Si la bala tiene el camino despejado avanza
                            {
                                swap(mapa, xb, y, xb, y + 1);
                            }
                            else if (enemy_checker(xb, y + 1, mapa)) // Si la bala se encuentra con otro alien hace que dispare ese alien
                            {
                                mapa[y][xb] = SPACE;
                                y += 2;
                                mapa[y][xb] = FIRE_EN;
                                y--;
                            }
                            else
                            {
                                eureka = 0;

                                if (mapa[y + 1][xb] == BARRIER) // Si se encuentra una barrera, la destruye y borra al disparo del mapa
                                {
                                    mapa[y + 1][xb] += 1;
                                    mapa[y][xb] = SPACE;
                                }
                                else if (mapa[y + 1][xb] == JUGADOR )  // Si la bala impacta al jugador de frente
                                {
                                    mapa[y][xb] = SPACE;
                                    mapa[y + 1][xb] = SPACE;

                                    IMPACT_X = xb;
                                    IMPACT_Y = y + 1;

                                    pthread_t impact_up;
                                    pthread_create(&impact_up, NULL, impact_updater, mapa);

                                    life_updater(mapa);
                                }
                            }
                        }
                    }
                }
                recorre_fil = rand() % 3 + 1;
            }
            recorre_col = rand() % 4 + 1;
        }
    }

    pthread_exit(NULL);
}

void enemy_life(int x, int y, int mapa[][COL])
{
    time_t t;
    srand((unsigned)time(&t));

    // Si la dificultad del juego es tradicional o para Raspberry, se elimina el enemigo
    if (DIFICULTAD == NORMAL || DIFICULTAD == RASP)
    {
        mapa[y][x] = 0;
    }
    // Si la dificultad es HARD, hay un 50% de probabilidad de que muera o no
    // Si la dificultad es EXTREME, hay un 60% de probabilidad de que no muera
    // Si es un boss, lo elimina independientemente de la dificultad
    else if (DIFICULTAD == EXTREME || DIFICULTAD == HARD)
    {
        int i = rand() % 10 + 1;
        if (i <= (7 - DIFICULTAD) || mapa[y][x] == BOSS)
        {
            mapa[y][x] = 0;
        }
    }

    if(mapa[y][x] == FIRE_PL){
    	mapa[y][x] = 0;
    }
}
