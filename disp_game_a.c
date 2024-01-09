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
static int display_barr (const int mapa[][COL]);
static int display_stats (int score, int lives);
static int display_player (const int mapa[][COL]);
static int display_aliens (const int mapa[][COL]);
static int display_bullet (const int mapa[][COL]);

#define SCALER 45

int display_game (const int mapa[][COL], int score, int lives){
	int i = 0; //Si ocurre un error, la variable cambiará su valor, haciendo que se detenga la ejecución del programa

	//Backbuffer se settea en negro
	al_clear_to_color(al_map_rgb(15,20,42));

	i += display_barr(mapa);

	display_impact(5,11);

	i += display_stats (score, lives);

	i += display_player(mapa);

	i += display_aliens(mapa);

	i += display_bullet(mapa);

	if(i == 0){
		al_flip_display();
	}

	al_rest(10.0);

	return i;
}

/* FUNCIÓN DISPLAY_BARR
 * BRIEF: Se encarga de mostrar en pantalla las barreras/escudos
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) En caso de haber un error devuelve -1, 0 en caso de no haber ningún problema
 *  */
static int display_barr (const int mapa[][COL]) {

	ALLEGRO_BITMAP *barrier_state_2 = NULL, *barrier_state_1 = NULL;

    //Carga ambos estados de la barrera
    barrier_state_2 = al_load_bitmap("resources/barrier_state_2.png");
    barrier_state_1 = al_load_bitmap("resources/barrier_state_1.png");

    if( !barrier_state_2 || !barrier_state_1){
    	fprintf(stderr, "Al momento de crear las barreras hubo un error 2 \n");
    	return -1;
    }

    int x, y;
    //ESTA HARCODEADO, MODIFICAR PARA QUE ACEPTE OTROS NIVELES Y TAMAÑOS DE MATRICES
    for (y = 10; y < 12; y++){

    	for ( x = 0; x < 16; x++){
    		if(mapa[y][x] == BARRIER){
    			al_draw_scaled_bitmap(barrier_state_2, 0, 0, 64, 64, x* SCALER, y* SCALER , SCALER, SCALER, 0);
    		}
    		else if (mapa[y][x] == BRO_BARRIER){
    			al_draw_scaled_bitmap(barrier_state_1, 0, 0, 64, 64, x * SCALER, y * SCALER , SCALER, SCALER, 0);
    		}
    	}

    }

    return 0;
}

/* FUNCIÓN DISPLAY_STATS
 * BRIEF: Se encarga de mostrar en pantalla el score, vidas actuales y una leyenda que indica como entrar al menu de pausa
 * score: (int) Recibe el score actual del jugador
 * lives: (int) Recibe la cantidad de vidas que tiene el jugador
 * return: (int) En caso de haber un error devuelve -1, 0 en caso de no haber ningún problema
 *  */
static int display_stats (int score, int lives) {
	int size = 30;

	//Muestra es Score en pantalla
	ALLEGRO_FONT * font = NULL;

	font = al_load_ttf_font("resources/Zepto-Regular.ttf", size, 0);

	//Escribe en pantalla el score que tiene el jugador
	al_draw_textf(font, al_map_rgb(255, 255, 255), 25, 5, 0, "SCORE: %d", score);

	//Escribe en pantalla lives
	al_draw_text(font, al_map_rgb(255, 255, 255), 510, 5, 0, "LIVES:");

	//Muestra las vidas que tiene el jugador
	//Crea la imágen para el corazón vivo
	ALLEGRO_BITMAP * heart_ok = NULL;

	heart_ok = al_load_bitmap("resources/heart_yes.png");

	//Loop que pone en el buffer la cantidad de vidas que tiene el jugador
	int i, x=595;
	for(i = 1; i <= lives; i++, x += 35){
		al_draw_scaled_bitmap(heart_ok, 0, 0, 920, 920, x, 10, 30, 30, 0);
	}

	//Muestra en pantalla "Press ESC to pause the game"
	al_draw_text(font, al_map_rgb(255, 255, 255), 170, 680, 0, "Press ESC to pause the game.");

	if(!heart_ok || !font){
		return -1;
	}
	else{
		return 0;
	}
}

