//LIBRERIAS
#include "disp_game_a.h"

#include <stdio.h>
#include <stdint.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//ARCHIVO HEADER

//DEFINICIÓN DE FUNCIONES PRIVADAS
static int display_barr (const int mapa[][COL]);
static int display_stats (int score, int lives);
static int display_player (const int mapa[][COL]);

//TAMAÑOS PARA ALLEGRO
#define SCALER 45


int display_init (void) {
	ALLEGRO_DISPLAY * display = NULL;

	//Inicializa Allegro
	if ( !al_init()) {
		fprintf(stderr, "No se pudo inicializar allegro \n");
		return -1;
	}

	//Inicializa el manejo de imágenes
	if (!al_init_image_addon()) {
	        fprintf(stderr, "No se pudo inicializar el manejo de imagenes\n");
	        return -1;
	}


	//Inicializa el uso de fonts
	if (!al_init_font_addon() || !al_init_ttf_addon()) {
		fprintf(stderr, "No se pudo inicializar el manejo de fuentes y texto\n");
		return -1;
	}

	//Inicializa el display
	display = al_create_display(720, 720);
	if (!display) {
		fprintf(stderr, "No se pudo crear el display \n");
		return -1;
	}

	return 0;
}

int display_game (const int mapa[][COL], int score, int lives){
	int i = 0; //Si ocurre un error, la variable cambiará su valor, haciendo que se detenga la ejecución del programa

	//Backbuffer se settea en negro
	al_clear_to_color(al_map_rgb(15,20,42));

	i += display_barr(mapa);


	i += display_stats (score, lives);

	i += display_player(mapa);

	if(i == 0){
		al_flip_display();
	}

	al_rest(10.0);

	return i;
}

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

static int display_stats (int score, int lives) {
	int size = 30;

	//Muestra es Score en pantalla
	ALLEGRO_FONT * font = NULL;

	font = al_load_ttf_font("resources/Zepto-Regular.ttf", size, 0);

	al_draw_textf(font, al_map_rgb(255, 255, 255), 25, 680, 0, "SCORE: %d", score);

	al_draw_text(font, al_map_rgb(255, 255, 255), 510, 680, 0, "LIVES:");

	//Muestra las vidas que tiene el jugador

	//Crea la imágen para el corazón vivo
	ALLEGRO_BITMAP * heart_ok = NULL;

	heart_ok = al_load_bitmap("resources/heart_yes.png");

	//Loop que pone en el buffer la cantidad de vidas que tiene el jugador
	int i, x=595;
	for(i = 1; i <= lives; i++, x += 35){
		al_draw_scaled_bitmap(heart_ok, 0, 0, 920, 920, x, 685, 30, 30, 0);
	}

	if(!heart_ok || !font){
		return -1;
	}
	else{
		return 0;
	}
}
//falta terminarrrr
static int display_player (const int mapa[][COL]){
	//Crea la imágen para el jugador
	ALLEGRO_BITMAP * player = NULL;

	player = al_load_bitmap("resources/player.png");

	if(!player){
		fprintf(stderr, "Actualizando al jugador ocurrió un problema \n");
		return -1;
	}

	//Loop que recorre la fila donde está el jugador
	int x, m;
	for( x = 0; (x < COL) && (m == 0); x++){
			//Cuando en la coordenada x, esté el jugador, cortará el loop
			m = (mapa[14][x] == 1);
	}

	al_draw_scaled_bitmap(player, 0, 0, a, b, x, 685, 45, 45, 0);

	return 0;
}
