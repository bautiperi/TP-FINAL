//Acá van todas las funciones relacionadas a las cosas de enemigos
#include "ships.h"

#include <unistd.h>

static void spawn_gen (int mapa[][COL], coord_t ini, coord_t desp, int type_of_enemy);

void ships_create (int diff, int mapa[][COL])
{

	//Dependiendo de la dificultad, se crearan de diferentes formas los aliens
	if (diff == EASY){
		int i, enemy = 4;
		{
			coord_t ini = {4, 5}, desp = {27, 5};
			//Se crea una fila del alien "4"
			spawn_gen(mapa, ini, desp, enemy--);
		}

		//Primeras dos filas alien "4", fila 3 y 4 alien "3" y fila 5 y 6 alien "2"
		for(i = 7; i < 13; i += 4){
			//ini es la coordenada superior izq y desp es la coordenada inferior derecha
			coord_t ini = {4, i}, desp = {27, i + 3};

			//Se crean dos filas del alien seleccionado
			spawn_gen(mapa, ini, desp, enemy--);
		}

	}

}

static void spawn_gen (int mapa[][COL], coord_t ini, coord_t desp, int type_of_enemy){

	int y, x;
	//Loop que pone los aliens separados por un espacio de una celda vertical y horizontal
	for(y = ini.y; y <= desp.y; y += 2){

		for(x = ini.x; x <= desp.x; x += 2){
			mapa[y][x] = type_of_enemy;
		}
	}

}
