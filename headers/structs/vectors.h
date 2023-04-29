#ifndef __VECTORS_H__
#define __VECTORS_H__

/* ------ Structs ------*/

typedef struct Vec2D {
    double x, y;
} Vec2D, Point2D;

typedef struct Vec3D {
    double x, y, z;
} Vec3D, Point3D;

/* ------ Functions ------*/

/*------ VEC 2D ------ */
Vec2D sum_Vec2D(Vec2D a, Vec2D b);
#define sum_Point2D sum_Vec2D
Vec2D mul_Vec2D(Vec2D v, double x);
#define mul_Point2D mul_Vec2D
int equals_Vec2D(Vec2D a, Vec2D b);
#define equals_Point2D equals_Vec2D

/*------ VEC 3D ------ */

// Sum
Vec3D sum_Vec3D(Vec3D a, Vec3D b);
#define sum_Point3D sum_Vec3D

// Scalar multiplication
Vec3D mul_Vec3D(Vec3D v, double x);
#define mul_Point3D mul_Vec3D

// Equality
int equals_Vec3D(Vec3D a, Vec3D b);
#define equals_Point3D equals_Vec3D

// Dot product
double dot_Vec3D(Vec3D u, Vec3D v);

// Norm
double norm_Vec3D(Vec3D u);

// Normalized vector
Vec3D normalize_Vec3D(Vec3D u);

// Cross product
Vec3D cross_Vec3D(Vec3D u, Vec3D v);

// Rotates on x axis
Vec3D rotate_x(Vec3D u, double angle);

// Rotates on y axis
Vec3D rotate_y(Vec3D u, double angle);

void print_vec3D(Vec3D v);

void print_vec2D(Vec2D v);

#endif