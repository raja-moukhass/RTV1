
#include "rtv1.h"



double cone_intersection(t_ray *ray, t_obj *cone)
{
    double k;
    double a;
    double b;
    double c;
    double t1;
    double t2;
    double t;
    k = tan((cone->an_ra * M_PI / 180.0));
    t_vec obj_center;
    obj_center = vec_sub(ray->o, cone->pos);
    a = dot_product(ray->dir, ray->dir) - (1 + pow(k, 2)) * (dot_product(ray->dir, cone->axis) * dot_product(ray->dir, cone->axis));
    b = 2 * (dot_product(ray->dir, obj_center) - (1 + pow(k, 2)) * (dot_product(ray->dir, cone->axis) * dot_product(obj_center, cone->axis)));
    c = (dot_product(obj_center, obj_center) - (1 + pow(k, 2)) * (dot_product(obj_center, cone->axis) * dot_product(obj_center, cone->axis)));
    double discr = b * b - 4 * a * c;
    if (discr < 0)
        return -1;
    else
    {
        t1 = (-b - sqrt(discr)) / (2 * a);
        t2 = (-b + sqrt(discr)) / (2 * a);
    }
    if (t2 < 0 && t1 < 0)
        return (-1);
    else if (t1 >= 0 && t2 < 0)
        t = t1;
    else if (t2 > 0 && t1 < 0)
        t = t2;
    else
        t = fmin(t1, t2);
    return t;
}

// double		solve_plane(t_plane *pl, t_ray ray)
// {
// 	t_equation	e;
// 	t_vect		x;

// 	e.a = vector_scalar(ray.dir, pl->norm);
// 	if (e.a == 0)
// 		return (0);
// 	x = vector_sub(ray.origin, pl->origin);
// 	e.b = vector_scalar(x, pl->norm);
// 	e.s1 = -e.b / e.a;
// 	if (e.s1 < 0)
// 		return (0);
// 	return (e.s1);
// }


double  intersect_plane(t_ray *r, t_obj *plane)
{
    double  t;

    double res = dot_product(r->dir, plane->axis);
	if (res == 0)
		return (0);
    t_vec nomin = vec_sub(r->o, plane->pos);
    double denom = dot_product(nomin,plane->axis);
    double s1 = -(denom)/(res);
    if(s1 <= 0)
        return 0;
        return(s1);
}

double intersection_cylinder(t_ray *ray, t_obj *cylinder)
{
	ray = ft_transform_ray(ray, cylinder);
    t_vec delta_p = vec_sub(ray->o, cylinder->pos);
    double tmp = dot_product(ray->dir, cylinder->axis);
    double a = dot_product(ray->dir, ray->dir) - pow(tmp, 2);

    double tmp1 = dot_product(delta_p, cylinder->axis);
    double b = 2 * (dot_product(ray->dir, delta_p) - (tmp * tmp1));
    double c = dot_product(delta_p, delta_p) - pow(tmp1, 2) - (cylinder->an_ra * cylinder->an_ra);
    double delta = b * b - (4 * a * c);
    double t1;
    double t2;
    if (delta < 0)
        return 0;
    t1 = (-b - sqrt(delta)) / (2 * a);
    t2 = (-b + sqrt(delta)) / (2 * a);
    double t;
    if (t1 <= 0 && t2 <= 0)
        return 0;
    if (t1 >= 0 && t2 >= 0)
    {
        if (t1 > t2)
            t = t2;
        else
            t = t1;
    }
    else if ((t1 >= 0 && t2 <= 0) || (t2 <= 0 && t2 >= 0))
    {
        if (t1 >= t2)
            t = t1;
        else
            t = t2;
    }
    return t;
}

double intersection_spher(t_ray *r, t_obj *s)
{

    double t1;
    double t2;
    double t;

    t_vec dist = vec_sub(r->o, s->pos);
    double a =  get_norm(r->dir);
    double b = 2 * dot_product(r->dir, dist);
    double c = get_norm(dist) - (s->an_ra * s->an_ra);
    double delta = b * b - 4 * a * c;


    if (delta < 0)
        return (-1);

    t1 = (-1 * b - sqrt(delta)) / (2 * a);
    t2 = (-1 * b + sqrt(delta)) / (2 * a);

    if (t2 <= 0 && t1 <= 0)
        return (-1);
    else if (t1 >= 0 && t2 <= 0)
        t = t1;
    else if (t2 >= 0 && t1 <= 0)
        t = t2;
    else
        t = fmin(t1, t2);
    return (t);
}
