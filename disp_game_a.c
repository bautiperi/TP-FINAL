//HEADER
#include "disp_game_a.h"

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

//DEFINICIÓN DE FUNCIONES PRIVADAS
static void display_barr (const int mapa[][COL], ALLEGRO_BITMAP * barrier);
static void display_stats (int score, int lives, ALLEGRO_FONT * font, ALLEGRO_BITMAP * heart);
static void display_player (const int mapa[][COL], ALLEGRO_BITMAP * player);
static void display_aliens (const int mapa[][COL], ALLEGRO_BITMAP * alien);
static void display_bullet (const int mapa[][COL]);
static void display_impact (const int x, const int y);

#define SCALER 25
#define BARRIER -1
#define FONT_SIZE 30

// RESERVAR LAS ÚLTIMAS 5 CELDAS DE LA PRIMER FILA PARA DATOS, EN SIGUIENTE ORDEN:
// HUBO IMPACTO (1 = Sí) | COORD X IMPACTO | COORD Y IMPACTO | SCORE | LIVES

int display_game (int mapa[][COL]){

	// INICIALIZACIÓN DE ELEMENTOS PARA EL JUEGO:
	// PLAYER IMAGE
	ALLEGRO_BITMAP * player = al_load_bitmap("resources/player.png");
	// ALIENS IMAGE
	ALLEGRO_BITMAP * alien = al_load_bitmap("resources/aliens.png");
	// BARRIERS IMAGE
	ALLEGRO_BITMAP *barrier = al_load_bitmap("resources/barrier.png");
	// LIVES IMAGE
	ALLEGRO_BITMAP * heart = al_load_bitmap("resources/heart_yes.png");
	// FONT
	ALLEGRO_FONT * font = al_load_ttf_font("resources/Zepto-Regular.ttf", FONT_SIZE, 0);

	//TIMER
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *timer_ev_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);  // 60 FPS
	al_register_event_source(timer_ev_queue, al_get_timer_event_source(timer));

	//DETECTA CUANDO SE OPRIME COSAS EN EL TECLADO
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	ALLEGRO_EVENT event, ev;

	//INICIALIZA EL TIMER
	al_start_timer(timer);

	do{

		al_get_next_event(event_queue, &event);
		al_get_next_event(timer_ev_queue, &ev);

		if( ev.type == ALLEGRO_EVENT_TIMER ){
			//Backbuffer se settea en el fondo deseado
			al_clear_to_color(al_map_rgb(54,1,63));
			//Muestra los escudos/barreras en pantalla
			display_barr(mapa, barrier);
			//Muestra las vidas, score y una leyenda en pantalla
			display_stats(mapa[0][COL-2], mapa[0][COL-1], font, heart);
			//Muestra el jugador en pantalla, se le debe pasar la coordenada x donde está el jugador
			display_player(mapa, player);
			//Muestra a los enemigos en pantalla
			display_aliens(mapa, alien);
			//Muestra los disparos en pantalla
			display_bullet(mapa);

			//En caso de haber un impacto, lo muestra en pantalla
			if(mapa[0][COL-5] == 1){
				display_impact(mapa[0][COL-4],mapa[0][COL-3]);
			}

			//Muestra los cambios en pantalla
			al_flip_display();

		}

		if(event.type == ALLEGRO_EVENT_KEY_DOWN){
			if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				return 0;
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
    			al_draw_scaled_bitmap(barrier, 0, 0, 64, 64, x* SCALER, y* SCALER , SCALER, SCALER, 0);
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
	al_draw_textf(font, al_map_rgb(255, 255, 255), 25, 5, 0, "SCORE: %d", score);

	//Escribe en pantalla lives
	al_draw_text(font, al_map_rgb(255, 255, 255), 590, 5, 0, "LIVES:");

	//Loop que pone en el buffer la cantidad de vidas que tiene el jugador
	int i, x=680;
	for(i = 1; i <= lives; i++, x += 35){
		al_draw_scaled_bitmap(heart, 0, 0, 920, 920, x, 10, 30, 30, 0);
	}

	//Muestra en pantalla "Press ESC to pause the game"
	al_draw_text(font, al_map_rgb(255, 255, 255), 400, 750, ALLEGRO_ALIGN_CENTER, "Press ESC to pause the game.");

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
			al_draw_scaled_bitmap(player, 0, 0, 128, 64, (x-1)* SCALER, 28 * SCALER , SCALER * 2, SCALER, 0);
		}
	}

}

/* FUNCIÓN DISPLAY_ALIENS
 * BRIEF: Se encarga de mostrar en pantalla los enemigos (aliens y boss)
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) En caso de haber un error devuelve -1, 0 en caso de no haber ningún problema
 *  */
static void display_aliens (const int mapa[][COL], ALLEGRO_BITMAP * alien){
	//Crea la imagen para el boss
	ALLEGRO_BITMAP * boss = NULL;
	//Crea un nro aleatorio para definir que imagen usar:
	srand(time(NULL));
	int rand_num = (rand()%100 + 1);

	//Si el nro es mayor o igual a 50, muestra boss 1, caso contrario muestra boss 2
	if(rand_num >= 50){
		boss = al_load_bitmap("resources/boss1.png");
	}
	else {
		boss = al_load_bitmap("resources/boss2.png");
	}

	//Loop que encuentra los aliens y los muestra en pantalla
	int x, y;
	for (y = 1; y < (FIL - 4); y++){
		for(x = 0; x < COL; x++){
			if (mapa[y][x] == 2){
				//Si el enemigo es un alien, muestra la imagen de un alien
				al_draw_scaled_bitmap(alien, 0, 0, 308, 308, x * SCALER, y * SCALER , 30, 30, 0);
			}
			else if (mapa[y][x] == 3){
				//Muestra la imagen del boss
				al_draw_scaled_bitmap(boss, 0, 0, 360, 360, x * SCALER, y * SCALER, SCALER, SCALER, 0);
			}
		}
	}

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

			if (mapa[y][x] == 5){
				//Si el disparo es de un jugador, lo muestra de color celeste
				al_draw_filled_rounded_rectangle(x*SCALER-5, y*SCALER-5, x*SCALER+5, y*SCALER+5, 4, 4, al_map_rgb(204,143,233));
			}
			else if (mapa[y][x] == 6){
				//Si el disparo es de un enemigo, lo muestra de color naranja
				al_draw_filled_rounded_rectangle(x*SCALER-5, y*SCALER-5, x*SCALER+5, y*SCALER+5, 4, 4, al_map_rgb(130,39,215));
			}
		}
	}

}

/* FUNCIÓN DISPLAY_GAME
 * BRIEF: Se encarga de mostrar en pantalla cuando un disparo le pega a una barrera o a un alien
 * x: (int) Coordenada x donde ocurre el impacto
 * y: (int) Coordenada y donde ocurre el impacto
 * return: (int) En caso de haber un error devuelve -1
 *  */
static void display_impact(const int x, const int y){
	ALLEGRO_BITMAP * impact = al_load_bitmap("resources/impact.png");

	//Muestra en pantalla el impacto
	al_draw_scaled_bitmap(impact, 0, 0, 360, 360, x* SCALER, y* SCALER , SCALER, SCALER, 0);

	//Hace un efecto de sonido para acompañar el impacto (a hacer)
}
