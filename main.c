#include <stdio.h>
#include <pthread.h>

#include "disp_game_a.h"
#include "map.h"
#include "disp_start_menu_a.h"
#include "disp_pause_a.h"
#include "ships.h"
#include "disp_scoreboard_a.h"

int main(void){

	int mapa[FIL][COL];

	//Llama a la función mapdef para inicializar el mapa
	map_def(EASY, mapa);

	ships_create(mapa, EASY);

	mapa[0][31] = 3;
	mapa[0][COL-2] = 9999999;
	mapa[28][16] = 1;
	mapa[27][16] = 5;


	display_init();


	//CREACION DE THREAD
	pthread_t enemigos;

	pthread_create(&enemigos, NULL, ships_update, mapa);

	display_game(mapa);

	return 0;

}
