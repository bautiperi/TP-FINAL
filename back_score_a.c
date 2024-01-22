#include "back_score_a.h"

void score_updater (int mapa[][COL], int identifier){

	//Dependiendo del enemigo al que se le pegó, se agregarán una determinada cantidad de puntos al score
	switch (identifier) {
	case 2:
		mapa[0][COL - 2] += 10;
		break;
	case 3:
		mapa[0][COL - 2] += 20;
		break;
	case 4:
		mapa[0][COL - 2] += 30;
		break;
	case 5:
		mapa[0][COL - 2] += 50;
		break;
	}

}

void score_saver (int mapa[][COL]){
	//Seguir
}
