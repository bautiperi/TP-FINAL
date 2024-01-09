raspberry: obj_r.o aux_r.o main.o
	gcc obj_r.o aux_r.o -Wall -g -o raspberry -l"/libs/disdrv.h" -l"/libs/joydrv.h"
	
main.o: main.c obj_r.h
	gcc main.c -c -Wall -g -l"/libs/disdrv.h" -l"/libs/joydrv.h"

obj_r.o: obj_r.c obj_r.h aux_r.h
	gcc obj_r.c -c -Wall -g -l"/libs/disdrv.h" -l"/libs/joydrv.h"
	
aux_r.o: aux_r.c aux_r.h
	gcc aux_r.c -c -Wall -g -l"/libs/disdrv.h" -l"/libs/joydrv.h"