//HEADER
#include "disp_game_a.h"
#include "disp_pause_a.h"
#include "back_game_a.h"
#include "disp_scoreboard_a.h"

//LIBRERIAS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//DEFINICIÓN DE FUNCIONES PRIVADAS
static void display_barr (const int mapa[][COL], ALLEGRO_BITMAP * barrier);
static void display_stats (int score, int lives, ALLEGRO_FONT * font, ALLEGRO_BITMAP * heart);
static void display_player (const int mapa[][COL], ALLEGRO_BITMAP * player);
static int display_aliens (const int mapa[][COL], ALLEGRO_BITMAP * alien_1, ALLEGRO_BITMAP * alien_2, ALLEGRO_BITMAP * alien_3, ALLEGRO_BITMAP * boss);
static void display_bullet (const int mapa[][COL]);
static void display_impact(const int x, const int y, ALLEGRO_BITMAP * impact);

//DEFINICIONES PARA ALLEGRO
#define SCALER 25
#define FONT_SIZE 35

#define POS_X(x) ((x)* SCALER - SCALER/2)
#define POS_Y(y) ((y) * SCALER)


// RESERVAR LAS ÚLTIMAS 5 CELDAS DE LA PRIMER FILA PARA DATOS, EN SIGUIENTE ORDEN:
// HUBO IMPACTO (1 = Sí) | COORD X IMPACTO | COORD Y IMPACTO | SCORE | LIVES

int display_game (const int mapa[][COL]){

	int ken_flag = 0, ken_flag_continue = 0;

	// INICIALIZACIÓN DE ELEMENTOS PARA EL JUEGO:
	// PLAYER IMAGE
	ALLEGRO_BITMAP * player = al_load_bitmap("resources/player.png");
	// ALIENS & BOSS IMAGE
	ALLEGRO_BITMAP * alien_1 = al_load_bitmap("resources/aliens.png");
	ALLEGRO_BITMAP * alien_2 = al_load_bitmap("resources/aliens_2.png");
	ALLEGRO_BITMAP * alien_3 = al_load_bitmap("resources/aliens_2.png");
	ALLEGRO_BITMAP * boss = al_load_bitmap("resources/aliens_2.png");
	// BARRIERS IMAGE
	ALLEGRO_BITMAP * barrier = al_load_bitmap("resources/barrier.png");
	// LIVES IMAGE
	ALLEGRO_BITMAP * heart = al_load_bitmap("resources/heart_yes.png");
	// IMPACT IMAGE
	ALLEGRO_BITMAP * impact = al_load_bitmap("resources/impact.png");
	// FONT
	ALLEGRO_FONT * font = al_load_ttf_font("resources/Barbie-font.ttf", FONT_SIZE, 0);

	// CARGA LA CANCIÓN "Journey to the real world"
	ALLEGRO_SAMPLE *background = al_load_sample("resources/Journey To The Real World - Tame Impala.wav");
	ALLEGRO_SAMPLE_INSTANCE *backgroundInstance = al_create_sample_instance(background);
	al_set_sample_instance_playmode(backgroundInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(backgroundInstance, al_get_default_mixer());

	//CARGA LA CANCIÓN "I´m just ken"
	ALLEGRO_SAMPLE *ken_alien = al_load_sample("resources/Im Just Ken - Ryan Gosling.wav");
	ALLEGRO_SAMPLE_INSTANCE *kenInstance = al_create_sample_instance(ken_alien);
	al_attach_sample_instance_to_mixer(kenInstance, al_get_default_mixer());

	// Pone la canción
	al_play_sample_instance(backgroundInstance);
	al_set_sample_instance_gain(backgroundInstance, 0.4);

	// -------------- LLAMA PARA PEDIR EL NOMBRE DEL JUGADOR --------------
	//display_score_name(); Deshabilitado para probar el juego más facilmente
	// --------------------------------------------------------------------

	// TIMER
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *timer_ev_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);  // 60 FPS
	al_register_event_source(timer_ev_queue, al_get_timer_event_source(timer));

	// DETECTA CUANDO SE OPRIME COSAS EN EL TECLADO
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	ALLEGRO_EVENT event, ev;

	// INICIALIZA EL TIMER
	al_start_timer(timer);

	//Habilita los threads del juego, interacciones del usuario, movimiento de enemigos, etc
	flag_game_update = 1;

	do{

		al_get_next_event(event_queue, &event);
		al_get_next_event(timer_ev_queue, &ev);

		if(ken_flag == 1 && ken_flag_continue == 0){
			ken_flag_continue = 1;
			al_play_sample_instance(kenInstance);
			al_set_sample_instance_gain(kenInstance, 0.5);

		}
		else if (ken_flag == 0 && ken_flag_continue == 1){
			ken_flag_continue = 0;
			al_stop_sample_instance(kenInstance);
			al_set_sample_instance_gain(backgroundInstance, 0.4);
		}

		if( ev.type == ALLEGRO_EVENT_TIMER ){
			// Backbuffer se settea en el fondo deseado
			al_clear_to_color(al_map_rgb(54,1,63));
			// Muestra los escudos/barreras en pantalla
			display_barr(mapa, barrier);
			// Muestra las vidas, score y una leyenda en pantalla
			display_stats(SCORE, LIFES, font, heart);
			// Muestra el jugador en pantalla, se le debe pasar la coordenada x donde está el jugador
			display_player(mapa, player);
			// Muestra a los enemigos en pantalla
			ken_flag = display_aliens(mapa, alien_1, alien_2, alien_3, boss);
			// Muestra los disparos en pantalla
			display_bullet(mapa);

			// En caso de haber un impacto, lo muestra en pantalla
			if(IMPACT == 1){
				display_impact(IMPACT_X, IMPACT_Y, impact);
			}

			// Muestra los cambios en pantalla
			al_flip_display();

		}

		if(LIFES == 0){
			//Agregar animación de game over

			// Hace un fade-out de la música
			float volume;
			for (volume = 0.5; volume > 0.0; volume -= 0.01) {
				al_set_sample_instance_gain(backgroundInstance, volume);
				al_rest(0.01);
			}

			//Deja de correr la canción y elimina la instancia
			al_stop_sample_instance(backgroundInstance);
			al_destroy_sample_instance(kenInstance);
			al_destroy_sample(background);
			al_destroy_sample(ken_alien);

			return 0;
		}

		if(event.type == ALLEGRO_EVENT_KEY_DOWN){
			if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

				//DETIENE LOS THREADS
				flag_game_update = 0;

				float volume;
				//Hace un fade-in
				for (volume = 0.4; volume < 0.5; volume += 0.01) {
					al_set_sample_instance_gain(backgroundInstance, volume);
					al_rest(0.02);
				}

				int sel = display_pause_menu();

				if(sel == 3){
					return sel;
				}
				//Para volver al menú principal
				else if (sel == 2) {
					// Hace un fade-out de la música
					for (volume = 0.5; volume > 0.0; volume -= 0.01) {
						al_set_sample_instance_gain(backgroundInstance, volume);
						al_rest(0.01);
					}

					//Deja de correr la canción y elimina la instancia
					al_stop_sample_instance(backgroundInstance);
					al_destroy_sample_instance(kenInstance);
					al_destroy_sample(background);
					al_destroy_sample(ken_alien);

					return 0;
				}

			}
		}

	} while(1);

}

