#include "game.h"
#include "controller.h"
#include "structs/vectors.h"
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
            Vec3D base_normal = (Vec3D){0., 0., -1.};
            Vec3D point_impact = (Vec3D){game_state.ball.position.x, game_state.ball.position.y, 0};
            Vec3D center = (Vec3D){game_state.paddle.position.x, game_state.paddle.position.y, 0};
            Vec3D impact_dir = normalize_Vec3D(sum_Vec3D(point_impact, mul_Vec3D(center, -1)));

            double theta = acos(dot_Vec3D(impact_dir, base_normal));
            Vec3D axis = normalize_Vec3D(cross_vec3D(base_normal, impact_dir));

            double angle_factor = sin(theta) * 2;
            double rotation_angle = angle_factor * M_PI / 2;

            // Calculate rotation
            Vec3D normal = base_normal;

            printf("Calculated normal: %f, %f, %f\n", normal.x, normal.y, normal.z);
            ball_bounce(normal);
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