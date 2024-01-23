#ifndef SHIPS_H
#define SHIPS_H

// TAMAÑO DE LA MATRIZ
#define COL 16
#define FIL 16

// DIFICULTAD
#define RASP 0
#define EASY 1

// CONSTANTES
#define SPACE 0
#define BARRIER -1
#define ALIEN 4

/*FUNCION SHIPS_GEN
brief: se encarga de generar a los aliens
ubi: (int) matriz del mapa
return: void
*/
void ships_gen(int mapa[][COL], int diff);

#endif /* SHIPS_H */
