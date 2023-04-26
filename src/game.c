#include "game.h"
#include "controller.h"
#include <stdio.h>

/**
 * Modifies the ball's velocity vector as if it bounced off a surface with
 * the given normal vector
*/
void static ball_bounce(double norm_x, double norm_y, double norm_z) {
    double dot = game_state.ball.vel_x * norm_x 
        + game_state.ball.vel_y * norm_y 
        + game_state.ball.vel_z * norm_z;
    
    game_state.ball.vel_x -= 2 * norm_x * dot;
    game_state.ball.vel_y -= 2 * norm_y * dot;
    game_state.ball.vel_z -= 2 * norm_z * dot;
}

void static ball_detect_wall_collision() {
    if (game_state.ball.x - BALL_RADIUS < -CORRIDOR_WIDTH / 2) {
        game_state.ball.x = -CORRIDOR_WIDTH / 2 + BALL_RADIUS;
        ball_bounce(1., 0., 0.);
    }
    if (game_state.ball.x + BALL_RADIUS > CORRIDOR_WIDTH / 2) {
        game_state.ball.x = CORRIDOR_WIDTH / 2 - BALL_RADIUS;
        ball_bounce(-1., 0., 0.);
    }
    if (game_state.ball.y - BALL_RADIUS < -CORRIDOR_HEIGHT / 2) {
        game_state.ball.y = -CORRIDOR_HEIGHT / 2 + BALL_RADIUS;
        ball_bounce(0., 1., 0.);
    }
    if (game_state.ball.y + BALL_RADIUS > CORRIDOR_HEIGHT / 2) {
        game_state.ball.y = CORRIDOR_HEIGHT / 2 - BALL_RADIUS;
        ball_bounce(0., -1., 0.);
    }
}

void static ball_tick() {
    game_state.ball.x += game_state.ball.vel_x;
    game_state.ball.y += game_state.ball.vel_y;
    game_state.ball.z += game_state.ball.vel_z;

    ball_detect_wall_collision();
}

void game_init() {
    printf("Game init\n");
    game_state.paddle.x = 0;
    game_state.paddle.y = 0;

    game_state.camera_pos = 0;

    game_state.ball.x = 0;
    game_state.ball.y = 0;
    game_state.ball.z = -10;
    game_state.ball.vel_x = .5;
    game_state.ball.vel_y = .5;
    game_state.ball.vel_z = 0;
}

void game_free() {
    printf("Game free\n");
}

int game_tick() {
    // Test
    game_state.camera_pos += 1. / 5;

    ball_tick();
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