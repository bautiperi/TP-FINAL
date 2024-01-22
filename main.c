#include <stdio.h>
#include <pthread.h>
#include <allegro5/allegro.h>

#include "map.h"
#include "disp_start_menu_a.h"
#include "disp_game_a.h"
#include "back_game_a.h"

void update_player_keyboard (int mapa[][COL]);

int main(void){

	//INICIALIZA EL DISPLAY
	ALLEGRO_DISPLAY * display = display_init();

	if (display == NULL){
		fprintf(stderr, "Error al inicializar el display y sus librerias, descripción del error arriba");
		return -1;
	}

	int sel = 0;

	while( sel != 3 ){
		sel = display_start_menu();

		//Inicializar juego
		if(sel == 1){
			int mapa[FIL][COL];

			map_def(EASY, mapa);

			pthread_t * up_aliens, * up_boss, *up_player;

			pthread_create(&up_boss, NULL, final_boss_creation, mapa);
			pthread_create(&up_aliens, NULL, alien_movement, mapa);
			pthread_create(&up_player, NULL, update_player_keyboard, mapa);


			sel = display_game(mapa);
		}
	}

	return 0;

}

void update_player_keyboard (int mapa[][COL]){
	// DETECTA CUANDO SE OPRIME COSAS EN EL TECLADO
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	ALLEGRO_EVENT event;

	while (1){

		al_get_next_event(event_queue, &event);

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

		if(event.type == ALLEGRO_EVENT_KEY_DOWN){
			if (event.keyboard.keycode == ALLEGRO_KEY_X){
				pthread_t * gamer_shot;
				pthread_create(&gamer_shot, NULL, gamer_fire, mapa);
			}
		}
	}
}
