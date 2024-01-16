//HEADER
#include "disp_start_menu_a.h"

//LIBRERIAS
#include <stdio.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


//DEFINES
#define SIZE 800

//DEFINES MENU
#define TITLE_COLOR 255, 0, 127
#define BUTTON_COLOR 250, 218, 221
#define BUTTON_SEL_COLOR 233, 65, 150


static void display_s_menu (unsigned int boton);

int display_init (void){
	ALLEGRO_DISPLAY * display = NULL;

	//Inicializa Allegro
	if ( !al_init()) {
		fprintf(stderr, "No se pudo inicializar allegro \n");
		return -1;
	}

	//Inicializa el teclado
	if(!al_install_keyboard()){
		fprintf(stderr, "No se pudo instalar el driver para el teclado \n");
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

	//Inicializa el uso de audio
	if (!al_install_audio()) {
	    fprintf(stderr, "Failed to initialize audio.\n");
	    return -1;
	}

	if (!al_init_acodec_addon()) {
	    fprintf(stderr, "Failed to initialize audio codecs.\n");
	    return -1;
	}

	if (!al_reserve_samples(1)) {
	    fprintf(stderr, "Failed to reserve samples.\n");
	    return -1;
	}

	//Inicializa el display
	display = al_create_display(800, 800);
	if (!display) {
		fprintf(stderr, "No se pudo crear el display \n");
		return -1;
	}

	return 0;
}

int display_start_menu(void){
	int sel = 0, ret = 1;

		ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
		al_register_event_source(event_queue, al_get_keyboard_event_source());

		display_s_menu(0);

		do{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN || ev.keyboard.keycode == ALLEGRO_KEY_S){
					sel++;
				}
				else if(ev.keyboard.keycode == ALLEGRO_KEY_UP || ev.keyboard.keycode == ALLEGRO_KEY_W){
					sel--;
				}
			}

			if(sel > 3){
				sel = 1;
			}
			else if(sel <= 0){
				sel = 3;
			}

			display_s_menu(sel);


			if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
				ret = 0;
			}

		} while(ret);

		al_destroy_event_queue(event_queue);

		return sel;
}

/* FUNCIÓN DISPLAY_P_MENU
 * BRIEF: Es la función que muestra en pantalla el menú de inicio
 * boton: (u int) Recibe la selección del jugador para mostrar en pantalla
 * return: (void)
 * */
static void display_s_menu (unsigned int boton){
	int size_title = 150;
	int size_options = 75;

	al_clear_to_color(al_map_rgb(54,1,63));

	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Barbie-font.ttf", size_title, 0);
	al_draw_text(font_title, al_map_rgb(TITLE_COLOR), SIZE /2, 135, ALLEGRO_ALIGN_CENTER, "Space Invaders");

	ALLEGRO_FONT *font = NULL;
	font = al_load_ttf_font("resources/Barbie-font.ttf", size_options, 0);

	switch(boton){
	case 0:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 320, ALLEGRO_ALIGN_CENTER, "New game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 400, ALLEGRO_ALIGN_CENTER, "Highscore");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 480, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 1:
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), SIZE /2, 320, ALLEGRO_ALIGN_CENTER, "> >  New game  < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 400, ALLEGRO_ALIGN_CENTER, "Highscore");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 480, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 2:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 320, ALLEGRO_ALIGN_CENTER, "New game");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), SIZE /2, 400, ALLEGRO_ALIGN_CENTER, "> >  Highscore  < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 480, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 3:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 320, ALLEGRO_ALIGN_CENTER, "New game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 400, ALLEGRO_ALIGN_CENTER, "Highscore");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), SIZE /2, 480, ALLEGRO_ALIGN_CENTER, "> >  Quit game  < <");
		break;
	}

	al_flip_display();

	al_rest(0.01);

}
