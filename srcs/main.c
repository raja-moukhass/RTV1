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

// double    ft_slution(double a, double b, double c)
// {
//   double det;
//   t_vector sol;

//   det = b * b - 4 * a * c;
//   if (det < 0.0001)
//   return(-1);
//   sol.x = (-b + sqrt(det) / (2 * a));
//   sol.y = (-b - sqrt(det) / (2 * a));
//   sol.z = ((sol.x < sol.y && sol.x > 0) ? sol.x : sol.y);
// 	if (sol.z < 0)
// 		sol.z = 0;
// 	return (sol.z);

// }
// int intersection_sphere(t_mlx *data)
// {
//     double a =  dot_product(data->ray.dir,data->ray.dir);
//     double b = 2 * dot_product(data->ray.dir, vec_sub(data->ray.start, data->sphere->pos));
//     double c = dot_product(vec_sub(data->ray.start, data->sphere->pos) , vec_sub(data->ray.start, data->sphere->pos)) - (data->sphere->radius * data->sphere->radius);
//     double L = b*b - (4*a*c);
//     // printf("\ngood = %lf| bad = %lf",aa,a);
//     if (L< 0)
//         return 0;
//     return 1;
// }
int    intersection(t_ray *r,t_sphere *s)
{
  double a = dot_product(r->dir, r->dir);
  // printf("direction vect: (%lf, %lf, %lf)\n", r->dir.x, r->dir.y, r->dir.z);
  // printf("product: %lf\n", a);
  t_vector dist = vec_sub(r->start,s->pos);
  //printf("(%lf, %lf, %lf)\n", dist.x, dist.y, dist.z);
  double b = 2 * dot_product(r->dir, dist);
  double c = dot_product(dist, dist) - (s->radius * s->radius);
  double discr = b * b - 4 * a * c;
  if(discr < 0)
  return 0;
  else 
  return 1;

}
void  sphere_calculation(t_mlx *data)
{
    int x;
    int y;
    int hit;
    t_sphere s;
    t_ray r;git 
    s.pos.x = 50;
    s.pos.y = 50;
    s.pos.z = -50;
    r.start.x = 0;
    r.start.y = 0;
    r.start.z = 0;
    s.radius = 30;
  double  PI = 22 / 7;
  double alpha = 60 * PI/180;
    r.dir.x = 0;
    r.dir.y = 0;
    r.dir.z = 1;

    r.start.z = 0;
    y =0;
    while (y < HEIGHT)
    {
      r.dir.y = y;
      x = 0;
      
      while(x < WIDTH)
      {
        r.dir.x = x;
        r.dir.z =  -WIDTH/(2*tan(alpha));
        hit = intersection(&r,&s);
        // printf("%d",hit);
        if (hit)

        {

              data->d[y*WIDTH + x] = 0xffffff;
//ft_putstr("CHECK");

        }
        x++;
      }
      y++;
    }
}
//   int y;
//   int x;
//   double  PI = 22 / 7;
//   double alpha = 60 * PI/180;
//   y = 0;
//   while (y < HEIGHT)
//   {
//     x = -1;
//     while(x++ <WIDTH)
//     {
//       data->ray.dir.x = x-(HEIGHT/2);
//       data->ray.dir.y = y-(HEIGHT/2);
//       data->ray.dir.z = -WIDTH/(2*tan(alpha));
//       if(intersection_sphere(data))
//       data->d[y*WIDTH + x] = 0xffffff;
//     }
//     y++;
//   }
//}


int main()
{
  t_mlx *data;
  int bpp;
  // t_vector origin = {0,0,0};
  // t_vector s = {50,50,-200};
   t_sphere *sphere;
  sphere = (t_sphere *)malloc(sizeof(t_sphere));
  // sphere->pos =s;
  // sphere->radius = 10;
   data = (t_mlx *)malloc(sizeof(t_mlx));
   data->sphere = sphere;
  
  t_mlx f;
  f.ptr = mlx_init();
  f.win = mlx_new_window(f.ptr, WIDTH, HEIGHT, "RTV1");
  mlx_hook(f.win,17,0,ft_close,&data);
  mlx_hook(f.win, 2,0,keyhook,data);
  //printf("raja");

  f.img = mlx_new_image(f.ptr,WIDTH,HEIGHT);
  f.d   = (int *)mlx_get_data_addr(f.img, &bpp, &bpp, &bpp);
  //printf("raja");
  data->d = f.d; 
  sphere_calculation(data);

  mlx_put_image_to_window(f.ptr, f.win, f.img,0,0);
  mlx_loop(f.ptr);

}