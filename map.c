#include <stdio.h>
#include "map.h"

//DEF DE FUNCIONES PRIVADAS
static void barrier_diff (const int diff, int mapa[][COL]);
static void barrier_gen (int x, int wid, int mapa[][COL]);


//La función se encarga de generar la matriz donde se encuentra el mapa, llama a funciones para que la misma sea poblada y devuelve un puntero a una matriz
//dif es una variable que contiene el nivel de dificultad seleccionado
int (*mapdef(const int diff))[COL] {
	int mapa[FIL][COL];

	int x, y;

	//Loop que puebla de "espacio" la matriz
	for(x = 0; x < FIL; x++){
		for( y = 0; y < COL; y++){

			mapa[x][y] = 0;
		}
	}

	//Llama a la función encargada de crear los obstáculos
	barrier_diff(diff, mapa);

	//Llama a la función encargada de crear los enemigos y spawnear al jugador

	return mapa;
}

static void barrier_diff (const int diff, int mapa[][COL]){

	//Easy mode: Establece 4 barreras de 2x2 separadas por espacios de dos
	if (diff  == EASY){
		int i;

		for(i = 1; i < FIL; i += 3){
			barrier_gen(i, 2, mapa);
		}
	}

	//Agregar casos para modo normal y modo difícil
}

static void barrier_gen (int x, int wid, int mapa[][COL]){

	int add;

	for(add = 0; add <= wid; add++){

		mapa[x + add][10] = -2;
		mapa[x + add][11] = -2;
	}
}
