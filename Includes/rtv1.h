/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:06:46 by ramoukha          #+#    #+#             */
/*   Updated: 2021/01/08 16:28:39 by ramoukha         ###   ########.fr       */
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
typedef struct	s_vec		//target
{
	float	x;
	float	y;
	float	z;
}				t_vec;
typedef struct	s_sphere 
{
	float r;
	t_vec c;
}				t_sphere;
typedef struct	s_ray
{
	t_vec o; //source or origine
	t_vec d; //target or destination
}				t_ray;

typedef struct	s_data
{
	int		*d;
	void	*ptr;
	void	*win;
	void	*img;
	t_ray	ray;
	t_sphere	*sphere;
	t_vec	cam_s;	//cam source
	t_vec	cam_t;	//cam target

}				t_data;

// typedef struct	s_mlx
// {
// 	void		*ptr;
// 	void		*win;
// 	void		*img;
// 	void		*img_ptr;
// 	int 		pxl;
// }	t_mlx;

// typedef struct s_vector
// {
// 	float x;
// 	float y;
// 	float z;

// }t_vector;

// typedef struct s_sphere
// {
// 	t_vector pos;
// 	float radius;
// }t_sphere;

// typedef struct s_ray
// {
// 	t_vector start;
// 	t_vector dir;
	
// }t_ray;

# endif
