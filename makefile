raspberry: main.o obj_r.o aux_r.o menu_r.o conection_b_r.o map.o ships.o back_aux_a.o back_game_a.o back_score_a.o disdrv.o joydrv.o joy_read.o
	gcc main.o obj_r.o aux_r.o menu_r.o conection_b_r.o map.o ships.o disdrv.o joydrv.o back_aux_a.o back_game_a.o back_score_a.o -Wall -g -pthread -o raspberry
	
main.o: main.c map.h disdrv.h joydrv.h defines.h conection_b_r.h aux_r.h back_game_a.h
	gcc main.c -c -Wall -g -lpthread 

obj_r.o: obj_r.c obj_r.h aux_r.h disdrv.h joydrv.h defines.h
	gcc obj_r.c -c -Wall -g 
	
menu_r.o: menu_r.c menu_r.h disdrv.h joydrv.h aux_r.h defines.h
	gcc menu_r.c -c -Wall -g

aux_r.o: aux_r.c aux_r.h disdrv.h joydrv.h defines.h
	gcc aux_r.c -c -Wall -g 

conection_b_r.o: conection_b_r.c conection_b_r.h obj_r.h defines.h
	gcc conection_b_r.c -c -Wall -g

map.o: map.c map.h ships.h defines.h
	gcc map.c -c -Wall -g

ships.o: ships.c ships.h defines.h
	gcc ships.c -c -Wall -g

back_game_a.o: back_game_a.c back_game_a.h back_aux_a.h back_score_a.h defines.h
	gcc back_game_a.c -c -Wall -g

back_aux_a.o: back_aux_a.c back_aux_a.h defines.h
	gcc back_aux_a.c -c -Wall -g

back_score_a.o: back_score_a.c back_score_a.h defines.h
	gcc back_score_a.c -c -Wall -g

joy_read.o: joy_read.c joy_read.h defines.h joydrv.h disdrv.h menu_r.h map.h obj_r.h back_game_a.h
	gcc joy_read.c -c -Wall -g