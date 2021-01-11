/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv1in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rv1moukhv1 <rv1moukhv1@student.42.fr>          +#+  +:+       +#+    */
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



int    intersection(t_ray *r,t_sphere *s)
{
  double a = dot_product(r->dir, r->dir);

  t_vector dist = vec_sub(r->start,s->pos);
  //printf("(%lf, %lf, %lf)\n", dist.x, dist.y, dist.z);
  double b = 2 * dot_product(r->dir, dist);
  double c = dot_product(dist, dist) - (s->radius * s->radius);
  //printf("\na = %lf b = %lf c = %lf", a,b,c);
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
    t_ray r;
    s.pos.x = 0;
    s.pos.y = 0;
    s.pos.z = -40;
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
      r.dir.y = y-(WIDTH/2);
      x = 0;
      
      while(x < WIDTH)
      {
        r.dir.x = x-(WIDTH/2);
        r.dir.z =  -WIDTH/(2*tan(alpha));
        hit = intersection(&r,&s);
        if (hit)

        {
          data->d[y*WIDTH + x] = 0xffffff;
          //data->d[y*WIDTH + x] = (int)(r.dir.y * 350) << 16;

        }
        x++;
      }
      y++;
    }
}


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