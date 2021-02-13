#ifndef RTV1_H
# define RTV1_H
# include <stdio.h>
# include <math.h>
# include <mlx.h>
#include <stdlib.h>
# define WIDTH  1000
# define HEIGHT 1000
# define BPP 3
// # define PSIZE (4 - (600 * 3) % 4) % 4
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
 #include <fcntl.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct	s_vec	
{
	float	x;
	float	y;
	float	z;
}				t_vec;
typedef struct s_camera
{
   double low;
	t_vec cam_dir;
	double fov;
	//double aspect_ratio;
	t_vec hotizontal;
	t_vec up;
	t_vec vertical;
	t_vec low_left_corner;
	t_vec look_from;
}              t_camera;
typedef struct s_light
{
    t_vec		pos; 
    t_vec		color; 
	double		intens;

}              t_light;
typedef struct s_sphere
{
    t_vec			pos;
	t_vec			trans;
	t_vec			rot;
	t_vec			color;
	double			radius;
	struct s_sphere  *next;
}			t_sphere;

typedef struct s_cone
{
    t_vec			pos;
	t_vec			trans;
	t_vec			axis;
	t_vec			rot;
	t_vec			color;
	char	*angle;
	struct s_cone	*next;
}			t_cone;
typedef struct s_cylinder
{
    t_vec			pos;
	t_vec			trans;
	t_vec			axis;
	t_vec			rot;
	t_vec			color;
	double			angle;
	struct s_cylinder  *next;
}			t_cylinder;
typedef struct s_ray
{
	t_vec o;
	t_vec dir;
	
}t_ray;

typedef struct s_obj
{
	int 			id;
	double			t;
    t_vec			pos;
	t_vec			trans;
	t_vec			axis;
	t_vec			rot;
	t_vec			color;
	double			an_ra;
	double			(*inter)(t_ray *ray,struct s_obj *);
	struct s_obj  *next;
}			t_obj;
typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	void		*img_ptr;
	int 		pxl;
	int			*d;

}	t_mlx;
typedef struct	s_vars	
{
	t_vec	n;
	float	t;

}				t_vars;
typedef struct s_data
{
    char **tab;
	t_vars			var;
	int			fd;
	t_mlx		mlx;
    t_obj		*obj;
	t_camera	*camera;
	t_light		*light;
	t_ray		ray;
}              t_data;
double    intersection_spher(t_ray *r,t_obj *s);
double		 intersection_cylinder(t_ray *ray, t_obj *cylinder);
t_vec  vec_cross(t_vec v1, t_vec v2);
t_vec  vec_add(t_vec v1, t_vec v2);
t_ray   get_ray(double u, double v, t_camera *camera);
void    ft_camera(t_camera *cam, t_vec vup , double aspect);
t_vec get_camera_direction(t_camera cam, t_vec get_ray);


t_vec  vec_sub(t_vec v1, t_vec v2);
double	  dot_product(t_vec v1, t_vec v2);
t_vec normal_sphere(double t, t_ray r, t_sphere s);
t_vec  normalize(t_vec vec);
t_vec  vec_product(t_vec v, double i);
#endif