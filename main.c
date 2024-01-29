#include <unistd.h>
#include <pthread.h>

#include "conection_b_r.h"
#include "aux_r.h"
#include "map.h"
#include "joydrv.h"
#include "disdrv.h"
#include "back_aux_a.h"
#include "back_game_a.h"
#include "menu_r.h"
#include "joy_read.h"

int main(void)
{
	int sel = 0;
	disp_init();
	joy_init();
	disp_clear();

	int mapa[FIL][COL];

	pthread_t up_aliens, up_boss, up_aliens_fire, up_joy;
	pthread_create(&up_boss, NULL, final_boss_creation, mapa);
	pthread_create(&up_aliens, NULL, alien_movement, mapa);
	pthread_create(&up_aliens_fire, NULL, enemy_fire, mapa);
	pthread_create(&up_boss, NULL, joy_reading, mapa);

	game_over();
	usleep(500000);
	shutdown_disp();
	usleep(500000);

	return 0;
}
