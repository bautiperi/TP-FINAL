#include <unistd.h>
#include "obj_r.h"
#include "menu_r.h"
#include "map.h"
#include "ships.h"
#include "conection_b_r.h"
#include <stdio.h>

int main(void)
{
	disp_init();
	joy_init();
	disp_clear();

	int mapa[FIL][COL];
	mapdef(RASP, mapa);

	obj_gen(mapa, 3);

	return 0;
}
/*dcoord_t gamer = {1, 15};
	disp_init();
	joy_init();
	disp_clear();
	usleep(1000000);

	joyinfo_t ubi = joy_read();
	menu_vis(ubi);
	usleep(3000000);
	shutdown_disp();

	printf("EN MAIN -> GAMER_VIS: x: %d y: %d \n", gamer.x, gamer.y);
	gamer_vis(gamer);
	usleep(3000000);
	gamer_shot(gamer);
	usleep(3000000);

	dcoord_t final_boss = {1, 1};
	printf("EN MAIN -> FINAL_BOSS_VIS: x: %d y: %d \n", final_boss.x, final_boss.y);
	final_boss_vis(final_boss);
	usleep(3000000);
	final_boss_shot(final_boss);
	usleep(3000000);


	//dcoord_t alien = {1, 8};
	//printf("EN MAIN -> ALIEN_VIS: x: %d y: %d \n", alien.x, alien.y);
	//aliens_vis(alien);


	dcoord_t shield = {1, 12};
	printf("EN MAIN -> SHIELDS_VIS: x: %d y: %d \n", shield.x, shield.y);
	shields_vis(shield);
	usleep(3000000);

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
	usleep(50000);

	shutdown_disp();
	usleep(50000); */