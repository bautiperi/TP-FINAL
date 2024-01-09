#include <stdio.h>
#include "map.h"

//DEF DE FUNCIONES PRIVADAS
static void barrier_diff (const int diff, int mapa[][COL]);
static void barrier_gen (const int x, const int y, const int width, const int heigth, int mapa[][COL]);


//La función se encarga de generar la matriz donde se encuentra el mapa, llama a funciones para que la misma sea poblada y devuelve un puntero a una matriz
//dif es una variable que contiene el nivel de dificultad seleccionado
void map_def(const int diff, int mapa [][COL]) {

	int x, y;

	//Loop que puebla de "espacio" la matriz
	for(x = 0; x < FIL; x++){
		for( y = 0; y < COL; y++){

			mapa[x][y] = SPACE;
		}
	}

	//Llama a la función encargada de crear los obstáculos
	barrier_diff(diff, mapa);

	//Llama a la función encargada de crear los enemigos y spawnear al jugador

}

/* FUNCIÓN BARRIER_DIFF
 * BRIEF: Se encarga de determinar la cantidad y tamaño de las barreras a poner
 * diff: (const int) Es la dificultad que seleccionó el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
static void barrier_diff (const int diff, int mapa[][COL]){

	//Easy mode: Establece 4 barreras de 2x2 separadas por espacios de dos
	if (diff  == EASY){
		int i;

		//Loop donde se llama a la función barrier_gen para crear las barreras/escudos
		for(i = 1; i < FIL; i += 4){
			barrier_gen(i, 10, 2, 2, mapa);
		}
	}

	//Agregar casos para modo normal y modo difícil
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
static void barrier_gen (const int x, const int y, const int width, const int heigth, int mapa[][COL]){

	int i, j;

	//Loop generador de las barreras
	for(j = 0; j < heigth; j++){

		for(i = 0; i < width; i++){
			mapa[y + j][x + i] = BARRIER; //Pone en la celda el valor -2 (indicador de barrera)
		}
	}
}
