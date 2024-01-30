//-----------------------------------------------------------------------------------------------------------------------------------------//
#include "back_score.h"

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//PROTOTIPOS FUNCIONES PRIVADAS
/* FUNCIÓN PLAYER_COMP
 * BRIEF: Función que se encarga de comparar el score de dos jugadores para saber cual es más alto, para que se ordene de mayor a menor
 * a: (puntero a void constante) Es el primer jugador (el de la izquierda)
 * b: (puntero a void constante) Es el segundo jugador (el de la derecha)
 * return: (int) Devuelve el valor de verdad para cambiar o no el orden de ambos jugadores
 */
static int player_comp (const void * a, const void * b);
//-----------------------------------------------------------------------------------------------------------------------------------------//

//String donde se almacena el nombre del jugador
char name[50] = "";

void score_updater (int mapa[][COL], int identifier)
{
	time_t t;
	srand((unsigned) time(&t));
	static int enemy_counter;
	//Dependiendo del enemigo al que se le pegó, se agregarán una determinada cantidad de puntos al score
	//También, dependiendo del modo de juego, se multiplicará más el score total
	if(identifier < 5){
		SCORE += (identifier *10) * DIFICULTAD;
		enemy_counter++;
	}
	else if (identifier == 5){
		//Agrega en el score un nro aleatorio entre 50 y 100
		SCORE += ((rand()%6 + 5) *10) * DIFICULTAD;
	}

}

int score_saver (const int score)
{
	FILE *scoreboard = fopen("scoreboard.txt", "a+");

	if( scoreboard == NULL){
		fprintf(stderr, "No se pudo abrir el archivo donde se encuentra el score del juego! \n");
		return -1;
	}

	//Crea una matriz de jugadores del scoreboard
	player_t scores[10];

	int i;
	for(i = 0; i < 10; i++){
		//Escribe los nombres y los scores de cada jugador en la matriz
		fread(&scores[i], sizeof(player_t), 1, scoreboard);

		//Si el nombre del jugador coincide con uno de la lista, verifica si es mayor o no el nuevo score
		if(strcmp(scores[i].name, name) == 0){

			//Como el score almacenado es mayor al nuevo, no lo almacena
			if(scores[i].score >= score){
				fclose(scoreboard);
				return 0;
			}
			else{
				//Guarda el nuevo score del jugador
				scores[i].score = score;
			}

		}

		//Si el último jugador de la tabla tiene un mayor puntaje que el score a guardar, no se guarda
		if( i == 9 && (scores[i].score >= score)){
			fclose(scoreboard);
			return 0;
		}
	}

	//Como el último puesto tiene un score menor al nuevo, lo reemplaza
	strcpy(scores[9].name, name);
	scores[9].score = score;

	//Ordena de mayor a menor el scoreboard
	qsort(scores, 10, sizeof(player_t), player_comp);

	//Loop que escribe en el archivo los jugadores con el scoreboard actualizado
	for(i = 0; i < 10; i ++){
		fwrite(&scores[i], sizeof(player_t), 1, scoreboard);
	}

	fclose(scoreboard);

	return 1;
}

/* FUNCIÓN PLAYER_COMP
 * BRIEF: Función que se encarga de comparar el score de dos jugadores para saber cual es más alto, para que se ordene de mayor a menor
 * a: (puntero a void constante) Es el primer jugador (el de la izquierda)
 * b: (puntero a void constante) Es el segundo jugador (el de la derecha)
 * return: (int) Devuelve el valor de verdad para cambiar o no el orden de ambos jugadores
 */
static int player_comp (const void * a, const void * b)
{

	return ((*(player_t *) b).score - (*(player_t *) a).score);

}

