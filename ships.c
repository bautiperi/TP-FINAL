//Acá van todas las funciones relacionadas a las cosas de enemigos
#include "ships.h"

#include <unistd.h>

int ships_create (int mapa[][COL], int diff){

	mapa[5][5] = 2;
	mapa[4][7] = 2;
	mapa[6][10] = 2;
}

void ships_update (int mapa[][COL]){
	while(1){
	int x, y;

	for(y = 1; y < FIL; y++){
		for(x = 0; x < COL; x++){
			if(mapa[y][x] == 2){
				if((x) < COL){
					mapa[y][x+1] = 2;
					mapa[y][x++] = 0;
				}
				else{
					mapa[y][0] = 2;
					mapa[y][x++] = 0;
				}
			}
		}
	}
	usleep(500000);

	}
}
