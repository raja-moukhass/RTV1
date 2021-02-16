
#include "rtv1.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double    ft_slution(double a, double b, double c)
{
  double det;
  t_vec sol;

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

t_vec  vec_cross(t_vec v1, t_vec v2)
{
  t_vec c;
  c.x = v1.y * v2.z - v2.y * v1.z;
  c.y = v1.z * v2.x - v2.z * v1.x;
  c.z = v1.x * v2.y - v2.x * v1.y;
  return (c);
}

t_vec  vec_add(t_vec v1, t_vec v2)
{
  t_vec c;
  c.x = v1.x + v2.x;
	c.y = v1.y + v2.y;
	c.z = v1.z + v2.z;
	return (c);
}

// t_vec  vec_sub(t_vec v1, t_vec v2)
// {
//   t_vec c;
//   c.x = v1.x - v2.x;
//   c.y = v1.y - v2.y;
//   c.z = v1.z - v2.z;
//   return (c);
// }
t_vec  vec_sub(t_vec A, t_vec B)
{
    t_vec ret = {(A.x - B.x) , (A.y - B.y) , (A.z - B.z)};
    return (ret);
}
t_vec  vec_product(t_vec v, double i)
{
  t_vec c;
  c.x = v.x * i;
  c.y = v.y * i;
  c.z = v.z * i;
  return(c);
}
double	dot_product(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}