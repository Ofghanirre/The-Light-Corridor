#include "structs/vectors.h"
#include <math.h>

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

double norm_vec3D(Vec3D u) {
    return sqrt(dot_Vec3D(u, u));
}

Vec3D normalize_Vec3D(Vec3D u) {
    return mul_Vec3D(u, 1. / norm_vec3D(u));
}