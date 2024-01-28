#include "back_game_a.h"

#include "back_aux_a.h"
#include "back_score_a.h"

#include <unistd.h>
#include <time.h>
#include <stdlib.h>

//Variable global que sirve como flag para detener la ejecución de los threads
// 0 -> Falso, están en pausa | 1 -> Ejecutan | 2 -> Exit threads
int flag_game_update = 0;

static void alien_movement_v(int mapa[][COL]);

/* FUNCIÓN ALIEN_MOVEMENT_H
 * BRIEF: mueve horizontalmente a el final boss
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * dir: (int) direccion del movimiento (izq = -1, der = 0 o 1)
 * return: (void)
 */
static void final_boss_movement(int mapa[][COL], int dir);

void * alien_movement (void * arg)
{
	int (*mapa)[COL] = (int (*)[COL])arg;

    int x, y;
    int dir = 1, flag = 0;
    // se mueve hacia la derecha
    usleep(2000000);

    while (1)
    {
    	//Pone el thread "en pausa"
    	while (flag_game_update == 0){

    	}
    	//Termina la ejecución del thread
    	if(flag_game_update == 2){
    		return NULL;
    	}

    	if (flag == 1)
        {
            alien_movement_v(mapa);
            flag = 0;
        }
        else if (dir == 1)
        {

            for (y = 1; y < FIL; y++)
            {
                for (x = 0; x < COL; x++)
                {
                    // Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                    if (enemy_checker(COL - 2, y, mapa))
                    {
                        dir = -1; // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                    }
                    // Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                    else if (mapa[y][x + 1] == BARRIER && (enemy_checker(x, y, mapa)))
                    {
                        mapa[y][x + 1] = SPACE;
                        swap(mapa, x, y, x + 1, y);
                        x++;
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x + 1] == SPACE && (enemy_checker(x, y, mapa)))
                    {
                        swap(mapa, x, y, x + 1, y);
                        x++;
                    }
                    //Si al momento de querer cambiar de lugar el enemigo y justo pasa un disparo, elimina al enemigo y llama a score_updater
                    else if (mapa[y][x + 1] == FIRE_PL && (enemy_checker(x, y, mapa)))
                    {
                    	score_updater(mapa, mapa[y][x]);
                    	mapa[y][x] = 0;
                    	mapa[y][x + 1] = 0;
                    	x++;
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
                    if (enemy_checker(1, y, mapa))
                    {
                        dir = 1;  // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                    }
                    // Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                    else if (mapa[y][x - 1] == BARRIER && enemy_checker(x, y, mapa))
                    {
                        mapa[y][x - 1] = SPACE;
                        swap(mapa, x, y, x - 1, y);
                        x--;
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x - 1] == SPACE && enemy_checker(x, y, mapa))
                    {
                        swap(mapa, x, y, x - 1, y);
                        x--;
                    }
                    //Si al momento de querer cambiar de lugar el enemigo y justo pasa un disparo, elimina al enemigo y llama a score_updater
                    else if (mapa[y][x - 1] == FIRE_PL && (enemy_checker(x, y, mapa)))
                    {
                    	score_updater(mapa, mapa[y][x]);
                    	mapa[y][x] = 0;
                        mapa[y][x - 1] = 0;
                        x++;
                    }
                }
            }
        }
        usleep(1500000);
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
            //Si un enemigo llega a esta altura, el jugador ha perdido el juego
        	if(y == FIL - 3 && enemy_checker(x, y, mapa)){
            	LIFES = 0;
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
    usleep(1000000);
}

void * final_boss_creation(void *arg)
{
	//Pone el thread "en pausa"
	while (flag_game_update == 0){

	}
	//Termina la ejecución del thread
	if(flag_game_update == 2){
	    return NULL;
	}

	int (*mapa)[COL] = (int (*)[COL])arg;

    usleep(15000000);

    srand(time(NULL));
    int dir = rand() % 3 - 1;
    // si dir>=0 el enemigo aparece a la izquierda del mapa en direccion a la derecha
    if (dir >= 0)
    {
        mapa[3][0] = BOSS;
    }
    // si dir = -1 el enemigo aparece a la derecha del mapa en direccion a la izquierda
    else
    {
        mapa[3][COL - 1] = BOSS;
    }
    final_boss_movement(mapa, dir);

    return NULL;
}

static void final_boss_movement(int mapa[][COL], int dir)
{
    int x, y;

    while (1)
    {
        //  se mueve hacia la derecha
        if (dir >= 0)
        {
            for (y = 1; y < FIL; y++)
            {
                for (x = 0; x < COL; x++)
                {
                    // Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                    // Elimina al enemigo
                    if (mapa[y][COL - 1] == BOSS)
                    {
                        mapa[y][COL - 1] = SPACE; // hace que no haya mas enemigo
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x] == BOSS)
                    {
                        swap(mapa, x, y, x + 1, y);
                        x++;
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
                    if (mapa[y][0] == BOSS)
                    {
                        mapa[y][0] = SPACE;
                    }
                    else if (mapa[y][x] == BOSS)
                    {
                        swap(mapa, x, y, x - 1, y);
                        x--;
                    }
                }
            }
        }
        usleep(500000);
    }
}

void gamer_movement(int mapa[][COL], int dir) // REVISAR: se mueve muy rapido? => avisar a cami ;)
{
    int x, y;
    for (y = 1; y < FIL; y++)
    {
        for (x = 0; x < COL; x++)
        {
            if (mapa[y][x] == JUGADOR && mapa[y][x + dir] == FIRE_EN)
            {
                mapa[y][x] = 0;
                life_updater(mapa);
            }
            else if(mapa[y][x] == JUGADOR && (x + dir > 0) && (x + dir < COL - 1))
            {
            	swap(mapa, x, y, x + dir, y);
            	x++;
            }
        }
    }
}

//Variable global que establece la cantidad de disparos que puede efectuar
int flag_gamer_shot = 4;

void * gamer_fire(void * arg)
{
	if(flag_gamer_shot == 0){
		return NULL;
	}
	else{
		flag_gamer_shot--;
	}

	int (*mapa)[COL] = (int (*)[COL])arg;

    int x, y = 28, stop = 1;
    int pos_x;

    // Busca la posición del jugador al momento del disparo, cuando lo encuentra, enciende un flag para detener el loop y guardar la posición
    for (x = 0; stop && x < COL; x++)
    {
        if (mapa[y][x] == 1)
        {
            mapa[y - 1][x] = FIRE_PL;
            stop = 0;
            pos_x = x;
        }
    }

    int eureka = 1;

    // Empieza a mover el disparo por el mapa, en caso de encontrar un obstáculo lo destruye y se elimina el disparo
    for (y--; y > 1 && eureka; y--)
    {
        usleep(150000);


        if (mapa[y - 1][pos_x] == SPACE)
        {
            swap(mapa, pos_x, y, pos_x, y - 1);
        }
        else if (y - 1 < 0)
        {
            mapa[y][pos_x] = SPACE;
        }
        else
        {
            eureka = 0;
            // Si es una barrera, la destruye y borra al disparo del mapa

            if (mapa[y - 1][pos_x] == BARRIER)
            {
                //Destruye la barrera
            	mapa[y - 1][pos_x] = SPACE;
                //Elimina el disparo
                mapa[y][pos_x] = SPACE;
            }
            //Si es un enemigo, destruye el disparo y elimina al enemigo, tmb llama a la función score_updater para sumarle los puntos al jugador
            else if (mapa[y - 1][pos_x] != SPACE)
            {
            	//Evita que se puedan mover los enemigos al momento de ser detectados, para lograr evitar errores
            	flag_game_update = 0;

            	score_updater(mapa, mapa[y - 1][pos_x]);

            	mapa[y - 1][pos_x] = SPACE;

            	mapa[y][pos_x] = SPACE;

            	flag_game_update = 1;

            }
        }
    }

    flag_gamer_shot++;
    return NULL;
}

void * enemy_fire(void * arg) // Genera los disparos enemigos
{
	int (*mapa)[COL] = (int (*)[COL])arg;

	int x, y, shot, xb, eureka, recorre_fil, recorre_col;
	time_t t;
	srand((unsigned) time(&t));

	while(1)
	{
		//Pone el thread "en pausa"
		while (flag_game_update == 0){

		}
		//Termina la ejecución del thread
		if(flag_game_update == 2){
			return NULL;
		}

		recorre_col = rand() % 4 + 1;
		for (x = 0; x < 32; x+=recorre_col) // Recorre el area donde se encuentran los aliens
		{
			recorre_fil = rand() % 3 + 1;
			for  (y = 22; y > 0; y-=recorre_fil)
			{
				if (enemy_checker(x, y, mapa)) // Verifica que haya aliens para que disparen
				{
					shot = rand() % 100 +1;
					if(shot < 15) // Genera disparos en una cantidad determinada de las iteraciones
					{
						mapa[y + 1][x] = FIRE_EN; // Crea la bala enemiga
						xb = x; // Guarda la coordenada x del disparo
						eureka = 1; // Crea un flag

						for (y++; y < FIL  && eureka; y++) // Empieza a mover el disparo por el mapa
						{
							usleep(80000);

							if (mapa[y + 1][xb] == SPACE) // Si la bala tiene el camino despejado avanza
							{
								swap(mapa, xb, y, xb, y + 1);
							}
							else if (enemy_checker(xb, y + 1, mapa)) // Si la bala se encuentra con otro alien hace que dispare ese alien
							{
								mapa[y][xb] = SPACE;
								y+=2;
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
								else if (mapa[y + 1][xb] == JUGADOR || mapa[y + 1][xb-1] == JUGADOR || mapa[y + 1][xb+1] == JUGADOR) // Si la bala impacta al jugador
								{
									mapa[y][xb] = SPACE;

									//Para mostrar el impacto en el front
									IMPACT = 1; //Indica que hubo un impacto
									IMPACT_X = xb;
									IMPACT_Y = y +1;

									mapa[y+1][xb] = SPACE;
									mapa[y+1][xb+1] = SPACE;
									mapa[y+1][xb-1] = SPACE;
									life_updater(mapa);

									IMPACT = 0;
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
}


