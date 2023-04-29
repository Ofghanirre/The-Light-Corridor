#include "structs/vectors.h"
#include <math.h>
#include <stdio.h>


/*------ VEC 2D ------ */
Vec2D sum_Vec2D(Vec2D a, Vec2D b) {
    return (Vec2D){a.x + b.x, a.y + b.y};
}

Vec2D mul_Vec2D(Vec2D v, double x) {
    return (Vec2D){v.x * x, v.y * x};
}

int equals_Vec2D(Vec2D a, Vec2D b) {
    return a.x == b.x && a.y == b.y;
}


/*------ VEC 3D ------ */
Vec3D sum_Vec3D(Vec3D a, Vec3D b) {
    return (Vec3D){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3D mul_Vec3D(Vec3D v, double x) {
    return (Vec3D){v.x * x, v.y * x, v.z * x};
}

int equals_Vec3D(Vec3D a, Vec3D b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

double dot_Vec3D(Vec3D u, Vec3D v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

double norm_Vec3D(Vec3D u) {
    return sqrt(dot_Vec3D(u, u));
}

Vec3D normalize_Vec3D(Vec3D u) {
    return mul_Vec3D(u, 1. / norm_Vec3D(u));
}

Vec3D cross_Vec3D(Vec3D u, Vec3D v) {
    return (Vec3D){u.y * v.z - v.y * u.z, v.x * u.z - u.x * v.z, u.x * v.y - v.x * u.y};
}

Vec3D rotate_x(Vec3D u, double angle) {
    return (Vec3D){u.x, u.y * cos(angle) - sin(angle) * u.z, sin(angle) * u.y + cos(angle) * u.z};
}

Vec3D rotate_y(Vec3D u, double angle) {
    return (Vec3D){cos(angle) * u.x + sin(angle) * u.z, u.y, -sin(angle) * u.x + cos(angle) * u.z};
}

void print_vec3D(Vec3D v) {
    printf("vec3D{%f, %f, %f}", v.x, v.y, v.z);
}

void print_vec2D(Vec2D v) {
    printf("vec2D{%f, %f}", v.x, v.y);
}