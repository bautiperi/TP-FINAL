//Acá van todas las funciones relacionadas a las cosas de enemigos
#include "ships.h"

#include <unistd.h>

//Están harcodeadeas para probar el display de Allegro
int ships_create (int mapa[][COL], int diff){

	int x, y;
	for(y = 5; y < 15; y += 2){
		for(x = 4; x < 28; x += 3){
			mapa[y][x] = 2;
		}
	}

	return 0;
}

void ships_update (int mapa[][COL]){
	while(1){
	int x, y;
	int wall = 1;

	//Volver a hacer
	for(y = COL; (y > 0) && wall; y--){
		for(x = FIL; x > 0; x--){
			if(mapa[y][x] == 2){
				if((x) == (COL - 2)){
					wall = 0;
				}
				else{
					mapa[y][x+1] = 2;
					mapa[y][x--] = 0;
				}
			}
		}
		usleep(100000);
	}

	}
}
