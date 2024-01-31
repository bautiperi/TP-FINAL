// --------------------------------------------------------------------------------- //
//HEADER
#include "disp_scoreboard_a.h"
#include "back_score.h"
#include "_defines_display.h"

//LIBRERIAS
#include <stdio.h>

//LIBRERIAS ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//DEFINES
#define MAX_PLAYERS 10

//PROTOTIPOS FUNCIONES PRIVADAS
/* FUNCIÓN DISPLAY_BOARD
 * BRIEF: Se encarga de mostrar los jugadores que forman parte del scoreboard
 * return: (void)
 *  */
static void display_board (player_t players[MAX_PLAYERS]);
const void character_displayer_menu (int sel, ALLEGRO_BITMAP * char_1, ALLEGRO_BITMAP * char_2, ALLEGRO_BITMAP * char_3, ALLEGRO_BITMAP * char_4, ALLEGRO_BITMAP * char_5);
// --------------------------------------------------------------------------------- //

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

/* FUNCIÓN DISPLAY_BOARD
 * BRIEF: Se encarga de mostrar los jugadores que forman parte del scoreboard
 * return: (void)
 *  */
static void display_board (player_t players[MAX_PLAYERS]){
	int size_title = 125;
	int size_name = 30;

	//Pone al fonde de color
	al_clear_to_color(al_map_rgb(54,1,63));

	//Carga la fuente para el título
	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Barbie-font.ttf", size_title, 0);

	//Escribe en el buffer "SCOREBOARD"
	al_draw_text(font_title, al_map_rgb(TITLE_COLOR), DISPLAY_CENTRE, DISPLAY_CENTRE - 300, ALLEGRO_ALIGN_CENTER, "Highscore");

	//Carga la fuente para los nombres
	ALLEGRO_FONT *font = NULL;
	font = al_load_ttf_font("resources/Zepto-Regular.ttf", size_name, 0);

	//Escribe el primer nombre y su puntaje en color rosa neon
	al_draw_textf(font, al_map_rgb(255, 0, 127), DISPLAY_CENTRE - 190, 300, ALLEGRO_ALIGN_LEFT, "%s", players[0].name);
	al_draw_textf(font, al_map_rgb(255, 0, 127), DISPLAY_CENTRE + 185, 300, ALLEGRO_ALIGN_RIGHT, "%d", players[0].score);

	//Loop que escribe el resto de los nombres y sus respectivos puntajes en blanco
	int i;
	for(i = 1; i < 10; i++){
		al_draw_textf(font, al_map_rgb(250, 218, 221), DISPLAY_CENTRE - 190, 300 + i*35, ALLEGRO_ALIGN_LEFT, "%s", players[i].name);
		al_draw_textf(font, al_map_rgb(250, 218, 221), DISPLAY_CENTRE + 185, 300 + i*35, ALLEGRO_ALIGN_RIGHT, "%d", players[i].score);
	}

	//Leyenda que explica como volver a la pantalla anterior
	al_draw_text(font, al_map_rgb(250, 218, 221), DISPLAY_CENTRE, DISPLAY_SIZE - 50, ALLEGRO_ALIGN_CENTRE, "Press ESC to exit the scoreboard");

	//Muestra los cambios en pantalla
	al_flip_display();

}

