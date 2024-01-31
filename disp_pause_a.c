// --------------------------------------------------------------------------------------------- //
//HEADER
#include "disp_pause_a.h"
#include "_defines_display.h"

//LIBRERIAS
#include <stdio.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//PROTOTIPOS DE FUNCIONES PRIVADAS
/*FUNCIÓN DISPLAY_P_MENU
 * BRIEF: Se encarga de mostrar en pantalla el menú de pausa, con el botón seleccionado
 * boton: (unsigned int) Es el botón a seleccionar
 * return: (void)*/
static void display_p_menu(unsigned int boton, ALLEGRO_FONT *font_title, ALLEGRO_FONT *font);
// --------------------------------------------------------------------------------------------- //

int display_pause_menu (void){
	int sel = 0, ret = 1;

	//TAMAÑO DE LAS FONTS

	//CARGA LAS FONTS PARA EL MENU
	ALLEGRO_FONT *font_title = al_load_ttf_font("resources/Barbie-font.ttf", TITLE_SIZE, 0);
	ALLEGRO_FONT *font = al_load_ttf_font("resources/Barbie-font.ttf", OPTIONS_SIZE, 0);

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	do{
		display_p_menu(sel, font_title, font);

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
static void display_p_menu (unsigned int boton, ALLEGRO_FONT *font_title, ALLEGRO_FONT *font) {

	al_clear_to_color(al_map_rgb(54,1,63));

	al_draw_text(font_title, al_map_rgb(TITLE_COLOR), DISPLAY_CENTRE, 125, ALLEGRO_ALIGN_CENTER, "Pause Menu");

	switch(boton){
	case 0:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE -80, ALLEGRO_ALIGN_CENTER, "Resume game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE, ALLEGRO_ALIGN_CENTER, "Back to main menu");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE +80, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 1:
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE -80, ALLEGRO_ALIGN_CENTER, "> > Resume game < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE, ALLEGRO_ALIGN_CENTER, "Back to main menu");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE +80, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 2:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE -80, ALLEGRO_ALIGN_CENTER, "Resume game");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE, ALLEGRO_ALIGN_CENTER, "> > Back to main menu < <");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE +80, ALLEGRO_ALIGN_CENTER, "Quit game");
		break;
	case 3:
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE -80, ALLEGRO_ALIGN_CENTER, "Resume game");
		al_draw_text(font, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE, ALLEGRO_ALIGN_CENTER, "Back to main menu");
		al_draw_text(font, al_map_rgb(BUTTON_SEL_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE +80, ALLEGRO_ALIGN_CENTER, "> > Quit game < <");
		break;
	}

	al_flip_display();

	al_rest(0.01);

}
