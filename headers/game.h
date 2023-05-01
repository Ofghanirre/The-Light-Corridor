#ifndef __GAME_H
#define __GAME_H

#define BACK_DISTANCE 150
#define TRANSITION_LEVEL_DISTANCE 60
#define TIMELESS_GLUE -1
#define GLUE_TICK_BONUS_DURATION 100
#define PADDLE_SPEED 1.

/**
 * Initializes the game
*/
void game_init();

/**
 * Freeds the data used by the game
*/
void game_free();

/**
 * Processes a tick from the game
*/
int game_tick();

/**
 * Starts a game
*/
void game_start();

/**
 * Ends a game
*/
void game_end();

/**
 * Puts the game back into its initial state
*/
void game_restart();

#endif
