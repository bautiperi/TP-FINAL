#include <unistd.h>
#include "obj_r.h"

int main(void)
{
	dcoord_t gamer = {1, 1};
	disp_init();
	joy_init();
	gamer_vis(gamer);
	gamer_shot(gamer);

	dcoord_t final_boss = {1, 15};
	final_boss_vis(final_boss);
	final_boss_shot(final_boss);

	dcoord_t alien = {1, 8};
	aliens_vis(alien);

	dcoord_t shield = {1, 4};
	shields_vis(shield);

	lives_vis(3);
	usleep(3000000);
	lives_vis(2);
	usleep(3000000);
	lives_vis(1);
	usleep(3000000);

	// game_over();

	return 0;
}
