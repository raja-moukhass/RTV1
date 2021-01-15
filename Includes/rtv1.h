/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:06:46 by ramoukha          #+#    #+#             */
/*   Updated: 2021/01/15 17:13:08 by ramoukha         ###   ########.fr       */
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
# define WIDTH 600
# define HEIGHT 600



typedef struct s_vector
{
	double x;
	double y;
	double z;

}t_vector;

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

t_vector  vec_sub(t_vector v1, t_vector v2);
double	  dot_product(t_vector v1, t_vector v2);
t_vector normal_sphere(double t, t_ray r, t_sphere s);
t_vector  normalize(t_vector vec);
t_vector  vec_product(t_vector v, double i);
# endif

