// LIBS
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "joydrv.h"
#include "disdrv.h"

// CONEXION B-F
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

// DEFINES
#include "_defines.h"
#include "_defines_display_r.h"

int flag_game_update = 0;

int main(void)
{
	disp_init();
	disp_clear();

	int mapa[FIL][COL];
	map_def(RASP, mapa, 0);

	pthread_t up_aliens, up_boss, up_aliens_fire, up_vis;
	pthread_create(&up_vis, NULL, obj_vis, mapa);
	pthread_create(&up_boss, NULL, final_boss_creation, mapa);
	pthread_create(&up_aliens, NULL, alien_movement, mapa);
	pthread_create(&up_aliens_fire, NULL, enemy_fire, mapa);

	joy_init();
	STATUS = 2;
	joyinfo_t coord = {0, 0, J_NOPRESS};
	int npos = 0;
	dcoord_t coord_menu = {0, 15};
	FLICK_OPTION = 0; // flag para seleccion en el menu
	// JUEGO
	CLOSE_GAME = 0;

	do
	{
		while (STATUS == 0) // JUEGO
		{
			coord = joy_read();
			// led_flick(coord_menu);

			if ((coord.sw) == (J_PRESS)) // dispara el player
			{
				pthread_t up_gamer_fire;
				pthread_create(&up_gamer_fire, NULL, gamer_fire, mapa);
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
				STATUS = 1;
				flag_game_update = 0;
			}
			if (LIVES == 0)
			{
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
				FLICK_OPTION = 1; // TITILA EL PLAY
			}

			if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
			{
				FLICK_OPTION = 0; // TITLA EL SALIR
			}

			if (FLICK_OPTION == 1 && coord.sw == J_PRESS)
			{
				usleep(50000);
				STATUS = 2; // CAMBIA A MENU PRINCIPAL
			}
			else if (FLICK_OPTION == 0 && coord.sw == J_PRESS)
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
				FLICK_OPTION = 1; // TITILA EL APAGAR
			}

			if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
			{
				FLICK_OPTION = 0; // TITLA EL PLAY
			}

			if (FLICK_OPTION == 1 && coord.sw == J_PRESS)
			{
				shutdown_disp(); // APAGA EL DISPLAY
				flag_game_update = 0;
				CLOSE_GAME = 1; // INDICA QUE SE TERMNINO EL JUEGO
				STATUS = 4;
			}
			else if (FLICK_OPTION == 0 && coord.sw == J_PRESS)
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
			usleep(4000000);
			STATUS = 2;
		}
	} while (CLOSE_GAME != 1);

	game_over();
	usleep(500000);
	shutdown_disp();
	usleep(500000);

	return 0;
}