int disp_name_and_char (void) {
	int exit = 1, pos = 0;

	int size_title = 55;
	int size_subtitle = 45;
	int size_name = 40;

	//Busco la variable de back_score_a para que se guarde el nombre del jugador
	extern char name[50];

	//Carga la fuente para el título
	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Barbie-font.ttf", size_title, 0);

	//Carga la fuente para el subtítulo
	ALLEGRO_FONT *font_subtitle = NULL;
	font_subtitle = al_load_ttf_font("resources/Barbie-font.ttf", size_subtitle, 0);

	//Carga la fuente para el nombre
	ALLEGRO_FONT *font_name = NULL;
	font_name = al_load_ttf_font("resources/Barbie-font.ttf", size_name, 0);

	//Carga las imágenes de todos los personajes
	ALLEGRO_BITMAP * char_1 = al_load_bitmap("resources/characters/char_sel/char_1.png");
	ALLEGRO_BITMAP * char_2 = al_load_bitmap("resources/characters/char_sel/char_2.png");
	ALLEGRO_BITMAP * char_3 = al_load_bitmap("resources/characters/char_sel/char_3.png");
	ALLEGRO_BITMAP * char_4 = al_load_bitmap("resources/characters/char_sel/char_4.png");
	ALLEGRO_BITMAP * char_5 = al_load_bitmap("resources/characters/char_sel/char_5.png");

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	ALLEGRO_EVENT ev;

	do{
		//Pone al fonde de color
		al_clear_to_color(al_map_rgb(54,1,63));

		//Escribe en el buffer la leyenda
		al_draw_text(font_title, al_map_rgb(233, 65, 150), DISPLAY_CENTRE, 250, ALLEGRO_ALIGN_CENTER, "Write your name to save the score of your game:");
		al_draw_text(font_subtitle, al_map_rgb(233, 65, 150), DISPLAY_CENTRE, DISPLAY_SIZE - 50, ALLEGRO_ALIGN_CENTER, "After you're done, press ENTER to continue");

		//Genera la caja donde se escribe el nombre del jugador para que se pueda visualizar
		al_draw_filled_rounded_rectangle(DISPLAY_CENTRE - 235, DISPLAY_CENTRE - 145, DISPLAY_CENTRE + 235, DISPLAY_CENTRE - 50, 10, 10, al_map_rgb(227,185,255));
		al_draw_filled_rounded_rectangle(DISPLAY_CENTRE - 230, DISPLAY_CENTRE - 140, DISPLAY_CENTRE + 230, DISPLAY_CENTRE - 55, 10, 10, al_map_rgb(186,85,255));

		//Escribe en el buffer el nombre:
		al_draw_text(font_name, al_map_rgb(250, 218, 225), DISPLAY_CENTRE - 215, DISPLAY_CENTRE -120, ALLEGRO_ALIGN_LEFT, name);

		al_flip_display();

		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				exit = 0;
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
				int sel = 3, confirm = 1;

				do{
					//Pone al fonde de color
					al_clear_to_color(al_map_rgb(54,1,63));

					al_draw_textf(font_title, al_map_rgb(233, 65, 150), DISPLAY_CENTRE, 250, ALLEGRO_ALIGN_CENTER, "Well done %s, now choose your Barbie!", name);
					al_draw_text(font_subtitle, al_map_rgb(233, 65, 150), DISPLAY_CENTRE, DISPLAY_SIZE - 50, ALLEGRO_ALIGN_CENTER, "After you're done, press ENTER to choose your player");

					character_displayer_menu(sel, char_1, char_2, char_3, char_4, char_5);

					al_flip_display();

					al_wait_for_event(event_queue, &ev);

					if(ev.type == ALLEGRO_EVENT_KEY_CHAR){
						if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT){
							if(sel < 5){
								sel++;
							}
							else{
								sel = 1;
							}
						}
						else if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT){
							if(sel > 1){
								sel--;
							}
							else{
								sel = 5;
							}
						}
						else if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
							confirm = 0;
						}
					}

				}while(confirm);

				al_destroy_event_queue(event_queue);
				al_destroy_font(font_title);
				al_destroy_font(font_subtitle);
				al_destroy_font(font_name);

				return sel;
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
				if(pos > 0){
					name[--pos] = '\0';
				}
			}
			else if(ev.keyboard.unichar >= 32 && ev.keyboard.unichar <= 126){
				if(al_get_text_width(font_name, name) < 435){
					name[pos++] = (char)ev.keyboard.unichar;
					name[pos] = '\0';
				}
			}
		}

	}while(exit);

	al_destroy_event_queue(event_queue);

	return 0;

}

/* FUNCIÓN CHARACTER_DISPLAYER_MENU
 * BRIEF: Se encarga de mostrar en pantalla los personajes para que el jugador seleccione uno de ellos
 * sel: (int) Cual es la selección de personaje a resaltar
 * char_1: (puntero ALLEGRO_BITMAP) La imagen del personaje 1
 * char_2: (puntero ALLEGRO_BITMAP) La imagen del personaje 2
 * char_3: (puntero ALLEGRO_BITMAP) La imagen del personaje 3
 * char_4: (puntero ALLEGRO_BITMAP) La imagen del personaje 4
 * char_5: (puntero ALLEGRO_BITMAP) La imagen del personaje 5
 * return: (void)
 *  */