/* FUNCIÓN DISPLAY_PLAYER
 * BRIEF: Se encarga de mostrar en pantalla al jugador
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) En caso de haber un error devuelve -1, 0 en caso de no haber ningún problema
 *  */
static int display_player (const int mapa[][COL]){
	//Crea la imágen para el jugador
/*
	ALLEGRO_BITMAP * player = NULL;

	player = al_load_bitmap("resources/player.png");

	if(!player){
		fprintf(stderr, "Actualizando al jugador ocurrió un problema \n");
		return -1;
	}
*/
	//Loop que recorre la fila donde está el jugador
	int x, m = 0;

	for( x = 0; (x < COL) && (m == 0); x++){
		//Cuando en la coordenada x esté el jugador, cortará el loop
		m = (mapa[14][x] == 1);
	}

	//Temporal, al usar una foto queda mejor centrado
	al_draw_filled_rounded_rectangle((x -1) *SCALER, 600, (x+1) *SCALER, 600 + SCALER, 4, 4, al_map_rgb(173,216,230));

	return 0;
}

/* FUNCIÓN DISPLAY_ALIENS
 * BRIEF: Se encarga de mostrar en pantalla los enemigos (aliens y boss)
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) En caso de haber un error devuelve -1, 0 en caso de no haber ningún problema
 *  */
static int display_aliens (const int mapa[][COL]){
	//Crea la imágen para los aliens
	ALLEGRO_BITMAP * alien = NULL;

	alien = al_load_bitmap("resources/aliens.png");

	//Crea la imagen para el boss
	ALLEGRO_BITMAP * boss = NULL;
	//Crea un nro aleatorio para definir que imagen usar:
	srand(time(NULL));
	int rand_num = (rand()%100 + 1);

	if(rand_num >= 50){
		boss = al_load_bitmap("resources/boss1.png");
	}
	else {
		boss = al_load_bitmap("resources/boss2.png");
	}

	//Verificador de errores de allegro
	if(!alien /*|| !boss*/){
			fprintf(stderr, "Actualizando a los enemigos ocurrió un problema \n");
			return -1;
		}

	//Loop que encuentra los aliens y los muestra en pantalla
	int x, y;
	for (y = 1; y < FIL; y++){
		for(x = 0; x < COL; x++){
			if (mapa[y][x] == 2){
				al_draw_scaled_bitmap(alien, 0, 0, 360, 360, x* SCALER, y* SCALER , SCALER, SCALER, 0);
			}
			else if (mapa[y][x] == 3){
				al_draw_scaled_bitmap(boss, 0, 0, 360, 360, x * SCALER, y * SCALER, SCALER, SCALER, 0);
			}
		}
	}

	return 0;
}

/* FUNCIÓN DISPLAY_BULLET
 * BRIEF: Se encarga de mostrar en pantalla las balas de enemigos y jugador (celestes jugador, naranja enemigo)
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (int) En caso de haber un error devuelve -1, 0 en caso de no haber ningún problema
 *  */
static int display_bullet(const int mapa[][COL]){
	//Loop que encuentra los aliens y los muestra en pantalla
	int x, y;
	for (y = 1; y < FIL; y++){
		for(x = 0; x < COL; x++){
			if (mapa[y][x] == 5){
				al_draw_filled_rounded_rectangle(x*SCALER-5, y*SCALER-5, x*SCALER+5, y*SCALER+5, 4, 4, al_map_rgb(173,216,230));
			}
			else if (mapa[y][x] == 6){
				al_draw_filled_rounded_rectangle(x*SCALER-5, y*SCALER-5, x*SCALER+5, y*SCALER+5, 4, 4, al_map_rgb(252,75,8));
			}
		}
	}
	return 0;
}

void display_impact(int x, int y){
	ALLEGRO_BITMAP * impact = NULL;
	impact = al_load_bitmap("resources/impact.png");
	al_draw_scaled_bitmap(impact, 0, 0, 360, 360, x* SCALER, y* SCALER , SCALER, SCALER, 0);
}
