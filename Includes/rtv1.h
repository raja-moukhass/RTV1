#ifndef RTV1_H
# define RTV1_H
# include <stdio.h>
# include <math.h>
# include <mlx.h>
#include <stdlib.h>
# define WIDTH  1000
# define HEIGHT 1000
# define BPP 3
# define PI 22 /7
# define ALPHA 60 * PI / 180
// # define PSIZE (4 - (600 * 3) % 4) % 4
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
 #include <fcntl.h>
#include <stdlib.h>
# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "math.h"
# include "pthread.h"
#include "../miniLibX/mlx.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>



typedef struct s_sol
{
	double k;
    double a;
    double b;
    double c;
    double t1;
    double t2;
    double t;
	double tmp;
	double tmp_2;
	double tmp1;
	double delta;

}t_sol;

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct  s_var_light
{
	t_vec L;
	t_vec V;
	t_vec dd;
	t_vec Rm;
	double intensite_pixel;
	double ang_norm_light;
}t_var_light;


typedef struct s_camera
{
   double low;
	t_vec cam_dir;
	double fov;
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

typedef struct s_delta{
  double a;
  double b;
  double c;
  double delta;
} t_delta;

typedef struct s_ray
{
	t_vec o;
	t_vec dir;

}t_ray;

typedef struct s_obj
{
	int 			id;
	double			t;
	t_vec			hit;
    t_vec			pos;
	t_vec			trans;
	t_vec			axis;
	t_vec			rot;
	t_vec			n;
	t_vec			color;
	double			an_ra;
	double			(*inter)(t_ray *ray,struct s_obj *);
	struct s_obj  *next;
}			t_obj;
typedef struct s_hit
{
	double t;
	t_obj *o;
	t_vec n;
	t_vec p;
}t_hit;

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
	double	t;

}				t_vars;
typedef struct s_data
{
    char **tab;
	t_vec hit;
	t_vec  n;

	t_vars			var;
	int			fd;
	t_mlx		mlx;
    t_obj		*obj;
	t_camera	*camera;
	t_light		*light;
	t_ray		ray;
}              t_data;


typedef	struct	s_get_ray
{
	t_vec	horizontal;
	t_vec	vertical;
	t_vec	cam_u;
	t_vec	cam_v;
	t_vec	cam_w;
	t_ray	new;
	double	half_h;
	double	half_w;
}				t_get_ray;

typedef struct s_raytracer
{
	t_vec color;
    t_obj *head;
    t_obj *save;
    t_ray shadow;
    int y;
    int x;
	double t;
	double t1;

}t_raytracer;
void	color_limit(t_vec *color);
double    intersection_spher(t_ray *r,t_obj *s);
void ray_tracer(t_data *data);
double cone_intersection(t_ray *ray, t_obj *cone);
t_vec ft_object_normal(double hit, t_ray *ray, t_vec p, t_obj *o);
int ft_lines(int fd);
double get_norm(t_vec v);
t_vec normal_sphere(double t, t_ray r, t_sphere s);
t_vec normalize(t_vec vec);
int mouse_move(int x, int y, t_data *data);
double ft_min_ray(double t1, double t2, double t);
double ft_atof(char *str);

t_vec light_it_up(t_data *data, int x, int y, t_obj *obj, double t);
void init_data(t_data **data, char *av);
t_var_light          *ft_var_light(t_data *data, t_obj *obj, t_var_light *light);

//  n = normalize(vec_sub(hit, obj->pos));
//         double ang_norm_light = fmax(0, dot_product(normalize(vec_sub(data->light->pos, hit)), n));
//         t_vec L = normalize(vec_sub(data->light->pos, hit));
//         t_vec V = normalize(vec_sub(data->ray.o, hit));
//         t_vec dd = vec_product(n, dot_product(L, n));
//         t_vec Rm = vec_sub(vec_product(dd, 2), L);
//         double ka = 0, kd = 0, ks = 1;
//         double intensite_pixel = ka + (kd * ang_norm_light) + (ks * pow(fmax(0, dot_product(Rm, V)), 40));
//         color.x = obj->color.x * 0.3;
//         color.y = obj->color.y * 0.3;
//         color.z = obj->color.x * 0.3;
//         color.x = fmin(255, obj->color.x * ang_norm_light + color.x);
//         color.y = fmin(255, obj->color.y * ang_norm_light + color.y);
//         color.z = fmin(255, obj->color.z * ang_norm_light + color.z);
//         data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
//         color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 16) & 255) + data->light->color.x * intensite_pixel);
//         color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 8) & 255) + data->light->color.y * intensite_pixel);
//         color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] & 255) + data->light->color.z * intensite_pixel);
//         if (color.x > 255)
//             color.x = 255;
//         if (color.y > 255)
//             color.y = 255;
//         if (color.z > 255)
//             color.z = 255;



// t_vec light_it_up(t_data *data, int x, int y, t_obj *obj, double t)
// {
// 	t_vec hit;
// 	t_vec n;
// 	t_vec color;

