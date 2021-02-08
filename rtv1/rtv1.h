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
 #include <fcntl.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <stdio.h>
typedef struct	s_vec	
{
	float	x;
	float	y;
	float	z;
}				t_vec;
typedef struct s_camera
{
    t_vec		source; 
    t_vec		target; 
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
typedef struct s_plane
{
    t_vec			pos;
	t_vec			trans;
	t_vec			axis;
	t_vec			rot;
	t_vec			color;
	char	*angle;
	struct s_plane  *next;
}			t_plane;
typedef struct s_data
{
    char **tab;
	int		fd;
    t_camera	*camera;
	t_sphere	*sphere;
	t_cone		*cone;
	t_cylinder		*cylinder;
	t_plane		*plane;
	t_light		*light;
}              t_data;

#endif