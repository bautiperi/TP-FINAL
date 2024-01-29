#include "back_aux.h"

#include <unistd.h>

void swap(int mapa[][COL], int x1, int y1, int x2, int y2)
{
    int aux = mapa[y1][x1];
    mapa[y1][x1] = mapa[y2][x2];
    mapa[y2][x2] = aux;
}

int enemy_checker (int x, int y, const int mapa[][COL])
{
	return (mapa[y][x] == ALIEN_2 || mapa[y][x] == ALIEN_3 || mapa[y][x] == ALIEN_4);
}

void * impact_updater (void * arg){

	int (*mapa)[COL] = (int (*)[COL])arg;

	IMPACT = 1; //Indica que hubo un impacto

	usleep(450000);

	IMPACT = 0;

	return NULL;

}