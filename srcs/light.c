#include "rtv1.h"

t_vec light_it_up(t_data *data, int x, int y, t_obj *obj, double t)
{
    t_vec hit;
    t_vec n;
    t_vec color;
    hit = vec_add(data->ray.o, vec_product(data->ray.dir, t));
    if (obj->id == 2)
    {
        n = vec_sub(vec_sub(hit, obj->pos), vec_product(obj->axis, dot_product(obj->axis, vec_sub(hit, obj->pos))));
        n = normalize(n);
        double ang_norm_light = fmax(0, dot_product(normalize(vec_sub(data->light->pos, hit)), n));
        t_vec L = normalize(vec_sub(data->light->pos, hit));
        t_vec V = normalize(vec_sub(data->ray.o, hit));
        t_vec dd = vec_product(n, dot_product(L, n));
        t_vec Rm = vec_sub(vec_product(dd, 2), L);
        double ka = 0, kd = 0, ks = 1;
        double intensite_pixel = ka + (kd * ang_norm_light) + (ks * pow(fmax(0, dot_product(Rm, V)), 40));
        color.x = obj->color.x * 0.3;
        color.y = obj->color.y * 0.3;
        color.z = obj->color.x * 0.3;
        color.x = fmin(255, obj->color.x * ang_norm_light + color.x);
        color.y = fmin(255, obj->color.y * ang_norm_light + color.y);
        color.z = fmin(255, obj->color.z * ang_norm_light + color.z);
        data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
        color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 16) & 255) + data->light->color.x * intensite_pixel);
        color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 8) & 255) + data->light->color.y * intensite_pixel);
        color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] & 255) + data->light->color.z * intensite_pixel);
        if (color.x > 255)
            color.x = 255;
        if (color.y > 255)
            color.y = 255;
        if (color.z > 255)
            color.z = 255;
    }
    else if (obj->id == 1)
    {
        n = normalize(vec_sub(hit, obj->pos));
        double ang_norm_light = fmax(0, dot_product(normalize(vec_sub(data->light->pos, hit)), n));
        t_vec L = normalize(vec_sub(data->light->pos, hit));
        t_vec V = normalize(vec_sub(data->ray.o, hit));
        t_vec dd = vec_product(n, dot_product(L, n));
        t_vec Rm = vec_sub(vec_product(dd, 2), L);
        double ka = 0, kd = 0, ks = 1;
        double intensite_pixel = ka + (kd * ang_norm_light) + (ks * pow(fmax(0, dot_product(Rm, V)), 40));
        color.x = obj->color.x * 0.3;
        color.y = obj->color.y * 0.3;
        color.z = obj->color.x * 0.3;
        color.x = fmin(255, obj->color.x * ang_norm_light + color.x);
        color.y = fmin(255, obj->color.y * ang_norm_light + color.y);
        color.z = fmin(255, obj->color.z * ang_norm_light + color.z);
        data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
        color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 16) & 255) + data->light->color.x * intensite_pixel);
        color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 8) & 255) + data->light->color.y * intensite_pixel);
        color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] & 255) + data->light->color.z * intensite_pixel);
        if (color.x > 255)
            color.x = 255;
        if (color.y > 255)
            color.y = 255;
        if (color.z > 255)
            color.z = 255;
    }
    else if (obj->id == 4)
    {
        n = normalize(obj->axis);
        double ang_norm_light = fmax(0, dot_product(normalize(vec_sub(data->light->pos, hit)), n));
        t_vec L = normalize(vec_sub(data->light->pos, hit));
        t_vec V = normalize(vec_sub(data->ray.o, hit));
        t_vec dd = vec_product(n, dot_product(L, n));
        t_vec Rm = vec_sub(vec_product(dd, 2), L);
        double ka = 0, kd = 0, ks = 1;
        double intensite_pixel = ka + (kd * ang_norm_light) + (ks * pow(fmax(0, dot_product(Rm, V)), 40));
        color.x = obj->color.x * 0.3;
        color.y = obj->color.y * 0.3;
        color.z = obj->color.z * 0.3;
        //    color.x =  fmin(255, obj->color.x*ang_norm_light + color.x);
        //     color.y =  fmin(255, obj->color.y*ang_norm_light + color.y);
        // 	 color.z =  fmin(255, obj->color.z*ang_norm_light + color.z);
        data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
        color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 16) & 255) + data->light->color.x * intensite_pixel);
        color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 8) & 255) + data->light->color.y * intensite_pixel);
        color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] & 255) + data->light->color.z * intensite_pixel);
        if (color.x > 255)
            color.x = 255;
        if (color.y > 255)
            color.y = 255;
        if (color.z > 255)
            color.z = 255;
    }
    else if (obj->id == 5)
    {
        double k = tan((obj->an_ra * M_PI / 180) / 2);
        double m = dot_product(data->ray.dir, vec_product(obj->axis, t)) + dot_product(vec_sub(data->ray.o, obj->pos), obj->axis);
        n = normalize(vec_sub(vec_sub(hit, obj->pos), vec_product(obj->axis, (1 + k + k) * m)));
        double ang_norm_light = fmax(0, dot_product(normalize(vec_sub(data->light->pos, hit)), n));
        t_vec L = normalize(vec_sub(data->light->pos, hit));
        t_vec V = normalize(vec_sub(data->ray.o, hit));
        t_vec dd = vec_product(n, dot_product(L, n));
        t_vec Rm = vec_sub(vec_product(dd, 2), L);
        double ka = 0, kd = 0, ks = 1;
        double intensite_pixel = ka + (kd * ang_norm_light) + (ks * pow(fmax(0, dot_product(Rm, V)), 70));
        color.x = obj->color.x * 0.3;
        color.y = obj->color.y * 0.3;
        color.z = obj->color.z * 0.3;
        color.x = fmin(255, obj->color.x * ang_norm_light + color.x);
        color.y = fmin(255, obj->color.y * ang_norm_light + color.y);
        color.z = fmin(255, obj->color.z * ang_norm_light + color.z);
        data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
        color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 16) & 255) + data->light->color.x * intensite_pixel);
        color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0] >> 8) & 255) + data->light->color.y * intensite_pixel);
        color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] & 255) + data->light->color.z * intensite_pixel);
        if (color.x > 255)
            color.x = 255;
        if (color.y > 255)
            color.y = 255;
        if (color.z > 255)
            color.z = 255;
    }

    return color;
}