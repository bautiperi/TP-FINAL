raspberry: main.o obj_r.o aux_r.o menu_r.o disdrv.o joydrv.o
	gcc main.o obj_r.o aux_r.o menu_r.o disdrv.o joydrv.o -Wall -g -o raspberry
	
main.o: main.c obj_r.h disdrv.h joydrv.h
	gcc main.c -c -Wall -g 

obj_r.o: obj_r.c obj_r.h aux_r.h disdrv.h joydrv.h
	gcc obj_r.c -c -Wall -g 
	
menu_r.o: menu_r.c menu_r.h disdrv.h joydrv.h aux_r.h
	gcc menu_r.c -c -Wall -g

aux_r.o: aux_r.c aux_r.h disdrv.h joydrv.h
	gcc aux_r.c -c -Wall -g 
