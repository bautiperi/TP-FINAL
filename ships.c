//Acá van todas las funciones relacionadas a las cosas de enemigos
#include "ships.h"

#include <unistd.h>

static void spawn_gen (int mapa[][COL], int ini_y, int desp_y, int type_of_enemy, int r_o_a);

//Están harcodeadeas para probar el display de Allegro
int ships_create (int diff, int mapa[][COL]){

	if (diff == EASY){
		int i, enemy = 4;

		for(i = 4; i < 20; i += 4){
			spawn_gen(mapa, i, i + 4, enemy--, 0);
		}

	}

	return 0;
}

static void spawn_gen (int mapa[][COL], int ini_y, int desp_y, int type_of_enemy, int r_o_a){

	//Indica si es rasp o allegro
	if(r_o_a == 0){
		int y, x;
		for(y = ini_y; y < desp_y; y += 2){

			for(x = 3; x < 29; x += 3){
				mapa[y][x] = type_of_enemy;
			}
		}
	}


}
