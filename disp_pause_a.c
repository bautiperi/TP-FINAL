//Acá van todas las funciones relacionadas con el menú de pausa del juego
#include "disp_pause_a.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int display_pause_menu(unsigned int boton)
{
	int size_title = 75;
	int size_options = 40;

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

	al_rest(10.0);

	return 0;
}
