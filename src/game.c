#include "game.h"
#include "controller.h"
#include "structs/vectors.h"
#include <stdio.h>

/**
 * Modifies the ball's velocity vector as if it bounced off a surface with
 * the given normal vector
*/
void static ball_bounce(Vec3D normal) {
    double dot = dot_Vec3D(game_state.ball.velocity, normal);
    game_state.ball.velocity = sum_Vec3D(game_state.ball.velocity, mul_Vec3D(normal, -2 * dot));
}

void static ball_detect_wall_collision() {
    if (game_state.ball.position.x - BALL_RADIUS < -CORRIDOR_WIDTH / 2) {
        game_state.ball.position.x = -CORRIDOR_WIDTH / 2 + BALL_RADIUS;
        ball_bounce((Vec3D){1., 0., 0.});
    }
    if (game_state.ball.position.x + BALL_RADIUS > CORRIDOR_WIDTH / 2) {
        game_state.ball.position.x = CORRIDOR_WIDTH / 2 - BALL_RADIUS;
        ball_bounce((Vec3D){-1., 0., 0.});
    }
    if (game_state.ball.position.y - BALL_RADIUS < -CORRIDOR_HEIGHT / 2) {
        game_state.ball.position.y = -CORRIDOR_HEIGHT / 2 + BALL_RADIUS;
        ball_bounce((Vec3D){0., 1., 0.});
    }
    if (game_state.ball.position.y + BALL_RADIUS > CORRIDOR_HEIGHT / 2) {
        game_state.ball.position.y = CORRIDOR_HEIGHT / 2 - BALL_RADIUS;
        ball_bounce((Vec3D){0., -1., 0.});
    }
}

// Returns 1 if the ball failed to be caught
int static ball_detect_paddle_collision() {
    if (game_state.ball.position.z + BALL_RADIUS <= 0) {
        return 0;
    }
    if (game_state.ball.position.z > 0) {
        return 1;
    }
    
    if (game_state.ball.position.x > game_state.paddle.position.x - PADDLE_WIDTH / 2 - BALL_RADIUS / 2
        && game_state.ball.position.x < game_state.paddle.position.x + PADDLE_WIDTH / 2 + BALL_RADIUS / 2
        && game_state.ball.position.y > game_state.paddle.position.y - PADDLE_WIDTH / 2 - BALL_RADIUS / 2
        && game_state.ball.position.y < game_state.paddle.position.y + PADDLE_WIDTH / 2 + BALL_RADIUS / 2) {
            ball_bounce((Vec3D){0., 0., -1.});
        }
    return 0;
}

// Temp, there won't actually be a back wall in the actual game
void static ball_detect_back() {
    if (game_state.ball.position.z < -100) {
        ball_bounce((Vec3D){0., 0., 1.});
    }
}

void static ball_tick() {
    game_state.ball.position = sum_Vec3D(game_state.ball.position, game_state.ball.velocity);
    ball_detect_wall_collision();
    ball_detect_back();
    int lost_ball = ball_detect_paddle_collision();
    
    if (lost_ball) {
        printf("You lost the ball!\n");
        game_state.camera_pos = 0;

        game_state.ball.position = (Vec3D){0., 0., -10.};
        game_state.ball.velocity = (Vec3D){-0.5, -0.5, -1.};
    }
}

void game_init() {
    printf("Game init\n");
    game_state.paddle.position = (Vec2D){0., 0.};

    game_state.camera_pos = 0;

    game_state.ball.position = (Vec3D){0., 0., -10.};
    game_state.ball.velocity = (Vec3D){-0.5, -0.5, -1.};
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
    if (game_state.paddle.position.x - PADDLE_WIDTH / 2 < -CORRIDOR_WIDTH / 2) {
        game_state.paddle.position.x = -CORRIDOR_WIDTH / 2 + PADDLE_WIDTH / 2;
    }
    if (game_state.paddle.position.x + PADDLE_WIDTH / 2 > CORRIDOR_WIDTH / 2) {
        game_state.paddle.position.x = CORRIDOR_WIDTH / 2 - PADDLE_WIDTH / 2;
    }
    if (game_state.paddle.position.y - PADDLE_HEIGHT / 2 < -CORRIDOR_HEIGHT / 2) {
        game_state.paddle.position.y = -CORRIDOR_HEIGHT / 2 + PADDLE_HEIGHT / 2;
    }
    if (game_state.paddle.position.y + PADDLE_HEIGHT / 2 > CORRIDOR_HEIGHT / 2) {
        game_state.paddle.position.y = CORRIDOR_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    }
}