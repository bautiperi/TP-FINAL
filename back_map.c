//------------------------------------------------------------------------------------------------------------------//
#include "back_map.h"
#include "back_enemy.h"

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
//------------------------------------------------------------------------------------------------------------------//

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

/* FUNCIÓN BARRIER_DIFF
 * BRIEF: Se encarga de determinar la cantidad y tamaño de las barreras a poner
 * diff: (const int) Es la dificultad que seleccionó el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
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

/* FUNCIÓN BARRIER_GEN
 * BRIEF: Se encarga de generar barreras del tamaño deseado en una determinada posición.
 * x: (int) Posición x de inicio (debe ser la sup. izq.)
 * y: (int) Posición y de inicio (debe ser la sup. izq)
 * width: (int) Ancho deseado
 * heigth: (int) Alto deseado
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
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
