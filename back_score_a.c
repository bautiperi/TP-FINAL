#include "back_score_a.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char name[50] = "";

static int player_comp (const void * a, const void * b);

void score_updater (int mapa[][COL], int identifier)
{

	//Dependiendo del enemigo al que se le pegó, se agregarán una determinada cantidad de puntos al score
	switch (identifier) {
	case 2:
		SCORE += 10;
		break;
	case 3:
		SCORE += 20;
		break;
	case 4:
		SCORE += 30;
		break;
	case 5:
		SCORE += 50;
		break;
	}

}

int score_saver (int score)
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

	return 0;
}

static int player_comp (const void * a, const void * b)
{

	return ((*(player_t *) b).score - (*(player_t *) a).score);

}

int life_updater (int mapa[][COL])
{
	LIFES--;
	if(LIFES == 0){
		return 1;
	}
	else{
		SPAWN_POINT = JUGADOR;
		return 0;
	}

}

