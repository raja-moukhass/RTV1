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

int   cone_intersection(t_object *cone, t_ray *ray)
{
  double k;
  double a; 
  double b;
  double c;
  double t1;
  double t2;

  //printf("x : %.2f\t y : %.2f\t z : %.2f\n", cone->axis.x, cone->axis.y, cone->axis.z);
  k = tan(cone->angle / 2.0);
  t_vector x;
  x = vec_sub(ray->start, cone->pos);
  a = dot_product(ray->dir, ray->dir) - (1 + k * k) * dot_product(ray->dir, cone->axis) * dot_product(ray->dir, cone->axis);
  b = 2 * (dot_product(ray->dir, x) - (1 + k * k) * (dot_product(ray->dir, cone->axis) * dot_product(x, cone->axis)));
  c = dot_product(x, x) - (1 + k * k) * dot_product(x, cone->axis) * dot_product(x, cone->axis);
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

int    sphere_intersection(t_object *s, t_ray *r)
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


t_ray   ft_transform_ray(t_ray ray, t_object *o){
  t_vector rot;
  t_vector trans;

  rot = (t_vector){-o->rot.x, -o->rot.y, -o->rot.z};
  trans = (t_vector){-o->trans.x, -o->trans.y, -o->trans.z};

  ray.start = ft_rotate(ray.start, rot);
  ray.start = ft_translate(ray.start, trans);
  ray.dir = ft_rotate(ray.dir, rot);
  return ray;
}



typedef struct s_delta{
  float a;
  float b;
  float c;
  float delta;
} t_delta;

static int		ft_min_ray(float t1, float t2, float *t)
{
	if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
	{
		*t = t2;
		return (1);
	}
	else
		return (0);
}

int				ft_cone_intersect(t_object *c, t_ray *r, float *t)
{
	t_delta		d;
	t_vector	dist;
	float		anglesin;
	float		anglecos;

	anglecos = pow(cos(c->angle), 2.0);
	anglesin = pow(sin(c->angle), 2.0);
	dist = vec_sub(r->start, c->pos);
	d.a = anglecos * (r->dir.z * r->dir.z + r->dir.x * r->dir.x)
		- anglesin * (r->dir.y * r->dir.y);
	d.b = 2.0 * (anglecos * (dist.z * r->dir.z + dist.x * r->dir.x)
			- anglesin * (dist.y * r->dir.y));
	d.c = anglecos * (dist.z * dist.z + dist.x * dist.x)
		- anglesin * (dist.y * dist.y);
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.00000001)
		return (0);
	d.delta = sqrt(d.delta);
	return (ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
				(-d.b - d.delta) / (2.0 * d.a), t));
}

t_vector ft_object_normal(t_hit *hit, t_ray *ray)
{
  t_vector nr;

  nr = (t_vector){0, 0.0, 0};
  if (hit->o->type == SPHERE){
     nr = vec_sub(hit->p, hit->o->pos);
  }else if (hit->o->type == CONE){
    float m;
    float k = tan((hit->o->angle * M_PI / 180.0) / 2);
   t_vector p = hit->p;
    
	if (p.y > 0)
		p.y = -sqrt(p.z * p.z + p.x * p.x) * tan(hit->o->angle);
	else
		p.y = sqrt(p.z * p.z + p.x * p.x) * tan(hit->o->angle);

    nr = (t_vector){p.x, 0.01, p.z};
   /* t_vector x = vec_sub(ray->start, hit->o->pos);
    m = dot_product(ray->dir, hit->o->axis) * hit->t + dot_product(x, hit->o->axis);
    nr = vec_sub(vec_sub(hit->p, hit->o->pos), vec_product(hit->o->axis, (1 + k * k) * m));*/

  }else{
    ft_putendl("Wrong");
  }
  return normalize(nr);
}

void ft_scene_init(t_mlx *data)
{
  t_object sphere;
  t_object cone;


  sphere = ft_create_sphere((t_vector){0, 0, 0},
  (t_vector){0, 12, 0},
  (t_vector){0, 0, 0},
  1.0,
  (t_color){1.0, 0.0, 0.0}
  );

   cone = ft_create_cone((t_vector){0, 0, 0},
  (t_vector){0, 0, 0},
  (t_vector){0, 0, 90},
  (t_vector){0, 1, 0},
  45,
  (t_color){1.0, 1.0, 1.0}
  );
    data->cam.look_from = (t_vector){0, 0, 5};
    data->cam.cam_dir = (t_vector){0, 0, -1};
    data->cam.up = (t_vector){0, 1, 0};
    data->cam.fov = 60;
    data->objects = NULL;
   //ft_add_object(&data->objects, ft_create_object(sphere));
   ft_add_object(&data->objects, ft_create_object(cone));
}

int ft_intersect_scene_objects(t_object *lst, t_hit *hit,  t_ray *ray){
  t_object *p;
  float t;

  p=lst;
  t = INFINITY;
  hit->t = INFINITY;
  hit->o = NULL;
  while (p)
  {
    *ray = ft_transform_ray(*ray, p);
    if (p->type == SPHERE){
      t = sphere_intersection(p, ray);
    }
    else if (p->type == CONE){
     // t = cone_intersection(p, ray);
     ft_cone_intersect(p, ray,&t);
    }
    if (t > 0 && t < hit->t){
      hit->t = t;
      hit->o = p;
    }
    p = p->next;
  }

  if (hit->o){
    hit->p = vec_add(ray->start, vec_product(ray->dir, hit->t));
    hit->n = ft_object_normal(hit, ray);
    return 1;
  }
  return 0;
}

t_color ft_shade(t_hit *hit, t_ray *ray){
  t_color rgb;
  (void)ray;

  rgb = (t_color){0, 0, 0};
  t_vector ldir = normalize(vec_sub((t_vector){10,0, 15}, hit->p));
  double dot = dot_product(hit->n, ldir);
  if (dot > 0)
  {
    rgb = hit->o->color;
    rgb.red = ((rgb.red) * dot);
    rgb.green = ((rgb.green) * dot);
    rgb.blue = ((rgb.blue) * dot);
  }
  return rgb;
}

void ft_raytrace(t_mlx *data){
    int x;
    int y;
    t_hit hit;
    t_ray ray;
    t_color color;

    y =-1;
    while (++y < HEIGHT)
    {
      x = -1;
      while(++x < WIDTH)
      {
        ray = get_ray(x, y, &data->cam);
        if (ft_intersect_scene_objects(data->objects, &hit,  &ray)){
          color = ft_shade(&hit, &ray);          
           data->d[y*WIDTH + x] =  rgb_to_int(clamp_color(color)) ;
        }
      }
    }
}


int main()
{
  t_mlx *data;
  int bpp;
  t_sphere *sphere;
  sphere = (t_sphere *)malloc(sizeof(t_sphere));
  data = (t_mlx *)malloc(sizeof(t_mlx));
  ft_scene_init(data);
  t_mlx f;
  f.ptr = mlx_init();
  f.win = mlx_new_window(f.ptr, WIDTH, HEIGHT, "RTV1");
  mlx_hook(f.win,17,0,ft_close,&data);
  mlx_hook(f.win, 2,0,keyhook,data);
  f.img = mlx_new_image(f.ptr,WIDTH,HEIGHT);
  f.d   = (int *)mlx_get_data_addr(f.img, &bpp, &bpp, &bpp);
  data->d = f.d; 
  ft_raytrace(data);
  mlx_put_image_to_window(f.ptr, f.win, f.img,0 ,0);
  mlx_loop(f.ptr);
}