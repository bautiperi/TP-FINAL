#ifndef RASPBERRY
// ----------------------------------------------------------------------------- //

// INCLUDE HEADER FILES

//FRONT
#include "disp_start_menu_a.h"
#include "disp_game_a.h"
#include "disp_scoreboard_a.h"
#include "_defines_display.h"

//BACK
#include "back_map.h"
#include "back_player.h"
#include "back_enemy.h"

//LIBRERIAS
#include <stdio.h>
#include <pthread.h>
#include <allegro5/allegro.h>

//Variable global que sirve como flag para detener la ejecución de los threads
// 0 -> Falso, están en pausa | 1 -> Ejecutan | 2 -> Exit threads
int flag_game_update = 0;

// Declaración de variables globales
int is_shooting = 0; // Flag que sirve para verificar si se puede disparar
double last_shot_time = 0.0;
double shot_cooldown = 0.75;  // Definimos el tiempo entre cada disparo
// ----------------------------------------------------------------------------- //

// PROTOTIPO DE FUNCIONES

/* FUNCIÓN UPDATE_PLAYER_KEYBOARD (hecha para threads)
 * BRIEF: Es la función que se encarga de la interacción entre el usuario y dentro del juego
 * mapa: (matriz de ints) Es la matriz donde se desarrolla el juego
 * return: (void *)
 */
void * update_player_keyboard (void * arg);

int main(void){

	//INICIALIZA EL DISPLAY
	ALLEGRO_DISPLAY * display = display_init();

	if (display == NULL){
		fprintf(stderr, "Error al inicializar el display y sus librerias, descripción del error arriba");
		return -1;
	}

	int sel = 0;
	int dificultad = NORMAL;

	while( sel != QUIT ){
		sel = display_start_menu(&dificultad, display);

		//Inicializar juego
		if(sel == NEW_GAME){
			int mapa[FIL][COL];

			map_def(dificultad, mapa, 0);

			//Flag en 0 para que los threads no se inicialicen y estén en pausa
			flag_game_update = 0;

			pthread_t up_aliens, up_boss, up_player, enemy_shot;

			pthread_create(&up_boss, NULL, final_boss_creation, mapa);
			pthread_create(&up_aliens, NULL, alien_movement, mapa);
			pthread_create(&up_player, NULL, update_player_keyboard, mapa);
			pthread_create(&enemy_shot, NULL, enemy_fire, mapa);

			sel = display_game(mapa, display);
		}

		//Cierra los threads
		flag_game_update = 2;
	}

	al_destroy_display(display);
	return 0;

}

void *update_player_keyboard(void *arg) {
    int (*mapa)[COL] = (int (*)[COL])arg;

    // DETECTA CUANDO SE OPRIME COSAS EN EL TECLADO
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    ALLEGRO_EVENT event;

    while (1) {
        // Espera a que se habilite el funcionamiento de threads
        // Vacía la cola de eventos para evitar que se acumulen
        if (flag_game_update == 0) {
            al_get_next_event(event_queue, &event);
        }
        // Cierra el thread
        else if (flag_game_update == 2) {
            al_destroy_event_queue(event_queue);
            pthread_exit(NULL);
        } else {
            al_get_next_event(event_queue, &event);

            // Gestiona el movimiento
            if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_CHAR) {
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D) {
                    gamer_movement(mapa, 1);
                    al_rest(0.045);
                } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A) {
                    gamer_movement(mapa, -1);
                    al_rest(0.045);
                }
            }

            // Gestiona los disparos con un delay
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    double current_time = al_get_time();

                    // Verifica que haya pasado el tiempo suficiente desde el último disparo
                    if (current_time - last_shot_time >= shot_cooldown) {
                        if (!is_shooting) {
                            is_shooting = 1;
                            pthread_t gamer_shot;
                            pthread_create(&gamer_shot, NULL, gamer_fire, mapa);
                            last_shot_time = current_time;  // Actualiza el tiempo desde el último disparo
                        }
                    }
                }
            }
        }
    }
}

#else

// LIBRERIAS
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "joydrv.h"
#include "disdrv.h"

// CONEXION BACK-FRONT
#include "conection_b_r.h"

