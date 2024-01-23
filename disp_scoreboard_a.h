/*
 * disp_scoreboard_a.h
 *
 *  Created on: Jan 10, 2024
 *      Author: bauti
 */

#ifndef DISP_SCOREBOARD_A_H_
#define DISP_SCOREBOARD_A_H_

typedef struct {
    char name[50];
    int score;
} player_t;

int display_scoreboard (void);

int display_score_name (void);

#endif /* DISP_SCOREBOARD_A_H_ */