const void character_displayer_menu (int sel, ALLEGRO_BITMAP * char_1, ALLEGRO_BITMAP * char_2, ALLEGRO_BITMAP * char_3, ALLEGRO_BITMAP * char_4, ALLEGRO_BITMAP * char_5){

	switch (sel){
	case 1:
		al_draw_scaled_bitmap(char_1, 0, 0, 650, 650, 004, DISPLAY_CENTRE - 100, 200, 200, 0);
		al_draw_scaled_bitmap(char_2, 0, 0, 650, 650, 208, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_3, 0, 0, 650, 650, 396, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_4, 0, 0, 650, 650, 582, DISPLAY_CENTRE - 90 , 172, 172, 0);
		al_draw_scaled_bitmap(char_5, 0, 0, 650, 650, 772, DISPLAY_CENTRE - 84 , 168, 168, 0);
		break;
	case 2:
		al_draw_scaled_bitmap(char_1, 0, 0, 650, 650, 020, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_2, 0, 0, 650, 650, 192, DISPLAY_CENTRE - 100, 200, 200, 0);
		al_draw_scaled_bitmap(char_3, 0, 0, 650, 650, 396, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_4, 0, 0, 650, 650, 582, DISPLAY_CENTRE - 90 , 172, 172, 0);
		al_draw_scaled_bitmap(char_5, 0, 0, 650, 650, 772, DISPLAY_CENTRE - 84 , 168, 168, 0);
		break;
	case 3:
		al_draw_scaled_bitmap(char_1, 0, 0, 650, 650, 020, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_2, 0, 0, 650, 650, 208, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_3, 0, 0, 650, 650, 380, DISPLAY_CENTRE - 100, 200, 200, 0);
		al_draw_scaled_bitmap(char_4, 0, 0, 650, 650, 582, DISPLAY_CENTRE - 90 , 172, 172, 0);
		al_draw_scaled_bitmap(char_5, 0, 0, 650, 650, 772, DISPLAY_CENTRE - 84 , 168, 168, 0);
		break;
	case 4:
		al_draw_scaled_bitmap(char_1, 0, 0, 650, 650, 020, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_2, 0, 0, 650, 650, 208, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_3, 0, 0, 650, 650, 396, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_4, 0, 0, 650, 650, 565, DISPLAY_CENTRE - 100, 200, 200, 0);
		al_draw_scaled_bitmap(char_5, 0, 0, 650, 650, 772, DISPLAY_CENTRE - 84 , 168, 168, 0);
		break;
	case 5:
		al_draw_scaled_bitmap(char_1, 0, 0, 650, 650, 020, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_2, 0, 0, 650, 650, 208, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_3, 0, 0, 650, 650, 396, DISPLAY_CENTRE - 84 , 168, 168, 0);
		al_draw_scaled_bitmap(char_4, 0, 0, 650, 650, 582, DISPLAY_CENTRE - 90 , 172, 172, 0);
		al_draw_scaled_bitmap(char_5, 0, 0, 650, 650, 756, DISPLAY_CENTRE - 100, 200, 200, 0);

	}
}


void display_game_over (const int score){
	ALLEGRO_FONT *font_title = NULL;
	font_title = al_load_ttf_font("resources/Barbie-font.ttf", TITLE_SIZE, 0);
	ALLEGRO_FONT *font_score = NULL;
	font_score = al_load_ttf_font("resources/Barbie-font.ttf", 55, 0);
	ALLEGRO_FONT *font_description = NULL;
	font_description = al_load_ttf_font("resources/Barbie-font.ttf", 35, 0);

	int i = score_saver(score);

	al_clear_to_color(al_map_rgb(54,1,63));

	al_draw_text(font_title, al_map_rgb(TITLE_COLOR), DISPLAY_CENTRE, 135, ALLEGRO_ALIGN_CENTER, "Game Over! :(");
	al_draw_textf(font_score, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, 350, ALLEGRO_ALIGN_CENTER, "Your score was: %d", score);
	al_draw_text(font_description, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, 750, ALLEGRO_ALIGN_CENTER, "Press any key to go back to the main menu");

	if(i == 1){
		al_draw_textf(font_description, al_map_rgb(BUTTON_COLOR), DISPLAY_CENTRE, DISPLAY_SIZE, ALLEGRO_ALIGN_CENTER, "Congrats! You made it to the scoreboard, check the scoreboard to see your position.");
	}
	else if( i == -1){
		al_draw_textf(font_description, al_map_rgb(255,0,0), DISPLAY_CENTRE, DISPLAY_SIZE, ALLEGRO_ALIGN_CENTER, "An error happend while trying to save the scoreboard :(");
	}


	al_flip_display();
}

