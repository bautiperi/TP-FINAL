/*
 * disp_scoreboard_a.c
 *
 *  Created on: Jan 10, 2024
 *      Author: bauti
 */
//HEADER
#include "disp_scoreboard_a.h"

//LIBRERIAS
#include <stdio.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//DEFINES
#define MAX_PLAYERS 10

static void display_board (player_t players[MAX_PLAYERS]);

int display_scoreboard (void){
	int exit = 1;
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	player_t players[MAX_PLAYERS];

	// Carga los jugadores en el array
    FILE *file = fopen("scoreboard.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening scoreboard file.\n");
        return 1;
    }

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (fscanf(file, "%s %d", players[i].name, &players[i].score) != 2) {
            i = MAX_PLAYERS;
        }
    }

    fclose(file);

	do{
		display_board(players);

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				exit = 0;
			}
		}
	}while(exit);

	al_destroy_event_queue(event_queue);

	return 0;
}

static void display_board (player_t players[MAX_PLAYERS]){
	int size_title = 75;
	int size_name = 30;

	//Pone al fonde de color azul marino
	al_clear_to_color(al_map_rgb(15,20,42));

	//Carga la fuente para el título
	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Zepto-Regular.ttf", size_title, 0);

	//Escribe en el buffer "SCOREBOARD"
	al_draw_text(font_title, al_map_rgb(255, 255, 255), 360, 65, ALLEGRO_ALIGN_CENTER, "SCOREBOARD");

	//Carga la fuente para los nombres
	ALLEGRO_FONT *font = NULL;
	font = al_load_ttf_font("resources/Zepto-Regular.ttf", size_name, 0);

	//Escribe el primer nombre y su puntaje en color dorado
	al_draw_textf(font, al_map_rgb(255, 215, 0), 170, 150, ALLEGRO_ALIGN_LEFT, "%s", players[0].name);
	al_draw_textf(font, al_map_rgb(255, 215, 0), 545, 150, ALLEGRO_ALIGN_RIGHT, "%d", players[0].score);

	//Loop que escribe el resto de los nombres y sus respectivos puntajes en blanco
	int i;
	for(i = 1; i < 10; i++){
		al_draw_textf(font, al_map_rgb(255, 255, 255), 170, 150 + i*35, ALLEGRO_ALIGN_LEFT, "%s", players[i].name);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 545, 150 + i*35, ALLEGRO_ALIGN_RIGHT, "%d", players[i].score);
	}

	//Leyenda que explica como volver a la pantalla anterior
	al_draw_text(font, al_map_rgb(255, 255, 255), 360, 670, ALLEGRO_ALIGN_CENTRE, "Press ESC to exit the scoreboard");

	//Muestra los cambios en pantalla
	al_flip_display();
}



