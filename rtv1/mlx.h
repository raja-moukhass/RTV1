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

typedef struct	s_vec		//target
{
	float	x;
	float	y;
	float	z;
}				t_vec;
typedef struct	s_sphere 
{
	t_vec color;
	float r;
	t_vec c;
}				t_sphere;
typedef struct	s_cylinder 
{
	t_vec color;
	float r;
	t_vec ax;
	t_vec	o;
}				t_cylinder;
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
	int		cyl_center_calc;

	t_vec n;
	t_vec	lum_pos;
	t_cylinder *cyl;
	t_ray	ray;
	t_sphere	*sphere;
	t_vec	cam_s;	//cam source
	t_vec	cam_t;	//cam target

}				t_data;
#endif