// ------------------------------------------------------------------------------------------------- //
//HEADER
#include "disp_start_menu_a.h"
#include "disp_scoreboard_a.h"
#include "_defines_display.h"
#include "_defines.h"

//LIBRERIAS
#include <stdio.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//PROTOTIPOS FUNCIONES PRIVADAS
/* FUNCIÓN DISPLAY_P_MENU
 * BRIEF: Es la función que muestra en pantalla el menú de inicio
 * boton: (u int) Recibe la selección del jugador para mostrar en pantalla
 * return: (void)
 * */
static void display_s_menu (unsigned int boton, ALLEGRO_FONT * font_title, ALLEGRO_FONT * font);
// ------------------------------------------------------------------------------------------------- //

ALLEGRO_DISPLAY * display_init (void){
	ALLEGRO_DISPLAY * display = NULL;

	//Inicializa Allegro
	if ( !al_init()) {
		fprintf(stderr, "No se pudo inicializar allegro \n");
		return NULL;
	}

	//Inicializa el teclado
	if(!al_install_keyboard()){
		fprintf(stderr, "No se pudo instalar el driver para el teclado \n");
	}


	//Inicializa el manejo de imágenes
	if (!al_init_image_addon()) {
		fprintf(stderr, "No se pudo inicializar el manejo de imagenes\n");
	    return NULL;
	}

	//Inicializa el uso de formas
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "No se pudo inicializar el manejo de primitivas\n");
		return NULL;
	}

	//Inicializa el uso de fonts
	if (!al_init_font_addon() || !al_init_ttf_addon()) {
		fprintf(stderr, "No se pudo inicializar el manejo de fuentes y texto\n");
		return NULL;
	}

	//Inicializa el uso de audio
	if (!al_install_audio()) {
	    fprintf(stderr, "Failed to initialize audio.\n");
	    return NULL;
	}

	if (!al_init_acodec_addon()) {
	    fprintf(stderr, "Failed to initialize audio codecs.\n");
	    return NULL;
	}

	if (!al_reserve_samples(1)) {
	    fprintf(stderr, "Failed to reserve samples.\n");
	    return NULL;
	}

	//Inicializa el display
	display = al_create_display(DISPLAY_SIZE, DISPLAY_SIZE);
	if (!display) {
		fprintf(stderr, "No se pudo crear el display \n");
		return NULL;
	}

	return display;
}

//sel = 1 -> Iniciar juego nuevo | sel = 2 -> Scoreboard | sel = 3 -> exit game
int display_start_menu(int * dificultad, ALLEGRO_DISPLAY * display){
	int sel = 0, ret = 1;

	//Carga las fonts
	//Font para el título
	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Barbie-font.ttf", TITLE_SIZE, 0);
	// Font para los botones
	ALLEGRO_FONT *font = NULL;
	font = al_load_ttf_font("resources/Barbie-font.ttf", OPTIONS_SIZE, 0);

	// COLA DE EVENTOS
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //Teclado
	al_register_event_source(event_queue, al_get_display_event_source(display)); //Display

	// CARGA LA CANCIÓN "Dance the Night"
	ALLEGRO_SAMPLE *sample = al_load_sample("resources/Dance the night - Dua Lipa.wav");
	ALLEGRO_SAMPLE_INSTANCE *sampleInstance = al_create_sample_instance(sample);
	al_set_sample_instance_playmode(sampleInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());

	display_s_menu(sel, font_title, font);

	// Pone la canción
	al_play_sample_instance(sampleInstance);
	al_set_sample_instance_gain(sampleInstance, 0.5);

	//LOOP
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

		if(sel > QUIT){
			sel = NEW_GAME;
		}
		else if(sel <= 0){
			sel = QUIT;
		}

		display_s_menu(sel, font_title, font);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
			if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
				//Si se selecciona el scoreboard, se llama a la función encargada de ello
				if(sel == HIGHSCORE){
					// Hace un fade-out de la música
					float volume;
					for (volume = 0.5; volume > 0.2; volume -= 0.01) {
						al_set_sample_instance_gain(sampleInstance, volume);
						al_rest(0.02);
					}

					display_scoreboard();

					//Hace un fade-in
					for (volume = 0.2; volume < 0.5; volume += 0.01) {
						al_set_sample_instance_gain(sampleInstance, volume);
						al_rest(0.02);
					}
				}
				else if(sel != 0){
					ret = 0;
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			return QUIT;
		}

	} while(ret);

	//Destruye la cola de eventos
	al_destroy_event_queue(event_queue);

	// Hace un fade-out de la música
	float volume;
	for (volume = 0.5; volume > 0.0; volume -= 0.01) {
		al_set_sample_instance_gain(sampleInstance, volume);
	    al_rest(0.02);
	}

	//Deja de correr la canción y elimina la instancia
	al_stop_sample_instance(sampleInstance);
	al_destroy_sample_instance(sampleInstance);
	al_destroy_sample(sample);

	return sel;
}

/* FUNCIÓN DISPLAY_P_MENU
 * BRIEF: Es la función que muestra en pantalla el menú de inicio
 * boton: (u int) Recibe la selección del jugador para mostrar en pantalla
 * return: (void)
 * */
static void display_s_menu (unsigned int boton, ALLEGRO_FONT * font_title, ALLEGRO_FONT * font){

	al_clear_to_color(al_map_rgb(54,1,63));

	//TÍTULO
	al_draw_text(font_title, al_map_rgb(TITLE_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 300, ALLEGRO_ALIGN_CENTER, "Space Barbie");

	//BOTONES
	switch(boton){
	case 0:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 125, ALLEGRO_ALIGN_CENTER, "New game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 45, ALLEGRO_ALIGN_CENTER, "Highscore");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 45, ALLEGRO_ALIGN_CENTER, "Difficulty");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 125, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case NEW_GAME:
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 125, ALLEGRO_ALIGN_CENTER, "> >  New game  < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 45, ALLEGRO_ALIGN_CENTER, "Highscore");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 45, ALLEGRO_ALIGN_CENTER, "Difficulty");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 125, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case HIGHSCORE:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 125, ALLEGRO_ALIGN_CENTER, "New game");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 45, ALLEGRO_ALIGN_CENTER, "> >  Highscore  < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 45, ALLEGRO_ALIGN_CENTER, "Difficulty");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 125, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case DIFFICULTY:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 125, ALLEGRO_ALIGN_CENTER, "New game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 45, ALLEGRO_ALIGN_CENTER, "Highscore");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 45, ALLEGRO_ALIGN_CENTER, "> >  Difficulty  < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 125, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case QUIT:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 125, ALLEGRO_ALIGN_CENTER, "New game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 45, ALLEGRO_ALIGN_CENTER, "Highscore");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 45, ALLEGRO_ALIGN_CENTER, "Difficulty");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE + 125, ALLEGRO_ALIGN_CENTER, "> >  Quit game  < <");
		break;
	}

	al_flip_display();

	al_rest(0.01);

}
