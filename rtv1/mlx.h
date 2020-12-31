#ifndef RTV1_H
# define RTV1_H
# include <stdio.h>
# include <math.h>
# include <mlx.h>
#include <stdlib.h>
# define WIDTH  600
# define HEIGHT 600
# define BPP 3
# define PSIZE (4 - (600 * 3) % 4) % 4
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40

typedef struct	s_point		//target
{
	float	x;
	float	y;
	float	z;
}				t_point;
typedef struct	s_sphere 
{
	float r;
	t_point center;
}				t_sphere;
typedef struct	s_ray
{
	t_point s; //source
	t_point t; //target
}				t_ray;

typedef struct	s_data
{
	int		*d;
	void	*ptr;
	void	*win;
	void	*img;
	t_ray	ray;
	t_point	cam_s;	//cam source
	t_point	cam_t;	//cam target

}				t_data;
#endif