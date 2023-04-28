#include "game.h"
#include "controller.h"
#include "structs/vectors.h"
#include "scenery.h"
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.141
#endif

/**
 * Modifies the ball's velocity vector as if it bounced off a surface with
 * the given normal vector
*/
void static ball_bounce(Vec3D normal) {
    double dot = dot_Vec3D(game_state.ball.direction, normal);
    game_state.ball.direction = normalize_Vec3D(sum_Vec3D(game_state.ball.direction, mul_Vec3D(normal, -2 * dot)));
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
    // We only consider paddle collision is the ball is heading towards it
    //if (game_state.ball.direction.z < 0) { return 0;}

    // The ball is still too far from the paddle
    if (game_state.ball.position.z + BALL_RADIUS <= 0 + game_state.camera_pos) {
        return 0;
    }

    // We ball passed the paddle
    if (game_state.ball.position.z > 0 + game_state.camera_pos) {
        return 1;
    }
    
    if (game_state.ball.position.x > game_state.paddle.position.x - PADDLE_WIDTH / 2 - BALL_RADIUS / 2
        && game_state.ball.position.x < game_state.paddle.position.x + PADDLE_WIDTH / 2 + BALL_RADIUS / 2
        && game_state.ball.position.y > game_state.paddle.position.y - PADDLE_WIDTH / 2 - BALL_RADIUS / 2
        && game_state.ball.position.y < game_state.paddle.position.y + PADDLE_WIDTH / 2 + BALL_RADIUS / 2) {
            Vec3D point_impact = (Vec3D){game_state.ball.position.x, game_state.ball.position.y, 0};
            Vec3D center = (Vec3D){game_state.paddle.position.x, game_state.paddle.position.y, 0};
            Vec3D impact = sum_Vec3D(point_impact, mul_Vec3D(center, -1));

            double max_angle = M_PI / 4;
            double x_theta = impact.x / (PADDLE_WIDTH / 2) * max_angle;
            double y_theta = impact.y / (PADDLE_HEIGHT / 2) * max_angle;

            Vec3D base_direction = (Vec3D){0., 0., -1.};

            game_state.ball.direction = rotate_x(rotate_y(base_direction, -x_theta), y_theta);
            game_state.ball.position.z = PADDLE_Z - BALL_RADIUS - 0.5 + game_state.camera_pos;

            if (game_state.glue_enabled) {
                game_state.ball.glued = 1;
                game_state.ball.glued_offset.x = game_state.ball.position.x - game_state.paddle.position.x;
                game_state.ball.glued_offset.y = game_state.ball.position.y - game_state.paddle.position.y;
            }
        }
    return 0;
}

// Temp, there won't actually be a back wall in the actual game
void static ball_detect_back() {
    if (game_state.ball.position.z < game_state.camera_pos - 50) {
        ball_bounce((Vec3D){0., 0., 1.});
    }
}

void static ball_tick() {
    if (game_state.ball.glued != 0) {
        game_state.ball.position.x = game_state.paddle.position.x + game_state.ball.glued_offset.x;
        game_state.ball.position.y = game_state.paddle.position.y + game_state.ball.glued_offset.y;
        game_state.ball.position.z = game_state.camera_pos - PADDLE_Z - BALL_RADIUS;
        return;
    }

    game_state.ball.position = sum_Vec3D(game_state.ball.position, mul_Vec3D(game_state.ball.direction, game_state.ball.speed));
    ball_detect_wall_collision();
    ball_detect_back();
    int lost_ball = ball_detect_paddle_collision();
    
    if (lost_ball) {
        printf("You lost the ball!\n");
        game_state.camera_pos = 0;

        game_state.ball.glued = 1;
        game_state.ball.direction = (Vec3D){0., 0., -1.};
    }
}

void game_init() {
    printf("Game init\n");
    game_state.paddle.position = (Vec2D){0., 0.};

    game_state.camera_pos = 0;
    game_state.moving_forward = 0;

    game_state.ball.position = (Vec3D){0., 0., -BALL_RADIUS};
    game_state.ball.direction = (Vec3D){0, 0, -1};
    game_state.ball.speed = 1.;
    game_state.ball.glued = 1;
    game_state.ball.glued_offset = (Vec2D){0., 0.};
    
    game_state.glue_enabled = 0;

    
}

void game_free() {
    printf("Game free\n");
}

int game_tick() {
    ball_tick();

    if (game_state.moving_forward && !game_state.ball.glued) {
        game_state.camera_pos -= 0.5;
    }
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