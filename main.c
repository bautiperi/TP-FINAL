#include <stdio.h>

#include "disp_game_a.h"
#include "map.h"
#include "disp_start_menu_a.h"
#include "disp_pause_a.h"

int main(void){

	/*
	int mapa[FIL][COL];

	//Llama a la función mapdef para inicializar el mapa
	map_def(EASY, mapa);


	if(display_init() == -1){
		return -1;
	}

	mapa[14][7] = 1;
	mapa[14][8] = 1;
	mapa[8][8] = 2;
	//mapa [10][12] = 5;
	//mapa [10][13] = 6;
	mapa[0][COL-5] = 1;

	display_game(mapa);


	//Para probar si el mapa se inicializa de forma correcta

	int x, y;

	for(x = 0; x < 16; x++){

		for (y = 0; y < 16; y++){

			printf("%d ", mapa[x][y]);
		}
		putchar('\n');
	}
*/

	if(display_init() == -1){
			return -1;
		}

	display_scoreboard();

	return 0;

}
