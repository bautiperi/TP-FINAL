#ifndef JOY_READ_H
#define JOY_READ_H

#include "defines.h"
#include "joydrv.h"
#include "disdrv.h"
#include "menu_r.h"
#include "map.h"
#include "obj_r.h"
#include "back_game_a.h"

extern int flag_game_update;

void *joy_reading(void *arg);

#endif /* JOY_READ_H */