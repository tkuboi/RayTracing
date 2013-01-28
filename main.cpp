/*
  Toshihiro Kuboi
  CSC570 Lab 2
  Ray Tracing
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Image.h"
#include "types.h"
#include "utility.h"

int main(void) {

  // make a color
  color_t clr = {0,0,0};
  color_t background = {0,0.5,0.5};
  color_t shadow = {0,0,0};

  // make a 640x480 image (allocates buffer on the heap)
  Image img(640, 480);

  // coordinate of the eye(camera)
  vector3D eye = {320,240,0};
  vector3D up = {1,0,0};
  vector3D screen = {0, 0, 90}; //look

  // coordinate of the light source
  vector3D light = {320,400,-55};

  // create spheres
  sphere_t spheres[] = {
	  {{0,480,1600}, 1200, {1.0,0.1,0.1}, 1.0},
	  {{300,240,600}, 300, {0.1,1.0,0.1}, 1.0},
	  {{400,200,300}, 100, {0.1,0.1,1.0}, 1.0}
  };

  float t_hit, min_t, dl, intensity, att, v_dot, specular;
  vector3D p_hit, normal, l, ln, dir, ref;
  int idx, hit;
  float Ia = 1.0; //ambient
  float Ka = 0.2; //ambient
  float Id = 1.0; //diffuse
  float Kd = 0.9; //diffuse

  // do ray tracing for each pixel
  for (int i=0; i < 640; i++) {
    for (int j=0; j < 480; j++) {
		// setup ray
		screen.x=i;
		screen.y=j;
		dir = normalize(screen - eye);
		min_t = -1;
		idx = -1;
		// get hit time for each sphere
		for (int k=0; k < (sizeof spheres/sizeof(sphere_t)); k++) {
		   // get intersection
		   if (intersect(spheres[k],eye,dir, t_hit) == HIT && 
                       (min_t < 0 || t_hit < min_t)) {
			   min_t = t_hit;
			   idx = k;
		   }
		}
		// if hit, determine color
		if (idx >= 0) {
			// draw pixel
			p_hit = eye + dir * min_t;
			l = light - p_hit;
			dl = getLength(l);
			ln = normalize(l);
			normal = getNormal(spheres[idx], p_hit);
			v_dot = dot(normal,ln);
                        // check to see if it is in shadow
                        for (int k=0; k < (sizeof spheres/sizeof(sphere_t)); k++) {
                           if (k != idx && (hit = intersect(spheres[k],p_hit,ln, t_hit)) == HIT)
                              break;
                        }
			// if the angle between light and surface normal is less than 90 deg
                        // And not in shadow of other objects, then color the pixel
			if (v_dot > 0 && hit != HIT) {
			   //attenuation
			   att = (1/(0+0*dl+1*dl*dl)) < 1 ? (1/(0+0*dl+1*dl*dl)):1;
			   //reflaction
			   ref = 2*normal*v_dot - ln;
			   //specular reflaction
			   specular = std::pow(dot(ref, (-1*dir)),5);
			   //intensity
			   intensity = Ia*Ka+(Id*Kd*v_dot+1.0*specular);
			   clr.r = spheres[idx]._color.r+spheres[idx]._color.r*intensity;
			   clr.g = spheres[idx]._color.g+spheres[idx]._color.g*intensity;
			   clr.b = spheres[idx]._color.b+spheres[idx]._color.b*intensity;
                           img.pixel(i, j, clr);
			}
		}
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"ray.tga", true); 
  // true to scale to max color, false to clamp to 1.0

}