/* FUNCIÓN DISPLAY_BARR
 * BRIEF: Se encarga de mostrar en pantalla las barreras/escudos
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * barrier: (Puntero tipo ALLEGRO_BITMAP) Es la imagen utilizada para mostrar en pantalla las barreras
 * return: (void)
 *  */
static void display_barr (const int mapa[][COL], ALLEGRO_BITMAP *barrier) {

    int x, y;
    //ESTA HARCODEADO, MODIFICAR PARA QUE ACEPTE OTROS NIVELES
    for (y = 22; y < 27; y++){
    	for ( x = 0; x < 32; x++){
    		if(mapa[y][x] == BARRIER){
    			al_draw_scaled_bitmap(barrier, 0, 0, 64, 64, POS_X(x), POS_Y(y) , SCALER, SCALER, 0);
    		}
    	}

    }

}

/* FUNCIÓN DISPLAY_STATS
 * BRIEF: Se encarga de mostrar en pantalla el score, vidas actuales y una leyenda que indica como entrar al menu de pausa
 * score: (int) Recibe el score actual del jugador
 * lives: (int) Recibe la cantidad de vidas que tiene el jugador
 * font: (puntero tipo ALEGRO_FONT) Recibe el tipo de fuente a utilizar
 * heart: (puntero tipo ALLEGRO_BITMAP) Recibe la imágen para mostrar la cantidad de vidas que tiene el jugador
 * return: (void)
 *  */
static void display_stats (int score, int lives, ALLEGRO_FONT *font, ALLEGRO_BITMAP *heart) {

	//Escribe en pantalla el score que tiene el jugador
	al_draw_textf(font, al_map_rgb(255, 255, 255), 25, 5, 0, "Score: %d", score);

	//Escribe en pantalla lives
	al_draw_text(font, al_map_rgb(255, 255, 255), 615, 5, 0, "Lives:");

	//Loop que pone en el buffer la cantidad de vidas que tiene el jugador
	int i, x=680;
	for(i = 1; i <= lives; i++, x += 35){
		al_draw_scaled_bitmap(heart, 0, 0, 920, 920, x, 10, 30, 30, 0);
	}

	//Muestra en pantalla "Press ESC to pause the game"
	al_draw_text(font, al_map_rgb(255, 255, 255), 400, 750, ALLEGRO_ALIGN_CENTER, "Press ESC to pause the game");

}

