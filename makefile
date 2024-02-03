CC=gcc
CFLAGS=-Wall -g -pthread
CLIBS=-lallegro -lallegro_acodec -lallegro_audio -lallegro_image -lallegro_primitives -lallegro_font -lallegro_font -lallegro_ttf

RASP=main.o obj_r.o aux_r.o menu_r.o conection_b_r.o disdrv.o joydrv.o score_r.o
COMMON=back_map.o back_aux.o back_score.o back_enemy.o back_player.o
ALLEGRO=main.o disp_game_a.o disp_pause_a.o disp_scoreboard_a.o disp_start_menu_a.o
MAIN=main.c 

# Plataforma por defecto
PLATFORM ?= RASPBERRY
# Target por defecto
TARGET ?= RASPBERRY

ifeq ($(PLATFORM), RASPBERRY)
    CFLAGS += -DRASPBERRY
    TARGET = raspberry
	MAIN +=back_map.h back_player.h back_enemy.h back_score.h disdrv.h joydrv.h _defines_display_r.h conection_b_r.h aux_r.h menu_r.h score_r.h
else ifeq ($(PLATFORM), ALLEGRO)
    TARGET = ALLEGRO
	MAIN +=disp_start_menu_a.h disp_game_a.h disp_scoreboard_a.h _defines_display.h back_map.h back_player.h back_enemy.h
else
    $(error Platform not supported: $(PLATFORM))
endif

# TARGET
all: $(PLATFORM)

# TARGET RASPBERRY
RASPBERRY: $(RASP) $(COMMON)
	$(CC) -DRASPBERRY $(RASP) $(COMMON) -o raspberry $(CFLAGS)

# TARGET ALLEGRO
ALLEGRO: $(ALLEGRO) $(COMMON)
	$(CC) $(ALLEGRO) $(COMMON) -o allegro $(CFLAGS) $(CLIBS)

ifeq ($(TARGET), raspberry)
# Regla generica para la compilación de archivos fuente a objetos
%.o: %.c _defines.h
	$(CC) -DRASPBERRY -c $< -o $@ $(CFLAGS)

# Target main.o
main.o: $(MAIN)

# Front-end RASPBERRY
obj_r.o: obj_r.c obj_r.h aux_r.h disdrv.h _defines.h _defines_display_r.h
menu_r.o: menu_r.c menu_r.h disdrv.h aux_r.h _defines.h _defines_display_r.h
aux_r.o: aux_r.c aux_r.h disdrv.h joydrv.h _defines.h _defines_display_r.h
conection_b_r.o: conection_b_r.c conection_b_r.h obj_r.h _defines.h disdrv.h joydrv.h aux_r.h
score_r.o: score_r.c score_r.h disdrv.h _defines.h aux_r.h

# Dependencias especificas para cada objeto - Back-end
back_aux.o: back_aux.c back_aux.h _defines.h
back_enemy.o: back_enemy.c back_enemy.h back_map.h back_aux.h back_score.h _defines.h
back_map.o: back_map.c back_map.h _defines.h
back_player.o: back_player.c back_player.h _defines.h back_aux.h back_enemy.h back_score.h
back_score.o: back_score.c back_score.h _defines.h

else ifeq ($(TARGET), ALLEGRO)
# Regla generica para la compilación de archivos fuente a objetos
%.o: %.c _defines.h
	$(CC) -c $< -o $@ $(CFLAGS) $(CLIBS)

#front allegro
disp_game_a.o: disp_game_a.c disp_game_a.h _defines.h _defines_display.h disp_scoreboard_a.h disp_pause_a.h disp_game_a.h
disp_pause_a.o: disp_pause_a.c disp_pause_a.h _defines_display.h
disp_scoreboard_a.o: disp_scoreboard_a.c disp_scoreboard_a.h back_score.h _defines_display.h
disp_start_menu_a.o: disp_start_menu_a.c disp_start_menu_a.h disp_scoreboard_a.h _defines_display.h _defines.h
# Dependencias especificas para cada objeto - Back-end
back_aux.o: back_aux.c back_aux.h _defines.h
back_enemy.o: back_enemy.c back_enemy.h back_map.h back_aux.h back_score.h _defines.h
back_map.o: back_map.c back_map.h _defines.h
back_player.o: back_player.c back_player.h _defines.h back_aux.h back_enemy.h back_score.h
back_score.o: back_score.c back_score.h _defines.h

endif
