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
  double t1;
  double t2;

  t_vector dist = vec_sub(r->start,s->pos);
  //printf("(%lf, %lf, %lf)\n", dist.x, dist.y, dist.z);
  double b = 2 * dot_product(r->dir, dist);
  double c = dot_product(dist, dist) - (s->radius * s->radius);
  //printf("\na = %lf b = %lf c = %lf", a,b,c);
  double discr = b * b - 4 * a * c;
  if(discr < 0)
  return -1;
  else {
    t1 = (-b - sqrtf(discr)) / 2 * a;
    t2 = (-b + sqrtf(discr)) / 2 * a;
  }
  if (t1 > 0 && t1 < t2)
    return (t1);
  else if (t2 > 0)
      return (t2);
  return -1;

}
void  sphere_calculation(t_mlx *data)
{
    int x;
    int y;
    int hit;
    t_sphere s;
    t_ray r;

    t_material materials;
    materials.diffuse.red = 1;
    materials.diffuse.green = 0;
    materials.diffuse.blue = 0;
    materials.reflection = 0.2;

    t_light lights;
    lights.pos.x = 0;
    lights.pos.y = 0;
    lights.pos.z = -100;

    lights.intensity.red = 1;
    lights.intensity.blue = 1;
    lights.intensity.green =1;

    //double t = 20000.0f;
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
        if (hit >= 0)
        {
          t_vector hits;
          hits = vec_add(r.start, vec_product(normalize(r.dir), hit));
        
          
          t_vector nr = normalize(vec_sub(hits, s.pos));
          t_vector ldir = normalize(vec_sub((t_vector){0,0,-100},(t_vector){0,0,-40}));
          // t_vector refl = normalize(vec_add(ldir, r.dir));
          double dot = dot_product(nr, ldir);
          t_color rgb;
         // printf("%lf", dot);
          rgb = (t_color){1,1,1};
          rgb.red = ((rgb.red) * dot);
          rgb.green = ((rgb.green) * dot);
          rgb.blue = ((rgb.blue) * dot);
          if (rgb.red > 1.0)
            rgb.red = 1.0;
          if (rgb.green > 1.0)
            rgb.green = 1.0;
          if (rgb.blue > 1.0)
            rgb.blue = 1.0;
          int color = (((int)(rgb.red*255) << 16) | ((int)(rgb.green*255) << 8) | (int)((rgb.blue*255)));
          if (dot >= 0)
          {
            data->d[y*WIDTH + x] = color;
          }
          //data->d[y*WIDTH + x] = 0xff;

        }
        x++;
      }
      y++;
    }
}

t_vector normal_sphere(double t, t_ray r, t_sphere s)
{
  t_vector hit;
  t_vector n;

  hit = vec_add(r.start, vec_product(normalize(r.dir), t));
  n.x = hit.x - s.pos.x;
  n.y = hit.y - s.pos.y;
  n.z = hit.z - s.pos.z;
  return (normalize(n));
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

int main()
{
  t_mlx *data;
  int bpp;
   t_sphere *sphere;
  sphere = (t_sphere *)malloc(sizeof(t_sphere));

   data = (t_mlx *)malloc(sizeof(t_mlx));
   data->sphere = sphere;
  
  t_mlx f;
  f.ptr = mlx_init();
  f.win = mlx_new_window(f.ptr, WIDTH, HEIGHT, "RTV1");
  mlx_hook(f.win,17,0,ft_close,&data);
  mlx_hook(f.win, 2,0,keyhook,data);
  f.img = mlx_new_image(f.ptr,WIDTH,HEIGHT);
  f.d   = (int *)mlx_get_data_addr(f.img, &bpp, &bpp, &bpp);
  data->d = f.d; 
  sphere_calculation(data);
  mlx_put_image_to_window(f.ptr, f.win, f.img,0,0);
  mlx_loop(f.ptr);

}