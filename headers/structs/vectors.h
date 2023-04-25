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
#define sum_Point2D sum_Vec2D
Vec2D mul_Vec2D(Vec2D v, float x);
#define mul_Point2D mul_Vec2D
int equals_Vec2D(Vec2D a, Vec2D b);
#define equals_Point2D equals_Vec2D

/*------ VEC 3D ------ */
Vec3D sum_Vec3D(Vec3D a, Vec3D b);
#define sum_Point3D sum_Vec3D
Vec3D mul_Vec3D(Vec3D v, float x);
#define mul_Point3D mul_Vec3D
int equals_Vec3D(Vec3D a, Vec3D b);
#define equals_Point3D equals_Vec3D

#endif