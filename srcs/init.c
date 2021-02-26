#include "rtv1.h"

void init_data(t_data **data, char *av)
{
    int i;
    char **tab;
    int count;
    int fd;
    t_camera cam;

    i = 0;
    fd = open(av, O_RDONLY);
    count = ft_lines(fd);
    fd = open(av, O_RDONLY);
    tab = (char **)malloc(sizeof(char *) * (count + 1));
    while (get_next_line(fd, &tab[i]))
        i++;
    close(fd);
    tab[i] = NULL;
    (*data) = (t_data *)malloc(sizeof(t_data));
    (*data)->tab = tab;
    (*data)->camera = (t_camera *)malloc(sizeof(t_camera));
    (*data)->obj = malloc(sizeof(t_obj));
    (*data)->obj = NULL;
    (*data)->light = malloc(sizeof(t_light));
    (*data)->camera->look_from = (t_vec){0, 5, 0};
    (*data)->camera->cam_dir = (t_vec){0, 0, 0};
    (*data)->camera->up = (t_vec){0, 1, 0};
    (*data)->camera->fov = 20;
}

t_vec get_camera_direction(t_camera cam, t_vec get_ray)
{
    t_vec ray;
    cam.low_left_corner = vec_add(cam.look_from, get_ray);
    ray = vec_sub(cam.low_left_corner, cam.look_from);
    return ray;
}

double ft_min_ray(double t1, double t2, double t)
{
    t_sol n;
  if (t2 <= 0 && t1 <= 0)
        return (-1);
    else if (t1 >= 0 && t2 <= 0)
        t = t1;
    else if (t2 >= 0 && t1 <= 0)
        t = t2;
    else
        t = fmin(t1, t2);
    return (t);;
}

t_ray get_ray(double u, double v, t_camera *camera)
{
    t_vec horizontal;
    t_vec vertical;
    t_vec cam_u;
    t_vec cam_v;
    t_vec cam_w;
    t_ray new;

    u = 2 * (u + 2) / (HEIGHT)-1;
    v = 1 - 2 * (v + 2) / (HEIGHT);
    double half_h;
    double half_w;
    new.o = camera->look_from;
    half_h = 2.0 * tan((camera->fov * M_PI / 180) / 2);
    half_w = half_h;
    cam_w = normalize(vec_sub(camera->look_from, camera->cam_dir));
    cam_u = normalize(vec_cross(camera->up, cam_w));
    cam_v = vec_cross(cam_w, cam_u);
    horizontal = vec_product(cam_u, half_w);
    vertical = vec_product(cam_v, half_h);
    camera->low_left_corner = vec_sub(camera->look_from, cam_w);
    camera->low_left_corner = vec_sub(camera->low_left_corner, vec_product(horizontal, 1 / 2));
    camera->low_left_corner = vec_sub(camera->low_left_corner, vec_product(vertical, 1 / 2));
    new.dir = vec_sub(camera->low_left_corner, new.o);
    new.dir = vec_sub(new.dir, vec_product(horizontal, u));
    new.dir = vec_add(new.dir, vec_product(vertical, v));
    new.dir = normalize(new.dir);
    return new;
}
