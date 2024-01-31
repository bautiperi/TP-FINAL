raspberry: main.o obj_r.o aux_r.o menu_r.o conection_b_r.o back_map.o back_aux.o back_score.o disdrv.o joydrv.o back_enemy.o back_player.o
	gcc main.o obj_r.o aux_r.o menu_r.o conection_b_r.o back_map.o disdrv.o joydrv.o back_aux.o back_score.o back_enemy.o back_player.o -Wall -g -pthread -o raspberry

#	FRONT	

main.o: main.c back_map.h disdrv.h joydrv.h _defines.h _defines_display_r.h conection_b_r.h aux_r.h menu_r.h back_player.h back_enemy.h
	gcc main.c -c -Wall -g -lpthread 

obj_r.o: obj_r.c obj_r.h aux_r.h disdrv.h joydrv.h _defines.h
	gcc obj_r.c -c -Wall -g 
	
menu_r.o: menu_r.c menu_r.h disdrv.h joydrv.h aux_r.h _defines.h
	gcc menu_r.c -c -Wall -g

aux_r.o: aux_r.c aux_r.h disdrv.h joydrv.h _defines.h _defines_display_r.h
	gcc aux_r.c -c -Wall -g 

#	CONEXION B-F

conection_b_r.o: conection_b_r.c conection_b_r.h obj_r.h defines.h
	gcc conection_b_r.c -c -Wall -g

#	BACK

back_aux.o: back_aux.c back_aux.h _defines.h
	gcc back_aux.c -c -Wall -g

back_enemy.o: back_enemy.c back_enemy.h back_map.h back_player.h back_aux.h back_score.h _defines.h
	gcc back_enemy.c -c -Wall -g

back_map.o: back_map.c back_map.h _defines.h back_enemy.h
	gcc back_map.c -c -Wall -g

back_player.o: back_player.c back_player.h _defines.h back_aux.h back_enemy.h back_score
	gcc back_player.c -c -Wall -g

back_score.o: back_score.c back_score.h _defines.h
	gcc back_score.c -c -Wall -g
