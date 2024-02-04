//------------------------------------------------------------------------------------------------------------------//
#include "back_map.h"

// PROTOTIPOS DE FUNCIONES PRIVADAS

/* FUNCIÓN BARRIER_DIFF
 * BRIEF: Se encarga de determinar la cantidad y tamaño de las barreras a poner
 * diff: (const int) Es la dificultad que seleccionó el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
static void barrier_diff(const int diff, int mapa[][COL]);

/* FUNCIÓN BARRIER_GEN
 * BRIEF: Se encarga de generar barreras del tamaño deseado en una determinada posición.
 * x: (int) Posición x de inicio (debe ser la sup. izq.)
 * y: (int) Posición y de inicio (debe ser la sup. izq)
 * width: (int) Ancho deseado
 * heigth: (int) Alto deseado
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
static void barrier_gen(const int x, const int y, const int width, const int heigth, int mapa[][COL]);

/*FUNCION SHIPS_CREATE
 * BRIEF: Se encarga de posicionar los enemigos en el mapa
 * diff: (const int) Indica el nivel de dificultad seleccionado por el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * Return: (void)
 */
static void ships_create(int diff, int mapa[][COL]);

/* FUNCIÓN SPAWN_GEN
 * BRIEF: Crea en el mapa los enemigos según la dificultad
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * ini: (coord_t) Esquina superior izquierda donde comienza a ubicarse los aliens
 * desp: (coord_t) Esquina inferior derecha, totaliza el desplazamiento de la ubicación de los aliens
 * type_of_enemy: (int) Es el tipo de enemigo a asignar en el espacio entre ini y desp
 * return: (void)
 */
static void spawn_gen(int mapa[][COL], coord_t ini, coord_t desp, int type_of_enemy);

// Se usa y para las filas y x para las columnas, así coincide con los displays
void map_def(const int diff, int mapa[][COL], int score)
{

	// Guarda la dificultad en el primer elemento de la matriz
	int x, y;

	// Loop que puebla de "espacio" la matriz
	for (y = 0; y < FIL; y++)
	{
		for (x = 0; x < COL; x++)
		{

			mapa[y][x] = SPACE;
		}
	}

	// Si el modo es el normal, se regeneran las barriers y las vidas
	if (score == 0 || diff == NORMAL || diff == RASP)
	{
		// Llama a la función encargada de crear los obstáculos
		barrier_diff(diff, mapa);
		// Si el modo es extreme, solo le dá una vida
		if (diff == EXTREME)
		{
			LIVES = 1;
		}
		else
		{
			// Pone las 3 vidas del jugador
			LIVES = 3;
		}
	}

	if (score != 0)
	{
		SCORE = score;
	}

	// Llama a la función encargada de crear los enemigos
	ships_create(diff, mapa);

	// Guarda la dificultad seleccionada en el mapa
	DIFICULTAD = diff;

	// Ubica al jugador en el centro del mapa
	SPAWN_POINT = JUGADOR;
}

static void barrier_diff(const int diff, int mapa[][COL])
{
	int i;
	// Easy mode: Establece 4 barreras de 2x2 separadas por espacios de dos
	if (diff == RASP)
	{

		// Loop donde se llama a la función barrier_gen para crear las barreras/escudos
		for (i = 1; i < FIL; i += 4)
		{
			barrier_gen(i, 10, 2, 2, mapa);
		}
	}
	else if (diff == NORMAL || diff == HARD)
	{

		// Loop donde se llama a la función barrier_gen para crear las barreras/escudos
		for (i = 2; i < FIL; i += 8)
		{
			barrier_gen(i, 22, 4, 4, mapa);
		}
	}
	// EXTREME no genera barreras
}

static void barrier_gen(const int x, const int y, const int width, const int heigth, int mapa[][COL])
{

	int i, j;

	// Loop generador de las barreras
	for (j = 0; j < heigth; j++)
	{

		for (i = 0; i < width; i++)
		{
			mapa[y + j][x + i] = BARRIER; // Pone en la celda el valor deseado para indicar como barrera
		}
	}
}

static void ships_create(int diff, int mapa[][COL])
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