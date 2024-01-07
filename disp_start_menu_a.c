#include "disp_start_menu_a.h"
#include <stdio.h>

#define FPS 60.0

int display_init (void){
	ALLEGRO_DISPLAY * display = NULL;

	//Inicializa Allegro
	if ( !al_init()) {
		fprintf(stderr, "No se pudo inicializar allegro \n");
		return -1;
	}

	//Inicializa el timer
	ALLEGRO_TIMER *timer = NULL;
	timer = al_create_timer(1.0 / FPS); //crea el timer pero NO empieza a correr
	    if (!timer) {
	        fprintf(stderr, "No se pudo inicializar el timer\n");
	        return -1;
	    }

	//Inicializa el manejo de imágenes
	if (!al_init_image_addon()) {
	        fprintf(stderr, "No se pudo inicializar el manejo de imagenes\n");
	        return -1;
	}

	//Inicializa el uso de formas
		if (!al_init_primitives_addon()) {
			fprintf(stderr, "No se pudo inicializar el manejo de primitivas\n");
			return -1;
		}

	//Inicializa el uso de fonts
	if (!al_init_font_addon() || !al_init_ttf_addon()) {
		fprintf(stderr, "No se pudo inicializar el manejo de fuentes y texto\n");
		return -1;
	}

	//Inicializa el display
	display = al_create_display(720, 720);
	if (!display) {
		fprintf(stderr, "No se pudo crear el display \n");
		return -1;
	}

	return 0;
}

// Acá van todas las funciones del menú de inicio
