CC=gcc
CFLAGS=-Wall -g -pthread
CLIBS=-lallegro

RASP=main.o obj_r.o aux_r.o menu_r.o conection_b_r.o disdrv.o joydrv.o score_r.o
COMMON=back_map.o back_aux.o back_score.o back_enemy.o back_player.o
ALL=main.o disp_game.o disp_pause.o disp_scoreboard.o disp_start_menu.o
ALLEGRO=disp_game.o disp_pause.o disp_scoreboard.o disp_start_menu.o

# Plataforma por defecto
PLATFORM ?= RASPBERRY

ifeq ($(PLATFORM), RASPBERRY)
    CFLAGS += -DRASPBERRY
    TARGET = raspberry
else ifeq ($(PLATFORM), ALLEGRO)
    TARGET = allegro
else
    $(error Platform not supported: $(PLATFORM))
endif

# TARGET
all: $(PLATFORM)

# TARGET RASPBERRY
RASPBERRY: $(RASP) $(COMMON)
	$(CC) -DRASPBERRY $(RASP) $(COMMON) -o raspberry $(CFLAGS)

# TARGET ALLEGRO
ALLEGRO: $(RASP) $(ALLEGRO) $(COMMON)
	$(CC) $(ALLEGRO) $(COMMON) -o allegro $(CFLAGS) $(CLIBS)

ifeq ($(TARGET), raspberry)
# Regla generica para la compilación de archivos fuente a objetos
%.o: %.c _defines.h
	$(CC) -DRASPBERRY -c $< -o $@ $(CFLAGS)

# Dependencias especificas para cada objeto - Front-end
main.o: main.c back_map.h disdrv.h joydrv.h _defines_display_r.h conection_b_r.h aux_r.h
obj_r.o: obj_r.c obj_r.h aux_r.h disdrv.h joydrv.h _defines.h _defines_display_r.h
menu_r.o: menu_r.c menu_r.h disdrv.h aux_r.h _defines.h _defines_display_r.h
aux_r.o: aux_r.c aux_r.h disdrv.h joydrv.h _defines.h _defines_display_r.h
conection_b_r.o: conection_b_r.c conection_b_r.h obj_r.h _defines.h disdrv.h joydrv.h aux_r.h
score_r.o: score_r.c score_r.h disdrv.h _defines.h back_map.h

# Dependencias especificas para cada objeto - Back-end
back_aux.o: back_aux.c back_aux.h _defines.h
back_enemy.o: back_enemy.c back_enemy.h back_map.h back_player.h back_aux.h back_score.h _defines.h
back_map.o: back_map.c back_map.h _defines.h back_enemy.h
back_player.o: back_player.c back_player.h _defines.h back_aux.h back_enemy.h back_score.h
back_score.o: back_score.c back_score.h _defines.h

else ifeq ($(TARGET), allegro)
# Regla generica para la compilación de archivos fuente a objetos
%.o: %.c _defines.h
	$(CC) -c $< -o $@ $(CFLAGS) $(CLIBS)

#front allegro
disp_game.o: disp_game.c disp_game.h _defines.h _defines_display.h disp_scoreboard.h disp_pause.h disp_game.h
disp_pause.o: disp_pause.c disp_pause.h _defines_display.h
disp_scoreboard.o: disp_scoreboard.c disp_scoreboard.h back_score.h _defines_display.h
disp_start_menu.o: disp_start_menu.c disp_start_menu.h disp_scoreboard.h _defines_display.h _defines.h
# Dependencias especificas para cada objeto - Back-end
back_aux.o: back_aux.c back_aux.h _defines.h
back_enemy.o: back_enemy.c back_enemy.h back_map.h back_player.h back_aux.h back_score.h _defines.h
back_map.o: back_map.c back_map.h _defines.h back_enemy.h
back_player.o: back_player.c back_player.h _defines.h back_aux.h back_enemy.h back_score.h
back_score.o: back_score.c back_score.h _defines.h

endif