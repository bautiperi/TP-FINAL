//-----------------------------------------------------------------------------------------------------------------------------------------//
#include "back_score.h"

// LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// PROTOTIPOS FUNCIONES PRIVADAS
/* FUNCIÓN PLAYER_COMP
 * BRIEF: Función que se encarga de comparar el score de dos jugadores para saber cual es más alto, para que se ordene de mayor a menor
 * a: (puntero a void constante) Es el primer jugador (el de la izquierda)
 * b: (puntero a void constante) Es el segundo jugador (el de la derecha)
 * return: (int) Devuelve el valor de verdad para cambiar o no el orden de ambos jugadores
 */
static int player_comp(const void *a, const void *b);
//-----------------------------------------------------------------------------------------------------------------------------------------//

// String donde se almacena el nombre del jugador
char player_name[50] = "";

void score_updater(int mapa[][COL], int identifier)
{
	time_t t;
	srand((unsigned)time(&t));
	static int enemy_counter;
	// Dependiendo del enemigo al que se le pegó, se agregarán una determinada cantidad de puntos al score
	// También, dependiendo del modo de juego, se multiplicará más el score total
	if (identifier < 5)
	{
		SCORE += (identifier * 10) * (DIFICULTAD + 1);
		enemy_counter++;
	}
	else if (identifier == 5)
	{
		// Agrega en el score un nro aleatorio entre 50 y 100
		SCORE += ((rand() % 6 + 5) * 10) * (DIFICULTAD + 1);
	}
}

int score_saver(const int score)
{
	FILE *scoreboard = fopen("scoreboard.txt", "r");

	if (scoreboard == NULL)
	{
		fprintf(stderr, "No se pudo abrir el archivo donde se encuentra el score del juego! \n");
		return -1;
	}

	// Crea una matriz de jugadores del scoreboard
	player_t scores[10];

	// Lee todo el archivo
	int j;
	for (j = 0; j < 10; j++)
	{

		// Copia el nombre del jugador
		if (fscanf(scoreboard, "%s %d", scores[j].name, &scores[j].score) != 2)
		{
			fprintf(stderr, "Error al leer");
			return -1;
		}

		// Si el jugador ya estaba en el top, pero su score es menor al que ya estaba, cierra el archivo y devuelve 0
		// Caso contrario (el nuevo score es mayor) cambia el anterior por el nuevo
		if (strcmp(scores[j].name, player_name) == 0)
		{
			if (scores[j].score >= score)
			{
				fclose(scoreboard);
				return 0;
			}
			else
			{
				scores[j].score = score;
			}
		}

		// Si el score es menor al del top 10, cierra el archivo y devuelve 0
		// Caso contrario, reemplaza el nuevo score por el puesto nro 10
		if (j == 9)
		{
			if (scores[j].score >= score)
			{
				fclose(scoreboard);
				return 0;
			}
			else
			{
				strcpy(scores[j].name, player_name);
				scores[j].score = score;
			}
		}
	}

	// Como el nuevo score es mayor al del decimo puesto, ordena la matriz de mayor a menor score
	qsort(scores, 10, sizeof(player_t), player_comp);

	if (freopen("scoreboard.txt", "w", scoreboard) == NULL)
	{
		fprintf(stderr, "Error al reabrir el archivo de scoreboards");
	}

	// Escribe el score actualizado en el archivo
	int i;
	for (i = 0; i < 10; i++)
	{
		fprintf(scoreboard, "%s %d\n", scores[i].name, scores[i].score);
	}

	fflush(scoreboard);
	fclose(scoreboard);
	return 1;
}

/* FUNCIÓN PLAYER_COMP
 * BRIEF: Función que se encarga de comparar el score de dos jugadores para saber cual es más alto, para que se ordene de mayor a menor
 * a: (puntero a void constante) Es el primer jugador (el de la izquierda)
 * b: (puntero a void constante) Es el segundo jugador (el de la derecha)
 * return: (int) Devuelve el valor de verdad para cambiar o no el orden de ambos jugadores
 */
static int player_comp(const void *a, const void *b)
{

	return ((*(player_t *)b).score - (*(player_t *)a).score);
}