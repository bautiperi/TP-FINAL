#include "back_game_a.h"

#include <unistd.h>

static void alien_movement_v(int mapa[][COL]);
static void swap(int mapa[][COL], int x1, int y1, int x2, int y2);

void alien_movement_h(int mapa[][COL])
{
    int x, y;
    int dir = 1, flag = 0;
    // se mueve hacia la derecha
    usleep(3000000);

    while(1){
    if (dir == 1)
    {

    	for (y = 1; y < FIL; y++)
            {
                for (x = 0; x < COL; x++)
                {
                	// Analiza si se llegó al extremo de la matriz, para evitar que los enemigos se "amontonen"
                	if( mapa[y][COL - 2] == 4){
                		dir = -1; //Hace el cambio de dirección
                		flag = 1; //Hace que al terminar de cambiar el resto de las filas, se llame a la función para el cambio vertical
                	}
                	//Si adelante había una barreba la "destruye" y continúa cambiando la posición del enemigo
                	else if (mapa[y][x + 1] == -1 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        mapa[y][x + 1] = 0;
                        swap(mapa, x, y, x + 1, y);
                        x++;
                    }
                	//Cambia la posición del enemigo
                    else if (mapa[y][x + 1] == 0 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                    {
                        swap(mapa, x, y, x + 1, y);
                        x++;
                    }

                	}
                }
            }
    else if (flag == 1) {
    	alien_movement_v(mapa);
    	flag = 0;
    }
    else
    { // Se mueve hacia la izquierda
         for (y = 1; y < FIL; y++)
            {
                for (x = COL - 1; x >= 0; x--)
                {
                	if( mapa[y][1] == 4){
                	    dir = 1;
                	    flag = 1;
                	}
                	else if (mapa[y][x - 1] == -1 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                	{
                	    mapa[y][x - 1] = 0;
                	    swap(mapa, x, y, x - 1, y);
                	    x--;
                	    }
                	else if (mapa[y][x - 1] == 0 && (mapa[y][x] == 2 || mapa[y][x] == 3 || mapa[y][x] == 4))
                	{
                	    swap(mapa, x, y, x - 1, y);
                	    x--;
                	}
                }
            }
    }
    usleep(2000000);
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
    for (y = 1; y < FIL; y++)
    {
        for (x = 0; x < COL; x += 2)
        {
            if (mapa[y + 1][x] == -1 && mapa[y][x] == 2)
            {
                mapa[y + 1][x] = 0;
                swap(mapa, y, x, y + 1, x);
            }
            else if (mapa[y + 1][x] == 0 && mapa[y][x] == 2)
            {
                swap(mapa, y, x, y + 1, x + 1);
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
