/*
Vector math utility 
*/

#ifndef __UTILITY_H__
#define __UTILITY_H__

// intersection function return values
#define HIT      1		// Ray hit primitive
#define MISS	 0		// Ray missed primitive
#define INPRIM	-1		// Ray started inside primitive

#include <cmath>
#include "types.h"


float getLength(vector3D v) { return (float)std::sqrt( v.x * v.x + v.y * v.y + v.z * v.z ); }
vector3D normalize(vector3D v) { float l = 1.0f / getLength(v); vector3D res = {v.x *= l, v.y *= l, v.z *= l}; return res;}
float dot(vector3D v1, vector3D v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
vector3D cross(vector3D v1, vector3D v2) { vector3D res = { v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x }; return res; }
vector3D operator + ( const vector3D& v1, const vector3D& v2 ) { vector3D res = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }; return res;}
vector3D operator - ( const vector3D& v1, const vector3D& v2 ) { vector3D res = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }; return res;}
vector3D operator * ( const vector3D& v, float f ) { vector3D res = { v.x * f, v.y * f, v.z * f }; return res;}
vector3D operator * ( const vector3D& v1, vector3D& v2 ) { vector3D res = { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z }; return res;}
vector3D operator * ( float f, const vector3D& v ) { vector3D res = { v.x * f, v.y * f, v.z * f }; return res;}
int intersect( sphere_t a_Sphere, vector3D s, vector3D d, float& t_hit );
vector3D getNormal( sphere_t a_Sphere, vector3D a_Intersection );
//test if the ray intersect with any sphere
int intersect(  sphere_t a_Sphere, vector3D s, vector3D d, float& t_hit )
{
	float t1, t2, discrim;
        int retval = MISS;
	discrim = dot((s - a_Sphere._center), d)*dot((s - a_Sphere._center), d) - (dot((s - a_Sphere._center), (s - a_Sphere._center)) - (a_Sphere._radius)*(a_Sphere._radius));
	if (discrim == 0) {
		retval = HIT;
                t_hit = -1 * dot((s - a_Sphere._center), d);
        }
	else {
		if(discrim > 0) {
		   t1 = -dot((s - a_Sphere._center), d) + std::sqrt(discrim);
	           t2 = -dot((s - a_Sphere._center), d) - std::sqrt(discrim);
		   if (t1 > 0 && t2 > 0) {
                           retval = HIT;
			   t_hit = t1 < t2 ? t1:t2;
                   }
		   else {
			   if (t1 > 0 && t2 <= 0) {
                              retval = HIT;
			      t_hit = t1;
                           }
                           else
                              retval = INPRIM;
                   }
		}
	}
        return retval;
}
//get surface noraml
vector3D getNormal( sphere_t a_Sphere, vector3D a_Intersection )
{
	vector3D normal = normalize(a_Intersection - a_Sphere._center);
	return normal;
}

#endif
