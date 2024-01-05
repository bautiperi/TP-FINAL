#include <stdio.h>
#include "map.h"

int main(void){

	int mapa[FIL][COL];

	//Llama a la función mapdef para inicializar el mapa
	mapdef(EASY, mapa);

	int x, y;

	for(x = 0; x < 16; x++){

		for (y = 0; y < 16; y++){

			printf("%d", mapa[x][y]);
		}
	}

	return 0;
}
