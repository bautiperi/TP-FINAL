//HEADER
#include "disp_pause_a.h"

//LIBRERIAS
#include <stdio.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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
	int size_title = 75;
	int size_options = 40;

	al_clear_to_color(al_map_rgb(15,20,42));

	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Zepto-Regular.ttf", size_title, 0);
	al_draw_text(font_title, al_map_rgb(255, 255, 255), 360, 100, ALLEGRO_ALIGN_CENTER, "PAUSE");

	ALLEGRO_FONT *font = NULL;
	font = al_load_ttf_font("resources/Zepto-Regular.ttf", size_options, 0);

	switch(boton){
	case 0:
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 200, ALLEGRO_ALIGN_CENTER, "RESUME GAME");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 250, ALLEGRO_ALIGN_CENTER, "BACK TO MENU");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 300, ALLEGRO_ALIGN_CENTER, "QUIT GAME");
		break;
	case 1:
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 200, ALLEGRO_ALIGN_CENTER, ">> RESUME GAME <<");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 250, ALLEGRO_ALIGN_CENTER, "BACK TO MENU");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 300, ALLEGRO_ALIGN_CENTER, "QUIT GAME");
		break;
	case 2:
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 200, ALLEGRO_ALIGN_CENTER, "RESUME GAME");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 250, ALLEGRO_ALIGN_CENTER, ">> BACK TO MENU <<");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 300, ALLEGRO_ALIGN_CENTER, "QUIT GAME");
		break;
	case 3:
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 200, ALLEGRO_ALIGN_CENTER, "RESUME GAME");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 250, ALLEGRO_ALIGN_CENTER, "BACK TO MENU");
		al_draw_text(font, al_map_rgb(255, 255, 255), 360, 300, ALLEGRO_ALIGN_CENTER, ">> QUIT GAME <<");
		break;
	}

	al_flip_display();

	al_rest(0.01);

}
