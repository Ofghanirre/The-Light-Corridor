#ifndef __GAME_H
#define __GAME_H

#define BACK_DISTANCE 100
#define TRANSITION_LEVEL_DISTANCE 60
#define TIMELESS_GLUE -1
#define GLUE_TICK_BONUS_DURATION 100
void game_init();

void game_free();

int game_tick();

/**
 * Makes sure the paddle is positionned inside the corridor
*/
void clamp_paddle_position();

void game_start();

void game_end();

#endif
