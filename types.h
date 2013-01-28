#ifndef __TYPES_H__
#define __TYPES_H__

/* Color struct */
typedef struct color_struct {
   double r;
   double g;
   double b;
   double f; // "filter" or "alpha"
} color_t;

typedef struct vector3D_struct {
	float x;
	float y;
	float z;
} vector3D;

typedef struct ray_struct {
	vector3D _eye;
	vector3D _dir; 
} ray_t;

typedef struct sphere_struct {
	vector3D _center;
	int _radius;
	color_t _color;
	float _material;
} sphere_t;

#endif
