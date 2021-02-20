
#include "rtv1.h"

double				intersect_cone( t_ray *r, t_obj *c)
{
    double      t;
	t_delta		d;
	t_vec	dist;
	double		anglesin;
	double		anglecos;

	anglecos = pow(cos(c->an_ra), 2.0);
	anglesin = pow(sin(c->an_ra), 2.0);
	dist = vec_sub(r->o, c->axis);
	d.a = anglecos * (r->dir.z * r->dir.z + r->dir.x * r->dir.x)
		- anglesin * (r->dir.y * r->dir.y);
	d.b = 2.0 * (anglecos * (dist.z * r->dir.z + dist.x * r->dir.x)
			- anglesin * (dist.y * r->dir.y));
	d.c = anglecos * (dist.z * dist.z + dist.x * dist.x)
		- anglesin * (dist.y * dist.y);
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.00000001)
		return (0);
	d.delta = sqrt(d.delta);
	return (ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
				(-d.b - d.delta) / (2.0 * d.a), &t));
}
double  intersect_plane(t_ray *r, t_obj *plane)
{
    double  t;

    t_vec p0l0 = vec_sub(r->dir, plane->pos );
    double nomin = dot_product(p0l0, plane->axis);
    double denom = dot_product(plane->axis, r->dir);
    if (denom == 0 || (denom > 0 &&  nomin > 0) ||  (denom < 0 &&  nomin < 0) )
        return 0;

    t = -nomin / denom;

        return (t);

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
