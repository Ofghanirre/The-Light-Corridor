#include "structs/vectors.h"


/*------ VEC 2D ------ */
Vec2D sum_Vec2D(Vec2D a, Vec2D b) {
    return (Vec2D){a.x + b.x, a.y + b.y};
}

Vec2D mul_Vec2D(Vec2D v, float x) {
    return (Vec2D){v.x * x, v.y * x};
}

int equals_Vec2D(Vec2D a, Vec2D b) {
    return a.x == b.x && a.y == b.y;
}


/*------ VEC 3D ------ */
Vec3D sum_Vec3D(Vec3D a, Vec3D b) {
    return (Vec3D){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3D mul_Vec3D(Vec3D v, float x) {
    return (Vec3D){v.x * x, v.y * x, v.z * x};
}

int equals_Vec3D(Vec3D a, Vec3D b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}