// 	obj->hit = vec_add(data->ray.o, vec_product(data->ray.dir, t));
// 	if (obj->id == 2)
// 	obj->n = normalize (vec_sub(vec_sub(hit, obj->pos), vec_product(obj->axis, dot_product(obj->axis, vec_sub(hit, obj->pos)))));
// 	else if (obj->id == 1)
// 		obj->n = normalize(vec_sub(hit, obj->pos));
// 	else if (obj->id == 4)
// 		obj->n = normalize(obj->axis);
// 	else if (obj->id == 5)
// 	{
// 		double k = tan((obj->an_ra * M_PI / 180) / 2);
// 		double m = dot_product(data->ray.dir, vec_product(obj->axis, t)) + dot_product(vec_sub(data->ray.o, obj->pos), obj->axis);
// 		obj->n = normalize(vec_sub(vec_sub(hit, obj->pos), vec_product(obj->axis, (1 + k + k) * m)));
//     }
// 	color = get_color(data,obj, x, y);
// 	return (color);

// }
// t_var_light          *ft_var_light(t_data *data, t_obj *obj, t_var_light *light)
// {
// 	light->ang_norm_light = fmax(0, dot_product(normalize(vec_sub(data->light->pos, obj->hit)), obj->n));
// 	light->intensite_pixel =  (light->ang_norm_light) + (pow(fmax(0, dot_product(light->Rm, light->V)), 40));
// 	light->L = normalize(vec_sub(data->light->pos, obj->hit));
// 	light->V = normalize(vec_sub(data->ray.o, obj->hit));
// 	light->dd = vec_product(obj->n, dot_product(light->L, obj->n));
// 	light->Rm = vec_sub(vec_product(light->dd, 2), light->L);
// 	return(light);
// }

// t_vec       get_color(t_data *data, t_obj *obj, int x, int y)
// {
// 	t_var_light *light;
// 	t_vec color;
// 	light = malloc(sizeof(t_var_light));
// 	light = ft_var_light(data, obj, light);
// 	color.x = obj->color.x * 0.3;
// 		color.y = obj->color.y * 0.3;
// 		color.z = obj->color.x * 0.3;
// 		color.x = fmin(255, obj->color.x * light->ang_norm_light + color.x);
// 		color.y = fmin(255, obj->color.y * light->ang_norm_light + color.y);
// 		color.z = fmin(255, obj->color.z * light->ang_norm_light + color.z);
// 		data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
// 		color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 16) & 255) + data->light->color.x * light->intensite_pixel);
// 		color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 8) & 255) + data->light->color.y * light->intensite_pixel);
// 		color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] & 255) + data->light->color.z * light->intensite_pixel);
// 		if (color.x > 255)
// 			color.x = 255;
// 		if (color.y > 255)
// 			color.y = 255;
// 		if (color.z > 255)
// 			color.z = 255;
// 	return color;

// }










double	intersect_cone( t_ray *r, t_obj *c);
double  intersect_plane(t_ray *r, t_obj *plane);
double ft_min_ray(double t1, double t2, double t);
double intersection_spher(t_ray *r, t_obj *s);
double      get_norm(t_vec v);
int keyhook(int key, void *p);
void image_clear(int *d);
void call_error(t_data *data);
int ft_checker(t_data **data);
void camera_check(t_data **dat, int i);
void light_check(t_data **dat, int i);
void obj_check(t_data **dat, int i, int id);
double ft_atof(char *str);
t_obj *add_node(t_data **dat);


void init_data(t_data **data, char *av);
t_ray get_ray(double u, double v, t_camera *camera);
t_vec get_camera_direction(t_camera cam, t_vec get_ray);
t_ray init_rayy(int i, int j, t_camera *cam);
t_vec       get_color(t_data *data, t_obj *obj, int x, int y);


double		 intersection_cylinder(t_ray *ray, t_obj *cylinder);
t_vec  vec_cross(t_vec v1, t_vec v2);
t_vec  vec_add(t_vec v1, t_vec v2);
t_ray   get_ray(double u, double v, t_camera *camera);
void    ft_camera(t_camera *cam, t_vec vup , double aspect);
t_vec get_camera_direction(t_camera cam, t_vec get_ray);
t_vec ft_rotate_x(t_vec v, double angle);
t_vec ft_rotate_y(t_vec v, double angle);
t_vec ft_rotate_z(t_vec v, double angle);
t_vec ft_rotate(t_vec v, t_vec rot);
t_vec ft_translate(t_vec v, t_vec trans);
t_vec   ft_transform_ray(t_obj *o);
int ft_close(void);
t_vec  vec_sub(t_vec v1, t_vec v2);
double	  dot_product(t_vec v1, t_vec v2);
t_vec normal_sphere(double t, t_ray r, t_sphere s);
t_vec  normalize(t_vec vec);
t_vec  vec_product(t_vec v, double i);
t_vec split_data(t_data *data, char *str);

#endif
