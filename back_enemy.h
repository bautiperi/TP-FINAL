#ifndef BACK_ENEMY_H_
#define BACK_ENEMY_H_

// INCLUDE HEADER FILES
#include "_defines.h"

//PROTOTIPOS DE FUNCIONES

/* FUNCIÓN ALIEN_MOVEMENT (Diseñada para threads)
 * BRIEF: mueve horizontalmente a los aliens
 * arg: (*void) es la matriz donde se desarrolla el juego
 * Return: (void)
 */
void *alien_movement(void *arg);

/* FUNCIÓN FINAL_BOSS_CREATION (Diseñada para threads)
 * BRIEF: crea al final boss y llama a la funcion de su movimiento
 * arg: (*void) es la matriz donde se desarrolla el juego
 * Return: (void)
 */
void *final_boss_creation(void *arg);

/* FUNCIÓN ENEMY_FIRE (Diseñada para threads)
 * BRIEF: Crea de forma aleatoria los disparos de los enemigos
 * arg: (*void) es la matriz donde se desarrolla el juego
 * Return: (puntero void)
 */
void *enemy_fire(void *arg);

/* FUNCIÓN ENEMY_LIFE
 * BRIEF: Es llamada cuando un disparo del jugador "le pega" a un enemigo, la función decide si sigue o no con vida
 * x: (int) Coordenada x donde está el enemigo
 * y: (int) Coordenada y donde está el enemigo
 * mapa: (int) es la matriz donde se desarrolla el juego
 * Return: (puntero void)
 */
void enemy_life(int x, int y, int mapa[][COL]);

#endif /* BACK_ENEMY_H_ */