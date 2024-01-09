raspberry: obj_r.o aux_r.o main.o disdrv.o joydrv.o
	gcc obj_r.o aux_r.o disdrv.o joydrv.o -Wall -g -o raspberry 
	
main.o: main.c obj_r.h disdrv.h joydrv.h
	gcc main.c -c -Wall -g 

obj_r.o: obj_r.c obj_r.h aux_r.h disdrv.h joydrv.h
	gcc obj_r.c -c -Wall -g 
	
aux_r.o: aux_r.c aux_r.h disdrv.h joydrv.h
	gcc aux_r.c -c -Wall -g 