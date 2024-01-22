#include "back_aux_a.c"


void swap(int mapa[][COL], int x1, int y1, int x2, int y2)
{
    int aux = mapa[y1][x1];
    mapa[y1][x1] = mapa[y2][x2];
    mapa[y2][x2] = aux;
}
