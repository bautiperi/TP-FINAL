#include <stdio.h>

//TAMAÑO DE LA MATRIZ
#define COL 16
#define FIL 16

//DIFICULTAD
#define EASY 1


//La función se encarga de generar la matriz donde se encuentra el mapa, llama a funciones para que la misma sea poblada y devuelve un puntero a una matriz
//dif es una variable que contiene el nivel de dificultad seleccionado
int ** mapdef(const int diff){
	int mapa[][];

	int x, y;

	//Loop que puebla de "espacio" la matriz
	for(x = 0, x < FIL, x++){
		for( y = 0, y < COL, y++){

			mapa[x][y] = 0;
		}
	}

	//Llama a la función encargada de crear los obstáculos
	barrier_diff(diff, mapa[][]);

	//Llama a la función encargada de crear los enemigos y spawnear al jugador

}

void barrier_diff (const int diff, int mapa[][]){

	if (diff  == EASY){
		//Establece la primer barrera de tamaño 4x2
		barrier_gen( 1, 4, mapa);

		//Segunda barrera 3x2
		barrier_gen( 7, 3, mapa);

		//Tercer barrera 4x2
		barrier_gen( 12, 4, mapa);
	}
}

void barrier_gen (int x, int wid, int mapa[][]){

	int add;

	for(add = 0, add <= wid, add++){

		mapa[x + add][13] = -1;
		mapa[x + add][14] = -1;
	}
}
