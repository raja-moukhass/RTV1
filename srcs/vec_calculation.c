
#include "rtv1.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double    ft_slution(double a, double b, double c)
{
  double det;
  t_vector sol;

  det = b * b - 4 * a * c;
  if (det < 0.0001)
  return(-1);
  sol.x = (-b + sqrt(det) / (2 * a));
  sol.y = (-b - sqrt(det) / (2 * a));
  sol.z = ((sol.x < sol.y && sol.x > 0) ? sol.x : sol.y);
	if (sol.z < 0)
  sol.z = 0;
	return (sol.z);
}

t_vector  vec_cross(t_vector v1, t_vector v2)
{
  t_vector c;
  c.x = v1.y * v2.z - v2.y * v1.z;
  c.y = v1.z * v2.x - v2.z * v1.x;
  c.z = v1.x * v2.y - v2.x * v1.y;
  return (c);
}

t_vector  normalize(t_vector vec)
{
  double mod;
  
  mod = sqrtf(powf(vec.x, 2) + powf(vec.y,2) + powf(vec.z, 2));
  vec.x /= mod;
  vec.y /= mod;
  vec.z /= mod;
  return (vec);
}

t_vector    normal_sphere(double t, t_ray r, t_sphere s)
{
  t_vector  hit;
  t_vector  n;

  hit = vec_add(r.start, vec_product(normalize(r.dir), t));
  n.x = hit.x - s.pos.x;
  n.y = hit.y - s.pos.y;
  n.z = hit.z - s.pos.z;
  return (normalize(n));
}

t_vector  vec_add(t_vector v1, t_vector v2)
{
  t_vector c;
  c.x = v1.x + v2.x;
	c.y = v1.y + v2.y;
	c.z = v1.z + v2.z;
	return (c);
}

t_vector  vec_sub(t_vector v1, t_vector v2)
{
  t_vector c;
  c.x = v1.x - v2.x;
  c.y = v1.y - v2.y;
  c.z = v1.z - v2.z;
  return (c);
}

t_vector  vec_product(t_vector v, double i)
{
  t_vector c;
  c.x = v.x * i;
  c.y = v.y * i;
  c.z = v.z * i;
  return(c);
}
double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
void  position(t_material materials,t_light lights,t_cone c,t_camera cam)
{
  materials.diffuse.red = 1;
  materials.diffuse.green = 0;
  materials.diffuse.blue = 0;
  materials.reflection = 0.2;
  lights.pos = (t_vector){20,0,0};

  lights.intensity.red = 1;
  lights.intensity.blue = 1;
  lights.intensity.green =1;
  c.position.x = 0;
  c.position.y = 0;
  c.position.z = -60;
  c.axis.x = 0;
  c.axis.y = 1;
    c.axis.z = 0;
    c.angle = 60;
     cam.look_from = (t_vector){0, 0, 0};
    cam.cam_dir = (t_vector){0, 0, -1};
    cam.up = (t_vector){0, 1, 0};
    cam.fov = 60;

}
