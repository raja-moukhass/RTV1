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
#include <stdio.h>
#include <stdlib.h>

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
t_color clamp_color(t_color rgb){
          if (rgb.red > 1.0)
            rgb.red = 1.0;
          if (rgb.green > 1.0)
            rgb.green = 1.0;
          if (rgb.blue > 1.0)
            rgb.blue = 1.0;

            return  rgb;
}
int rgb_to_int(t_color rgb){
  return (((int)(rgb.red*255) << 16) | ((int)(rgb.green*255) << 8) | (int)((rgb.blue*255)));
}
int   cone_intersection(t_ray *ray, t_cone *cone)
{
  double k;
  double a; 
  double b;
  double c;
  double t1;
  double t2;
  k = tan((cone->angle * M_PI / 180.0) / 2);
  t_vector obj_center;
  obj_center = vec_sub(ray->start, cone->position);
  a = dot_product(ray->dir, ray->dir) -(1 + pow(k,2)) *(dot_product(ray->dir, cone->axis) * dot_product(ray->dir, cone->axis));
  b = 2 * (dot_product(ray->dir,obj_center) - (1 + pow(k,2)) * (dot_product(ray->dir, cone->axis) * dot_product(obj_center, cone->axis)));
  c = (dot_product(obj_center,obj_center) - (1 + pow(k,2)) * (dot_product(obj_center, cone->axis) * dot_product(obj_center, cone->axis)));
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


t_ray   get_ray(double u, double v, t_camera *camera)
{
  t_vector   horizontal;
  t_vector   vertical;
  t_vector   cam_u;
  t_vector   cam_v;
  t_vector   cam_w;
  t_ray      new;   
  
  u = 2 * (u + 0.5) / ( WIDTH -1) - 1;
  v = 1 - 2 * (v + 0.5) / ( HEIGHT -1);
  double  half_h;
  double  half_w;
  t_vector cam_pos = camera->look_from;
  cam_pos.z += 0.1;
  new.start = cam_pos;
  half_h =  2.0 * tan((camera->fov * M_PI /180) / 2);
  half_w = half_h;
  cam_w = normalize(vec_sub(cam_pos, camera->cam_dir));
  cam_u = normalize(vec_cross(camera->up, cam_w));
  cam_v = vec_cross(cam_w, cam_u); 
  horizontal = vec_product(cam_u, half_w);
  vertical = vec_product(cam_v, half_h);
  camera->low_left_corner = vec_sub(camera->look_from, cam_w);
  camera->low_left_corner = vec_sub(camera->low_left_corner,vec_product(horizontal, 1/2));
  camera->low_left_corner = vec_sub(camera->low_left_corner,vec_product(vertical, 1/2));
  new.dir = vec_sub(camera->low_left_corner, new.start);
  new.dir = vec_add(new.dir, vec_product(horizontal, u));
  new.dir = vec_add(new.dir, vec_product(vertical, v));
  new.dir = normalize(new.dir);
  return new;
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
    s.pos.z = -60;

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
          t_vector ldir = normalize(vec_sub((t_vector){100,0,-100},s.pos));
          // t_vector refl = normalize(vec_add(ldir, r.dir));
          double dot = dot_product(nr, ldir);
          t_color rgb;
         // printf("%lf", dot);
          rgb = (t_color){1,0,0};
          rgb.red = ((rgb.red) * dot);
          rgb.green = ((rgb.green) * dot);
          rgb.blue = ((rgb.blue) * dot);
           data->d[y*WIDTH + x] =  rgb_to_int(clamp_color(rgb)) ;

        }
        x++;
      }
      y++;
    }
}


void  cone_calculation(t_mlx *data)
{
    int x;
    int y = 0;
    double hit;
    t_sphere s;
    t_cone c;
    //t_cone s;
    t_ray r;

    t_material materials;
    materials.diffuse.red = 1;
    materials.diffuse.green = 0;
    materials.diffuse.blue = 0;
    materials.reflection = 0.2;

    t_light lights;
    lights.pos = (t_vector){20,0,0};

    lights.intensity.red = 1;
    lights.intensity.blue = 1;
    lights.intensity.green =1;

    //double t = 20000.0f;
    c.position.x = 0;
    c.position.y = 0;
    c.position.z = -60;
    c.axis.x = 0;
    c.axis.y = 1;
    c.axis.z = 0;
    c.angle = 60;


    t_camera cam;
    //init camera
    cam.look_from = (t_vector){0, 0, 0};
    cam.cam_dir = (t_vector){0, 0, -1};
    cam.up = (t_vector){0, 1, 0};
    cam.fov = 60;
    while (y < HEIGHT)
    {
      x = 0;
      
      while(x < WIDTH)
      {
        r = get_ray(x, y, &cam);
        hit = cone_intersection(&r,&c);
        if (hit >= 0)
        {
          t_vector hits;
          hits = vec_add(r.start, vec_product((r.dir), hit));
        
          
          t_vector nr = normalize(vec_sub(hits, s.pos));

          if (dot_product(nr, r.dir) > 0)
            nr = vec_product(nr, -1);
          t_vector ldir = normalize(vec_sub((t_vector){10,10,0}, hits));
          //t_vector refl = normalize(vec_add(ldir, r.dir));
          double dot = dot_product(nr, ldir);
          
          t_color rgb;
         // printf("%lf", dot);
          rgb = (t_color){1,1,1};
          rgb.red = ((rgb.red) * dot);
          rgb.green = ((rgb.green) * dot);
          rgb.blue = ((rgb.blue) * dot);
          data->d[y*WIDTH + x] =  rgb_to_int(clamp_color(rgb));

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
  //cone_calculation(data);
  sphere_calculation(data);
  mlx_put_image_to_window(f.ptr, f.win, f.img,0 ,0);
  mlx_loop(f.ptr);
}