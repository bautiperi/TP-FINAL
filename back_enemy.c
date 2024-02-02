//-----------------------------------------------------------------------------------------------------//
#include "back_enemy.h"
#include "back_map.h"
#include "back_player.h"
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
static void spawn_gen(int mapa[][COL], coord_t ini, coord_t desp, int type_of_enemy);

// Variable global de main.c (flag para threads)
extern int flag_game_update;
//-----------------------------------------------------------------------------------------------------//

// Variable global que incrementa la dificultad dentro del juego
float harder = 1;

void ships_create(int diff, int mapa[][COL])
{

    // Dependiendo de la dificultad, se crearan de diferentes formas los aliens
    if (diff == RASP)
    {
        int x, y, value;
        for (x = 2; x < 14; x += 2)
        {
            for (y = 3, value = ALIEN_4; y <= 7; y += 2, value--)
            {
                mapa[y][x] = value;
            }
        }
    }
    // Extreme: Todo dos filas y el primero 3?
    else if (diff == EXTREME)
    {
        int i, enemy = 4;

        for (i = 7; i < 16; i += 4)
        {
            // ini es la coordenada superior izq y desp es la coordenada inferior derecha
            coord_t ini = {4, i}, desp = {27, i + 3};

            // Se crean dos filas del alien seleccionado
            spawn_gen(mapa, ini, desp, enemy--);
        }
    }
    // Tradicional y hard: Crea una fila de alien_3, y dos filas por cada tipo de alien restante (alien_3 y alien_2)
    else
    {
        int i, enemy = 4;
        {
            coord_t ini = {4, 5}, desp = {27, 5};
            // Se crea una fila del alien "4"
            spawn_gen(mapa, ini, desp, enemy--);
        }

        // Primeras dos filas alien "4", fila 3 y 4 alien "3" y fila 5 y 6 alien "2"
        for (i = 7; i < 13; i += 4)
        {
            // ini es la coordenada superior izq y desp es la coordenada inferior derecha
            coord_t ini = {4, i}, desp = {27, i + 3};

            // Se crean dos filas del alien seleccionado
            spawn_gen(mapa, ini, desp, enemy--);
        }
    }
}

/* FUNCIÓN SPAWN_GEN
 * BRIEF: Crea en el mapa los enemigos según la dificultad
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * ini: (coord_t) Esquina superior izquierda donde comienza a ubicarse los aliens
 * desp: (coord_t) Esquina inferior derecha, totaliza el desplazamiento de la ubicación de los aliens
 * type_of_enemy: (int) Es el tipo de enemigo a asignar en el espacio entre ini y desp
 * return: (void)
 */
static void spawn_gen(int mapa[][COL], coord_t ini, coord_t desp, int type_of_enemy)
{

    int y, x;
    // Loop que pone los aliens separados por un espacio de una celda vertical y horizontal
    for (y = ini.y; y <= desp.y; y += 2)
    {

        for (x = ini.x; x <= desp.x; x += 2)
        {
            mapa[y][x] = type_of_enemy;
        }
    }
}

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
        any_enemy = 0; // Pone en 0 el contador

        // Pone el thread "en pausa"
        while (flag_game_update == 0)
        {
        }
        // Termina la ejecución del thread
        if (flag_game_update == 2)
        {
            pthread_exit(NULL);
        }

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
                    if (enemy_checker(R_BORDER - 1, y, mapa))
                    {
                        dir = -1; // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                        any_enemy++;
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
                        score_updater(mapa, mapa[y][x]);
                        enemy_life(x, y, mapa); // Decide si el alien vive o no
                        mapa[y][x + 1] = 0;     // Destruye la bala
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
                        score_updater(mapa, mapa[y][x]);
                        enemy_life(x, y, mapa);
                        mapa[y][x - 1] = 0;
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

        usleep((rand() % 6 + 10) * 1000000);

        int dir = rand() % 3 - 1;
        // si dir>=0 el enemigo aparece a la izquierda del mapa en direccion a la derecha
        if (dir >= 0)
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
        // si dir = -1 el enemigo aparece a la derecha del mapa en direccion a la izquierda
        else
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
 * dir: (int) direccion del movimiento (izq = -1, der = 0 o 1)
 * return: (void)
 */
static void final_boss_movement(int mapa[][COL], int dir, int y)
{
    int x;

    //  se mueve hacia la derecha
    if (dir >= 0)
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
            else if (mapa[y][x] == BOSS)
            {
                swap(mapa, x, y, x + 1, y);
            }
            usleep((int)(250000 / (harder / 2)));
        }
    }
    else
    { // Se mueve hacia la izquierda

        for (x = COL - 1; x >= 0; x--)
        {
            if (mapa[y][0] == BOSS)
            {
                mapa[y][0] = SPACE;
#ifdef RASPBERRY
                mapa[0][6] = 0;
#endif
            }
            else if (mapa[y][x] == BOSS)
            {
                swap(mapa, x, y, x - 1, y);
            }
            usleep((int)(250000 / (harder / 2)));
        }
    }
}

void *enemy_fire(void *arg) // Genera los disparos enemigos
{
    int(*mapa)[COL] = (int(*)[COL])arg;

    int x, y, shot, xb, eureka, recorre_fil, recorre_col;
    time_t t;
    srand((unsigned)time(&t));

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

        recorre_col = rand() % 4 + 1;
        for (x = 0; x < COL; x += recorre_col) // Recorre el area donde se encuentran los aliens
        {
            recorre_fil = rand() % 3 + 1;
            for (y = FIL; y > 0; y -= recorre_fil)
            {
                if (enemy_checker(x, y, mapa)) // Verifica que haya aliens para que disparen
                {
                    shot = rand() % 100 + 1;
                    if (shot < (15 * harder)) // Genera disparos en una cantidad determinada de las iteraciones
                    {
                        mapa[y + 1][x] = FIRE_EN; // Crea la bala enemiga
                        xb = x;                   // Guarda la coordenada x del disparo
                        eureka = 1;               // Crea un flag

                        for (y++; y < FIL && eureka; y++) // Empieza a mover el disparo por el mapa
                        {
                            usleep(80000);

                            if (mapa[y + 1][xb] == SPACE) // Si la bala tiene el camino despejado avanza
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
                            else if (y + 1 == FIL) // Si la bala llega al borde inferior del mapa desaparece
                            {
                                mapa[y][xb] = SPACE;
                            }
                            else
                            {
                                eureka = 0;

                                if (mapa[y + 1][xb] == BARRIER) // Si se encuentra una barrera, la destruye y borra al disparo del mapa
                                {
                                    mapa[y + 1][xb] += 1;
                                    mapa[y][xb] = SPACE;
                                }
                                else if (mapa[y + 1][xb] == JUGADOR || mapa[y + 1][xb - 1] == JUGADOR || mapa[y + 1][xb + 1] == JUGADOR) // Si la bala impacta al jugador
                                {
                                    mapa[y][xb] = SPACE;

                                    mapa[y + 1][xb] = SPACE;
                                    mapa[y + 1][xb + 1] = SPACE;
                                    mapa[y + 1][xb - 1] = SPACE;
                                    life_updater(mapa);

                                    IMPACT_X = xb;
                                    IMPACT_Y = y + 1;

                                    pthread_t impact_up;
                                    pthread_create(&impact_up, NULL, impact_updater, mapa);
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
}
