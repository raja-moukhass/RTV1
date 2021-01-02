/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:06:46 by ramoukha          #+#    #+#             */
/*   Updated: 2021/01/02 12:26:32 by ramoukha         ###   ########.fr       */
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

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	void		*img_ptr;
	int 		pxl;
}	t_mlx;

typedef struct s_vector
{
	float x;
	float y;
	float z;
}t_vector;

typedef struct s_sphere
{
	t_vector pos;
	float radius;
}t_sphere;

typedef struct s_ray
{
	t_vector start;
	t_vector dir;
	
}t_ray;


// 	t_mlx f;
  
//   f.ptr = mlx_init();
//   f.win = mlx_new_window(f.ptr, 500, 500, "Title");
//   	hit = intersectRaySphere(&r, &s);

//   f.pxl = mlx_pixel_put ( f.ptr,f.win, 40,40,255 );
// // mlx_loop(f.ptr);


# endif
