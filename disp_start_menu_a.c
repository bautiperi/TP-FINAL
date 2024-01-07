#include "disp_start_menu_a.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define FPS 60.0

int display_init (void){
	ALLEGRO_DISPLAY * display = NULL;

	//Inicializa Allegro
	if ( !al_init()) {
		fprintf(stderr, "No se pudo inicializar allegro \n");
		return -1;
	}

	//Inicializa el timer
	ALLEGRO_TIMER *timer = NULL;
	timer = al_create_timer(1.0 / FPS); //crea el timer pero NO empieza a correr
	    if (!timer) {
	        fprintf(stderr, "No se pudo inicializar el timer\n");
	        return -1;
	    }

	//Inicializa el manejo de imágenes
	if (!al_init_image_addon()) {
	        fprintf(stderr, "No se pudo inicializar el manejo de imagenes\n");
	        return -1;
	}

	//Inicializa el uso de formas
		if (!al_init_primitives_addon()) {
			fprintf(stderr, "No se pudo inicializar el manejo de primitivas\n");
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

// Acá van todas las funciones del menú de inicio

int display_start_menu(unsigned int boton)
{
	int size_title = 75;
	int size_options = 40;

	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Zepto-Regular.ttf", size_title, 0);
	al_draw_text(font_title, al_map_rgb(255, 255, 255), 100, 100, 0, "SPACE INVADERS");

	ALLEGRO_FONT *font = NULL;
	font = al_load_ttf_font("resources/Zepto-Regular.ttf", size_options, 0);

	switch(boton){
	case 0:
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 200, ALLEGRO_ALIGN_CENTER, "NEW GAME");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 250, ALLEGRO_ALIGN_CENTER, "HIGHSCORE");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 300, ALLEGRO_ALIGN_CENTER, "QUIT GAME");
		break;
	case 1:
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 200, ALLEGRO_ALIGN_CENTER, ">> NEW GAME <<");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 250, ALLEGRO_ALIGN_CENTER, "HIGHSCORE");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 300, ALLEGRO_ALIGN_CENTER, "QUIT GAME");
		break;
	case 2:
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 200, ALLEGRO_ALIGN_CENTER, "NEW GAME");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 250, ALLEGRO_ALIGN_CENTER, ">> HIGHSCORE <<");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 300, ALLEGRO_ALIGN_CENTER, "QUIT GAME");
		break;
	case 3:
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 200, ALLEGRO_ALIGN_CENTER, "NEW GAME");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 250, ALLEGRO_ALIGN_CENTER, "HIGHSCORE");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 300, ALLEGRO_ALIGN_CENTER, ">> QUIT GAME <<");
		break;
	}

	al_flip_display();

	al_rest(10.0);

	return 0;
}
