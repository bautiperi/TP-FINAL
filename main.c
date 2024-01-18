#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <allegro5/allegro.h>

#include "map.h"
#include "disp_start_menu_a.h"
#include "disp_game_a.h"
#include "back_game_a.h"

int main(void){

	//INICIALIZA EL DISPLAY
	ALLEGRO_DISPLAY * display = display_init();

	if (display == NULL){
		fprintf(stderr, "Error al inicializar el display y sus librerias, descripción del error arriba");
		return -1;
	}

	int mapa[FIL][COL];

	map_def(EASY, mapa);

	display_game(mapa);

	return 0;

}
