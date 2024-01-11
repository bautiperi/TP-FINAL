#include <unistd.h>
#include "obj_r.h"
#include <stdio.h>

int main(void)
{
	dcoord_t gamer = {1, 1};
	disp_init();
	joy_init();
	shutdown_disp();

	printf("EN MAIN -> GAMER_VIS: x: %d y: %d \n", gamer.x, gamer.y);
	gamer_vis(gamer);
	gamer_shot(gamer);

	dcoord_t final_boss = {1, 15};
	printf("EN MAIN -> FINAL_BOSS_VIS: x: %d y: %d \n", final_boss.x, final_boss.y);
	final_boss_vis(final_boss);
	final_boss_shot(final_boss);

	/*
	dcoord_t alien = {1, 8};
	printf("EN MAIN -> ALIEN_VIS: x: %d y: %d \n", alien.x, alien.y);
	aliens_vis(alien);
	*/

	dcoord_t shield = {1, 4};
	printf("EN MAIN -> SHIELDS_VIS: x: %d y: %d \n", shield.x, shield.y);
	shields_vis(shield);

	lives_vis(3);
	usleep(3000000);
	lives_vis(2);
	usleep(3000000);
	lives_vis(1);
	usleep(3000000);
	disp_update();
	usleep(3000000);

	shutdown_disp();

	game_over();

	return 0;
}