// FRONT
#include "menu_r.h"
#include "aux_r.h"
#include "score_r.h"

// BACK
#include "back_player.h"
#include "back_map.h"
#include "back_enemy.h"
#include "back_score.h"

// INCLUDE HEADER FILES
#include "_defines.h"
#include "_defines_display_r.h"

int flag_game_update = 0;

int main(void)
{
	disp_init(); // se inicializa el display
	disp_clear();

	int mapa[FIL][COL];
	map_def(RASP, mapa, 0);

	// creacion de threads
	pthread_t up_aliens, up_boss, up_aliens_fire;
	pthread_create(&up_boss, NULL, final_boss_creation, mapa);
	pthread_create(&up_aliens, NULL, alien_movement, mapa);
	pthread_create(&up_aliens_fire, NULL, enemy_fire, mapa);

	joy_init();
	STATUS = 2;
	joyinfo_t coord;
	int npos = 0;
	dcoord_t coord_menu = {15, 0};
	SELECT_OPTION = 0; // flag para seleccion en el menu
	CLOSE_GAME = 0; // flag para terminar la ejecucion

	do
	{
		while (STATUS == 0) // JUEGO
		{
			obj_vis(mapa);
			coord = joy_read();
			usleep(30000);
			disp_write(coord_menu, D_ON); // coordenada que simula un "boton" de menu

			if ((coord.sw) == (J_PRESS)) // dispara el player
			{
				pthread_t up_gamer_fire;
				pthread_create(&up_gamer_fire, NULL, gamer_fire, mapa);
				usleep(25000);
			}
			if (coord.x > THRESHOLD) // movimiento a la derecha
			{
				npos = 1;
			}
			else if (coord.x < -THRESHOLD) // movimiento a la izquierda
			{
				npos = -1;
			}
			else
			{
				npos = 0;
			}

			if (coord.y >= THRESHOLD)
			{ // si la coordenada en y no se movio hacia la seleccion del menu
				disp_write(coord_menu, D_OFF);
				STATUS = 1;
				flag_game_update = 0;
			}
			if (LIVES == 0)
			{
				disp_write(coord_menu, D_OFF);
				STATUS = 3;
				flag_game_update = 0;
			}
			gamer_movement(mapa, npos); // genera el movimiento del player
		}
		while (STATUS == 1) // MENU
		{
			coord = joy_read();
			menu_vis(mapa);
			if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
			{
				SELECT_OPTION = 1; // SALIR
			}

			if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
			{
				SELECT_OPTION = 0; // PLAY
			}

			if (SELECT_OPTION == 1 && coord.sw == J_PRESS)
			{
				STATUS = 3; // CAMBIA A MENU PRINCIPAL
			}
			else if (SELECT_OPTION == 0 && coord.sw == J_PRESS)
			{
				STATUS = 0; // VUELVE AL JUEGO
				flag_game_update = 1;
			}
		}
		while (STATUS == 2) // MENU PRINCIPAL
		{
			coord = joy_read();
			menu_principal_vis(mapa);
			if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
			{
				SELECT_OPTION = 1; // APAGAR
			}

			if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
			{
				SELECT_OPTION = 0; // PLAY
			}

			if (SELECT_OPTION == 1 && coord.sw == J_PRESS)
			{
				shutdown_disp(); // APAGA EL DISPLAY
				flag_game_update = 0;
				CLOSE_GAME = 1; // INDICA QUE SE TERMINO EL JUEGO
				STATUS = 4;
			}
			else if (SELECT_OPTION == 0 && coord.sw == J_PRESS)
			{
				STATUS = 0; // VUELVE AL JUEGO
				map_def(RASP, mapa, 0);
				flag_game_update = 1;
			}
		}
		while (STATUS == 3) // VISUALIZACION DEL SCORE
		{
			game_over();
			usleep(500000);
			score_vis(SCORE);
			printf("\n %d \n", SCORE);
			usleep(6000000);
			STATUS = 2;
		}
	} while (CLOSE_GAME != 1);

	game_over();
	usleep(500000);
	shutdown_disp();
	usleep(500000);

	return 0;
}
#endif
