#ifndef __GAME_H
#define __GAME_H

#define BACK_DISTANCE 100
#define TRANSITION_LEVEL_DISTANCE  ;

void game_init();

void game_free();

int game_tick();

/**
 * Makes sure the paddle is positionned inside the corridor
*/
void clamp_paddle_position();

#endif
