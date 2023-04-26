#include "game.h"
#include "controller.h"
#include <stdio.h>

void game_init() {
    printf("Game init\n");
    game_state.paddle.x = 0;
    game_state.paddle.y = 0;
    game_state.camera_pos = 0;
    game_state.ball.x = 0;
    game_state.ball.y = 0;
    game_state.ball.z = -10;
}

void game_free() {
    printf("Game free\n");
}

int game_tick() {
    // Test
    game_state.camera_pos += 1. / 5;
    return 0;
}

void clamp_paddle_position() {
    if (game_state.paddle.x - PADDLE_WIDTH / 2 < -CORRIDOR_WIDTH / 2) {
        game_state.paddle.x = -CORRIDOR_WIDTH / 2 + PADDLE_WIDTH / 2;
    }
    if (game_state.paddle.x + PADDLE_WIDTH / 2 > CORRIDOR_WIDTH / 2) {
        game_state.paddle.x = CORRIDOR_WIDTH / 2 - PADDLE_WIDTH / 2;
    }
    if (game_state.paddle.y - PADDLE_HEIGHT / 2 < -CORRIDOR_HEIGHT / 2) {
        game_state.paddle.y = -CORRIDOR_HEIGHT / 2 + PADDLE_HEIGHT / 2;
    }
    if (game_state.paddle.y + PADDLE_HEIGHT / 2 > CORRIDOR_HEIGHT / 2) {
        game_state.paddle.y = CORRIDOR_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    }
}