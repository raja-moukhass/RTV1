/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:54:06 by ramoukha          #+#    #+#             */
/*   Updated: 2021/01/08 18:33:45 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int			ft_close(void)
{
	exit(1);
	return (0);
}

int   keyhook(int key, void *p)
{
  (void)p;
  if (key == 53)
    ft_close();
    return (0);
}


float   vectorsub(t_vector *v1, t_vector *v2)
{
	float result = (v1->x - v2->x) + (v1->y - v2->y) + (v1->z - v2->z);
	return(result);
}
float vectordot(t_vector *v1, t_vector *v2)
{
  double result = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return result;
}

bool    intersect_ray(t_ray *r, t_sphere *s)
{
    float a;
    a =  vectordot(&r->dir , &r->dir); // the vector dot product of the direction 

  // vector representing the distence between the start and the position of the circle (p0 - c)

  float dist;
  dist = vectorsub(&r->start, &s->pos);
  float b;
  b = 2 * vectordot(&r->dir, &dist);
  float c ;
  c = vectordot(&dist, &dist) - (s->radius * s->radius);
  // solving the discriminant 
  float discr = b*b - 4 * a *c; // if the descr // 
                                                    
  if(discr < 0)
  return false;
  else 
  return true;
  
}




int main()
{
  t_mlx f;
  void *data;
  
  f.ptr = mlx_init();
  f.win = mlx_new_window(f.ptr, 500, 500, "Title");
  mlx_hook(f.win,17,0,ft_close,&data);
  mlx_hook(f.win, 2,0,keyhook,data);
  mlx_loop(f.ptr);
  
  return (0);
}