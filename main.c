#include <stdio.h>
#include "map.h"

int main(void){

	int (*ptr_mapa)[COL] = mapdef(EASY);

	int x, y;

	for(x = 0; x < 16; x++){

		for (y = 0; y < 16; y++){

			printf("%d", ptr_mapa[x][y]);
		}
	}

	return 0;
}
