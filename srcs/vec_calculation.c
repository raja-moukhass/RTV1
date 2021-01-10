

#include "rtv1.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
t_vector  vec_cross(t_vector v1, t_vector v2)
{
  t_vector c;
  c.x = v1.y * v2.z - v2.y * v1.z;
  c.y = v1.z * v2.x - v2.z * v1.x;
  c.z = v1.x * v2.y - v2.x * v1.y;
  return (c);
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