/* FUNCIÓN DISPLAY_PLAYER
 * BRIEF: Se encarga de mostrar en pantalla al jugador
 * mapa: (matriz de ints) Matriz donde se desarrolla el juego
 * player: (puntero tipo ALLEGRO_BITMAP) Imagen que se muestra en pantalla para representar al jugador)
 * return: (void)
 *  */
static void display_player (const int mapa[][COL], ALLEGRO_BITMAP * player){

	int x;
	for(x = 0; x < COL; x++){
		if(mapa[28][x] == 1){
			al_draw_scaled_bitmap(player, 0, 0, 128, 64, (x-1) * SCALER, 28 * SCALER , SCALER * 2, SCALER, 0);
			return;
		}
	}

}

/* FUNCIÓN DISPLAY_ALIENS
 * BRIEF: Se encarga de mostrar en pantalla los enemigos (aliens y boss)
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) En caso de que el boss esté en pantalla, se devuelve 1 para que se escuche la canción
 *  */
static int display_aliens (const int mapa[][COL], ALLEGRO_BITMAP * alien_1, ALLEGRO_BITMAP * alien_2, ALLEGRO_BITMAP * alien_3, ALLEGRO_BITMAP * boss){

	//Loop que encuentra los aliens y los muestra en pantalla
	int x, y, ken_flag = 0;
	for (y = 1; y < (FIL - 4); y++){
		for(x = 0; x < COL; x++){
			if (mapa[y][x] == ALIEN_2){
				//Si el enemigo es un alien, muestra la imagen de un alien
				al_draw_scaled_bitmap(alien_1, 0, 0, 308, 308, POS_X(x), POS_Y(y) , 30, 30, 0);
			}
			else if (mapa[y][x] == ALIEN_3){
				//Si el enemigo es un alien, muestra la imagen de un alien
				al_draw_scaled_bitmap(alien_2, 0, 0, 308, 308, POS_X(x), POS_Y(y) , 30, 30, 0);
			}
			else if (mapa [y][x] == ALIEN_4){
				//Si el enemigo es un alien, muestra la imagen de un alien
				al_draw_scaled_bitmap(alien_3, 0, 0, 308, 308, POS_X(x), POS_Y(y) , 30, 30, 0);
			}
			else if (mapa [y][x] == BOSS){
				//Si el enemigo es un alien, muestra la imagen de un alien
				al_draw_scaled_bitmap(boss, 0, 0, 308, 308, POS_X(x), POS_Y(y) , 30, 30, 0);
				ken_flag++;
			}
		}
	}

	return ken_flag;

}

/* FUNCIÓN DISPLAY_BULLET
 * BRIEF: Se encarga de mostrar en pantalla las balas de enemigos y jugador (celestes jugador, naranja enemigo)
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void)
 *  */
static void display_bullet(const int mapa[][COL]){
	int x, y;

	//Loop que encuentra los disparos y diferencia los de enemigos y jugador
	for (y = 4; y < (FIL - 4); y++){
		for(x = 0; x < COL; x++){

			if (mapa[y][x] == FIRE_PL){
				//Si el disparo es de un jugador, lo muestra de color celeste
				al_draw_filled_rounded_rectangle(x*SCALER -5, POS_Y(y) -5, x*SCALER +5, POS_Y(y) +5, 4, 4, al_map_rgb(204,143,233));
			}
			else if (mapa[y][x] == FIRE_EN){
				//Si el disparo es de un enemigo, lo muestra de color naranja
				al_draw_filled_rounded_rectangle(x*SCALER -5, POS_Y(y) -5, x*SCALER +5, POS_Y(y) +5, 4, 4, al_map_rgb(130,39,215));
			}
		}
	}

}

/* FUNCIÓN DISPLAY_GAME
 * BRIEF: Se encarga de mostrar en pantalla cuando un disparo le pega a una barrera o a un alien
 * x: (int) Coordenada x donde ocurre el impacto
 * y: (int) Coordenada y donde ocurre el impacto
 * impact: (Puntero a ALLEGRO_BITMAP) Recibe la foto para el impacto a mostrar en pantalla
 * return: (int) En caso de haber un error devuelve -1
 *  */
static void display_impact(const int x, const int y, ALLEGRO_BITMAP * impact){

	//Muestra en pantalla el impacto
	al_draw_scaled_bitmap(impact, 0, 0, 360, 360, POS_X(x), POS_Y(y), SCALER, SCALER, 0);

}
