//HEADER
#include "disp_pause_a.h"

//LIBRERIAS
#include <stdio.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//DEFINES
#define SIZE 800
#define TITLE_COLOR 255, 0, 127
#define BUTTON_COLOR 250, 218, 221
#define BUTTON_SEL_COLOR 233, 65, 150

//PROTOTIPOS
static void display_p_menu(unsigned int boton);

int display_pause_menu (void){
	int sel = 0, ret = 1;

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	display_p_menu(0);

	do{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN){
				sel++;
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_UP){
				sel--;
			}
		}

		if(sel > 3){
			sel = 1;
		}
		else if(sel <= 0){
			sel = 3;
		}

		display_p_menu(sel);


		if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
			ret = 0;
		}

	} while(ret);

	al_destroy_event_queue(event_queue);

	return sel;
}

/*FUNCIÓN DISPLAY_P_MENU
 * BRIEF: Se encarga de mostrar en pantalla el menú de pausa, con el botón seleccionado
 * boton: (unsigned int) Es el botón a seleccionar
 * return: (void)*/
static void display_p_menu (unsigned int boton) {
	int size_title = 150;
	int size_options = 75;

	al_clear_to_color(al_map_rgb(54,1,63));

	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Barbie-font.ttf", size_title, 0);
	al_draw_text(font_title, al_map_rgb(TITLE_COLOR), SIZE /2, 125, ALLEGRO_ALIGN_CENTER, "Pause Menu");

	ALLEGRO_FONT *font = NULL;
	font = al_load_ttf_font("resources/Barbie-font.ttf", size_options, 0);

	switch(boton){
	case 0:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 320, ALLEGRO_ALIGN_CENTER, "Resume game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 400, ALLEGRO_ALIGN_CENTER, "Back to main menu");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 480, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 1:
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), SIZE /2, 320, ALLEGRO_ALIGN_CENTER, "> > Resume game < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 400, ALLEGRO_ALIGN_CENTER, "Back to main menu");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 480, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 2:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 320, ALLEGRO_ALIGN_CENTER, "Resume game");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), SIZE /2, 400, ALLEGRO_ALIGN_CENTER, "> > Back to main menu < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 480, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 3:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 320, ALLEGRO_ALIGN_CENTER, "Resume game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), SIZE /2, 400, ALLEGRO_ALIGN_CENTER, "Back to main menu");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), SIZE /2, 480, ALLEGRO_ALIGN_CENTER, "> > Quit game < <");
		break;
	}

	al_flip_display();

	al_rest(0.01);

}
