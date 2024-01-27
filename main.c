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

	/*while (sel != )
	{

	}*/

	int mapa[FIL][COL];
	map_def(RASP, mapa);

	pthread_t up_aliens, up_boss, up_player, up_vis;
	// pthread_create(&up_player, NULL, joy_movement, mapa);
	pthread_create(&up_boss, NULL, final_boss_creation, mapa);
	pthread_create(&up_aliens, NULL, alien_movement, mapa);
	obj_vis(mapa, mapa[0][COL - 1]);

	shutdown_disp();
	usleep(500000);

	return 0;
}
