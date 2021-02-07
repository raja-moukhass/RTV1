/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:06:46 by ramoukha          #+#    #+#             */
/*   Updated: 2021/02/07 10:35:08 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "math.h"
# include "pthread.h"
#include "../miniLibX/mlx.h"
# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_vector
{
	double x;
	double y;
	double z;
}t_vector;

typedef struct s_cone 
{
	t_vector position;
	t_vector axis;
	double angle;
}t_cone;

typedef struct s_sphere
{
	t_vector pos;
	double radius;
	
}t_sphere;

typedef struct s_ray
{
	t_vector start;
	t_vector dir;
	
}t_ray;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	void		*img_ptr;
	int 		pxl;
	t_ray 		ray;
	t_sphere	*sphere;
	int			*d;
}	t_mlx;

typedef struct s_camera
{
	double low;
	t_vector cam_dir;
	double fov;
	t_vector hotizontal;
	t_vector up;
	t_vector vertical;
	t_vector low_left_corner;
	t_vector look_from;
}t_camera;

typedef struct s_color
{
	double red; 
	double green;
	double blue;
}t_color;

typedef struct s_light
{
	t_vector pos;
	t_color intensity;
}t_light;

typedef struct s_material
{
	t_color diffuse;
	double 	reflection;
}t_material;


t_vector  vec_cross(t_vector v1, t_vector v2);
t_vector  vec_add(t_vector v1, t_vector v2);
t_ray   get_ray(double u, double v, t_camera *camera);
void    ft_camera(t_camera *cam, t_vector vup , double aspect);
t_vector get_camera_direction(t_camera cam, t_vector get_ray);
t_vector  normalize(t_vector vec);
t_vector  vec_sub(t_vector v1, t_vector v2);
double	  dot_product(t_vector v1, t_vector v2);
t_vector normal_sphere(double t, t_ray r, t_sphere s);
t_vector  normalize(t_vector vec);
t_vector  vec_product(t_vector v, double i);
t_color clamp_color(t_color rgb);
int rgb_to_int(t_color rgb);
t_vector    normal_sphere(double t, t_ray r, t_sphere s);
void  position(t_material materials,t_light lights,t_cone c,t_camera cam);
# endif

