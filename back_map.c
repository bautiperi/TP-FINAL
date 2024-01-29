//------------------------------------------------------------------------------------------------------------------//
#include "back_map.h"
#include "back_enemy.h"

//PROTOTIPOS DE FUNCIONES PRIVADAS
/* FUNCIÓN BARRIER_DIFF
 * BRIEF: Se encarga de determinar la cantidad y tamaño de las barreras a poner
 * diff: (const int) Es la dificultad que seleccionó el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
static void barrier_diff (const int diff, int mapa[][COL]);
/* FUNCIÓN BARRIER_GEN
 * BRIEF: Se encarga de generar barreras del tamaño deseado en una determinada posición.
 * x: (int) Posición x de inicio (debe ser la sup. izq.)
 * y: (int) Posición y de inicio (debe ser la sup. izq)
 * width: (int) Ancho deseado
 * heigth: (int) Alto deseado
 * barr: (int) Indica que nro se le asigna a la barrera (cuantas veces se le tiene que disparar para romperla)
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
static void barrier_gen (const int x, const int y, const int width, const int heigth, int barr, int mapa[][COL]);
//------------------------------------------------------------------------------------------------------------------//

//Se usa y para las filas y x para las columnas, así coincide con los displays
void map_def(const int diff, int mapa [][COL]) {

	//Guarda la dificultad en el primer elemento de la matriz
	DIFICULTAD = diff;
	int x, y;

	//Loop que puebla de "espacio" la matriz
	for(y = 0; y < FIL; y++){
		for( x = 0; x < COL; x++){

			mapa[y][x] = SPACE;
		}
	}

	//Llama a la función encargada de crear los obstáculos
	barrier_diff(diff, mapa);

	//Llama a la función encargada de crear los enemigos
	ships_create(diff, mapa);

	//Ubica al jugador en el centro del mapa
	SPAWN_POINT = JUGADOR;

	LIFES = 3;
}

/* FUNCIÓN BARRIER_DIFF
 * BRIEF: Se encarga de determinar la cantidad y tamaño de las barreras a poner
 * diff: (const int) Es la dificultad que seleccionó el jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
static void barrier_diff (const int diff, int mapa[][COL]){

	//Easy mode: Establece 4 barreras de 2x2 separadas por espacios de dos
	if (diff  == RASP){
		int i;

		//Loop donde se llama a la función barrier_gen para crear las barreras/escudos
		for(i = 1; i < FIL; i += 4){
			barrier_gen(i, 10, 2, 2, -2, mapa);
		}
	}
	else if (diff == EASY){
		int i;

		//Loop donde se llama a la función barrier_gen para crear las barreras/escudos
		for(i = 2; i < FIL; i += 8){
			barrier_gen(i, 22, 4, 4, BARRIER, mapa);
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
 * barr: (int) Indica que nro se le asigna a la barrera (cuantas veces se le tiene que disparar para romperla)
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
static void barrier_gen (const int x, const int y, const int width, const int heigth, int barr, int mapa[][COL]){

	int i, j;

	//Loop generador de las barreras
	for(j = 0; j < heigth; j++){

		for(i = 0; i < width; i++){
			mapa[y + j][x + i] = barr; //Pone en la celda el valor deseado para indicar como barrera
		}
	}
}
