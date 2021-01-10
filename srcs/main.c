/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv1in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rv1moukhv1 <rv1moukhv1@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:54:06 by ramoukha          #+#    #+#             */
/*   Updated: 2021/01/10 16:45:11 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int intersection_sphere(t_mlx *data)
{
    double a = dot_product(data->ray.dir,data->ray.dir);
    double b = 2 * dot_product(data->ray.dir, vec_sub(data->ray.start, data->sphere->pos));
    double c = dot_product(vec_sub(data->ray.start, data->sphere->pos) , vec_sub(data->ray.start, data->sphere->pos)) - (data->sphere->radius * data->sphere->radius);
    double L = b*b - (4*a*c);
    // printf("\ngood = %lf| bad = %lf",aa,a);
    if (L< 0)
        return 0;
    return 1;

}
int main()
{
  printf("raj");
}