#include "back_game_a.h"

#include <unistd.h>
#include <time.h>
#include <stdlib.h>

static void alien_movement_v(int mapa[][COL]);
static void swap(int mapa[][COL], int x1, int y1, int x2, int y2);
/* FUNCIÓN ALIEN_MOVEMENT_H
 * BRIEF: mueve horizontalmente a el final boss
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * dir: (int) direccion del movimiento (izq = -1, der = 0 o 1)
 * return: (void)
 */
static void final_boss_movement(int mapa[][COL], int dir);

void alien_movement(int mapa[][COL])
{
    int x, y;
    int dir = 1, flag = 0;
    // se mueve hacia la derecha
    usleep(2000000);

    while (1)
    {
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
                    if (mapa[y][COL - 2] == 4)
                    {
                        dir = -1; // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                    }
                    // Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                    else if (mapa[y][x + 1] == -1 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        mapa[y][x + 1] = 0;
                        swap(mapa, x, y, x + 1, y);
                        x++;
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x + 1] == 0 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
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
                    // Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                    if (mapa[y][1] == 4)
                    {
                        dir = 1;  // Hace el cambio de dirección
                        flag = 1; // Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                    }
                    // Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                    else if (mapa[y][x - 1] == -1 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        mapa[y][x - 1] = 0;
                        swap(mapa, x, y, x - 1, y);
                        x--;
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x - 1] == 0 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        swap(mapa, x, y, x - 1, y);
                        x--;
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
            if (mapa[y + 1][x] == -1 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
            {
                mapa[y + 1][x] = 0;
                swap(mapa, x, y, x, y + 1);
                y++;
            }
            else if (mapa[y + 1][x] == 0 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
            {
                swap(mapa, x, y, x, y + 1);
                y++;
            }
        }
    }
    usleep(1000000);
}

static void swap(int mapa[][COL], int x1, int y1, int x2, int y2)
{
    int aux = mapa[y1][x1];
    mapa[y1][x1] = mapa[y2][x2];
    mapa[y2][x2] = aux;
}

void final_boss_creation(int mapa[][COL])
{
    usleep(15000000);

	srand(time(NULL));
    int dir = rand() % 3 - 1;
    // si dir>=0 el enemigo aparece a la izquierda del mapa en direccion a la derecha
    if (dir >= 0)
    {
        mapa[3][0] = 5;
    }
    // si dir = -1 el enemigo aparece a la derecha del mapa en direccion a la izquierda
    else
    {
        mapa[3][COL - 1] = 5;
    }
    final_boss_movement(mapa, dir);
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
                    if (mapa[y][COL - 1] == 5)
                    {
                        mapa[y][COL - 1] = 0; // hace que no haya mas enemigo
                    }
                    // Cambia la posición del enemigo
                    else if (mapa[y][x] == 5)
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
                    if (mapa[y][0] == 5)
                    {
                        mapa[y][0] = 0;
                    }
                    else if (mapa[y][x] == 5)
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
    int x, y = 28; //HARDCODEADO PARA ALLEGRO

    for (x = 0; x < COL; x++){
    	if (mapa[y][x] == 1 && (x + dir >= 0) && (x + dir < COL - 1)){
    		swap(mapa, x, y, x + dir, y);
    		x++;
    	}
    }
}

void gamer_fire (int mapa[][COL]){
	int x, y = 28, stop = 1;
	int pos_x;

	//Busca la posición del jugador al momento del disparo, cuando lo encuentra, enciende un flag para detener el loop y guardar la posición
	for (x = 0; stop && x < COL; x++){
	    if (mapa[y][x] == 1){
	    	mapa[y - 1][x] = 6;
	    	stop = 0;
	    	pos_x = x;
	    }
	}

	int eureka = 1;

	//Empieza a mover el disparo por el mapa, en caso de encontrar un obstáculo lo destruye y se elimina el disparo
	for ( y-- ; y > 0 && eureka; y--){
		usleep(150000);

		if( mapa[y-1][pos_x] == 0){
			swap(mapa, pos_x, y, pos_x, y - 1);
		}
		else if ( y - 1 == 0){
			mapa[y][pos_x] = 0;
		}
		else {
			eureka = 0;
			//Si es una barrera, la destruye y borra al disparo del mapa

			if(mapa[y - 1][pos_x] == -1){
				mapa[y - 1][pos_x] += 1;
				mapa[y][pos_x] = 0;
			}
			else if(mapa [y - 1][pos_x] == 2){
				//Llamar a función para dar puntos
			}
			//Seguir para el resto de enemigos
		}
	}

}
