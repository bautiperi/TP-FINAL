// ----------------------------------------------------------------------------- //
//FRONT
#include "disp_start_menu_a.h"
#include "disp_game_a.h"
#include "disp_scoreboard_a.h"
//BACK
#include "back_map.h"
#include "back_player.h"
#include "back_enemy.h"
//LIBRERIAS
#include <stdio.h>
#include <pthread.h>
#include <allegro5/allegro.h>

//Variable global que sirve como flag para detener la ejecución de los threads
// 0 -> Falso, están en pausa | 1 -> Ejecutan | 2 -> Exit threads
int flag_game_update = 0;
// ----------------------------------------------------------------------------- //

void * update_player_keyboard (void * arg);

int main(void){

	//INICIALIZA EL DISPLAY
	ALLEGRO_DISPLAY * display = display_init();

	if (display == NULL){
		fprintf(stderr, "Error al inicializar el display y sus librerias, descripción del error arriba");
		return -1;
	}

	int sel = 0;
	int dificultad = NORMAL;

	while( sel != QUIT ){
		sel = display_start_menu(&dificultad, display);

		//Inicializar juego
		if(sel == NEW_GAME){
			int mapa[FIL][COL];

			map_def(dificultad, mapa, 0);

			//Flag en 0 para que los threads no se inicialicen y estén en pausa
			flag_game_update = 0;

			pthread_t up_aliens, up_boss, up_player, enemy_shot;

			pthread_create(&up_boss, NULL, final_boss_creation, mapa);
			pthread_create(&up_aliens, NULL, alien_movement, mapa);
			pthread_create(&up_player, NULL, update_player_keyboard, mapa);
			pthread_create(&enemy_shot, NULL, enemy_fire, mapa);

			sel = display_game(mapa, display);
		}

		flag_game_update = 2;
	}

	return 0;

}

/* FUNCIÓN UPDATE_PLAYER_KEYBOARD (hecha para threads)
 * BRIEF: Es la función que se encarga de la interacción entre el usuario y dentro del juego
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void *)
 * */
void * update_player_keyboard (void * arg){

	int (*mapa)[COL] = (int (*)[COL])arg;

	// DETECTA CUANDO SE OPRIME COSAS EN EL TECLADO
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	ALLEGRO_EVENT event;

	// CREA UNA COLA DE EVENTOS PARA LIMITAR LA CANTIDAD DE DISPAROS
	ALLEGRO_EVENT_QUEUE *timer_queue = al_create_event_queue();
	ALLEGRO_TIMER *shot_timer = al_create_timer(1.5);
	al_register_event_source(timer_queue, al_get_timer_event_source(shot_timer));
	ALLEGRO_EVENT timer;

	al_start_timer(shot_timer);


	while (1){

		if(flag_game_update == 0){
			al_get_next_event(event_queue, &event);
			al_get_next_event(timer_queue, &timer);
		}
		else {
			al_get_next_event(event_queue, &event);
			al_get_next_event(timer_queue, &timer);

			if(event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_CHAR){
				if( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D){
					gamer_movement(mapa, 1);
					al_rest(0.045);
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A){
					gamer_movement(mapa, -1);
					al_rest(0.045);
				}
			}

			if(timer.type == ALLEGRO_EVENT_TIMER && timer.timer.source == shot_timer){
				if(event.type == ALLEGRO_EVENT_KEY_DOWN){
					if (event.keyboard.keycode == ALLEGRO_KEY_X){
						pthread_t gamer_shot;
						pthread_create(&gamer_shot, NULL, gamer_fire, mapa);
					}
				}
			}
		}

	}
}

/* NORMAL:	Juego tradicional | x1
 * HARD:	Como el tradicional, pero los enemigos tienen múltiples vidas (aleatorio), y los shields tienen la mitad del tamaño | x2
 * EXTREME:	No hay shield, enemigos con múltiples vidas y no hay vidas (jeje) | x3
 * */
