CC=gcc
CFLAGS=-Wall -g -pthread
OBJS=main.o obj_r.o aux_r.o menu_r.o conection_b_r.o back_map.o back_aux.o back_score.o disdrv.o joydrv.o back_enemy.o back_player.o score_r.o

raspberry: $(OBJS)
	$(CC) -DRASPBERRY $(OBJS) -o raspberry $(CFLAGS)

# regla generica para la compilación de archivos fuente a objetos
%.o: %.c _defines.h
	$(CC) -DRASPBERRY -c $< -o $@ $(CFLAGS)

# dependencias especificas para cada objeto
main.o: back_map.h disdrv.h joydrv.h _defines_display_r.h conection_b_r.h aux_r.h menu_r.h back_player.h back_enemy.h back_score.h score_r.h obj_r.h
obj_r.o: obj_r.h aux_r.h disdrv.h joydrv.h _defines.h _defines_display_r.h
menu_r.o: menu_r.h disdrv.h joydrv.h aux_r.h _defines.h
aux_r.o: aux_r.h disdrv.h joydrv.h _defines.h _defines_display_r.h
conection_b_r.o: conection_b_r.h obj_r.h _defines.h disdrv.h joydrv.h aux_r.h
back_aux.o: back_aux.h _defines.h
back_enemy.o: back_enemy.h back_map.h back_player.h back_aux.h back_score.h _defines.h
back_map.o: back_map.h _defines.h back_enemy.h
back_player.o: back_player.h _defines.h back_aux.h back_enemy.h back_score.h
back_score.o: back_score.h _defines.h
score_r.o: score_r.c score_r.h disdrv.h _defines.h back_map.h