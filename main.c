#include <unistd.h>
#include <pthread.h>

#include "conection_b_r.h"
#include "aux_r.h"
#include "map.h"
#include "joydrv.h"
#include "disdrv.h"
#include "back_aux_a.h"
#include "back_game_a.h"
#include "joy_read.h"

int main(void)
{
	int sel = 0;
	disp_init();
	joy_init();
	disp_clear();

	int mapa[FIL][COL];
	map_def(RASP, mapa);

	pthread_t up_aliens, up_boss, up_vis, up_aliens_fire;
	joyinfo_t coord = {0, 0, J_NOPRESS};
	int npos = 0;
	dcoord_t coord_menu = {0, 15};
	dcoord_t coords = {15, 0};
	FLICK_OPTION = 0; // flag para seleccion en el menu
	// JUEGO
	do
	{
		coord = joy_read();
		if (STATUS == 0) // JUEGO
		{
			pthread_create(&up_boss, NULL, final_boss_creation, mapa);
			pthread_create(&up_aliens, NULL, alien_movement, mapa);
			pthread_create(&up_aliens_fire, NULL, enemy_fire, mapa);
			led_flick(coord_menu);

			obj_vis(mapa, mapa[0][COL - 1]);
			if (coord.sw = J_PRESS) // dispara el player
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
			}
			gamer_movement(mapa, npos); // genera el movimiento del player
		}
		if (STATUS == 1) // MENU
		{
			menu_vis(mapa);
			if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
			{
				FLICK_OPTION = 1; // TITILA EL PLAY
			}
			else if (coord.x > THRESHOLD && coord.sw == J_PRESS)
			{
				STATUS = 2; // CAMBIA A MENU PRINCIPAL
			}
			if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
			{
				FLICK_OPTION = 0; // TITLA EL SALIR
			}
			else if (coord.x < -THRESHOLD && coord.sw == J_PRESS)
			{
				STATUS = 0; // VUELVE AL JUEGO
			}
		}
		if (STATUS == 2) // MENU PRINCIPAL
		{
			menu_principal_vis(mapa);
			if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
			{
				FLICK_OPTION = 1; // TITILA EL PLAY
			}
			else if (coord.x > THRESHOLD && coord.sw == J_PRESS)
			{
				shutdown_disp(); // APAGA EL DISPLAY
				END_GAME = 1;	 // INDICA QUE SE TERMNINO EL JUEGO
			}
			if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
			{
				FLICK_OPTION = 0; // TITLA EL APAGAR
			}
			else if (coord.x < -THRESHOLD && coord.sw == J_PRESS)
			{
				STATUS = 0; // VUELVE AL JUEGO
			}
		}
	} while (END_GAME != 1);
	game_over();
	usleep(500000);
	shutdown_disp();
	usleep(500000);

	return 0;
}
