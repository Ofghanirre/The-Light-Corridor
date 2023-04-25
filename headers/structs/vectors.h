#ifndef __VECTORS_H__
#define __VECTORS_H__

typedef struct Vec2D {
    float x, y;
} Vec2D, Point2D;

typedef struct Vec3D {
    float x, y, z;
} Vec3D, Point3D;

/*------ VEC 2D ------ */
Vec2D sum_Vec2D(Vec2D a, Vec2D b);
Vec2D mul_Vec2D(Vec2D v, float x);
int equals_Vec2D(Vec2D a, Vec2D b);

/*------ VEC 3D ------ */
Vec3D sum_Vec3D(Vec3D a, Vec3D b);
Vec3D mul_Vec3D(Vec3D v, float x);
int equals_Vec3D(Vec3D a, Vec3D b);
#endif