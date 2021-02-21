#include "rtv1.h"

double ft_min_ray(double t1, double t2, double *t)
{
    if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
    {
        *t = t1;
        return (1);
    }
    else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
    {
        *t = t2;
        return (1);
    }
    else
        return (0);
}

double ft_atof(char *str)
{
    int i;
    int j;
    int signe;
    double res;
    i = 0;
    res = 0;
    signe = 1;
    while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t' || str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        signe = str[i] == '-' ? -1 : 1;
        i++;
    }
    while (str[i] <= '9' && str[i] >= '0')
    {
        res = (res * 10) + str[i] - '0';
        i++;
    }
    j = 0;
    if (str[i] == '.')
    {
        i++;
        while (str[i] <= '9' && str[i] >= '0' && j <= 3)
        {
            res = res + (double)((str[i] - '0') / pow(10.0, (double)++j));
            i++;
        }
    }
    return (res * signe);
}

double get_norm(t_vec v)
{
    double ret;
    ret = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    return (ret);
}




int ft_lines(int fd)
{
    char *line = NULL;
    int count = 0;

    while (get_next_line(fd, &line))
    {
        count++;
        free(line);
    }
    close(fd);
    return (count);
}

t_vec split_data(t_data *data, char *str)
{
    int i;
    char **ar;
    int j;
    int dot;
    t_vec ret;

    i = 0;
    ar = ft_strsplit(str, ' ');
    while (ar[i])
    {
        dot = 1;
        j = 0;
        while (ar[i][j])
        {
            if (!ft_isdigit(ar[i][j]))
            {
                if ((ar[i][j] == '-' && j == 0) || (ar[i][j] == '.' && dot && j != 0 && ft_isdigit(ar[i][j + 1])))
                    ;
                else
                    call_error(data);
                if (ar[i][j] == '.')
                    dot--;
            }
            j++;
        }
        i++;
    }
    if (i != 3)
        call_error(data);
    ret.x = ft_atof(ar[0]);
    ret.y = ft_atof(ar[1]);
    ret.z = ft_atof(ar[2]);

    return (ret);
}




void init_data(t_data **data, char *av)
{
    int i;
    char **tab;
    int count;
    int fd;

    t_camera cam;
    //init camera

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

t_vec normal_sphere(double t, t_ray r, t_sphere s)
{
    t_vec hit;
    t_vec n;

    hit = vec_add(r.o, vec_product(normalize(r.dir), t));
    n.x = hit.x - s.pos.x;
    n.y = hit.y - s.pos.y;
    n.z = hit.z - s.pos.z;
    return (normalize(n));
}

t_vec normalize(t_vec vec)
{
    double mod;

    mod = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
    vec.x /= mod;
    vec.y /= mod;
    vec.z /= mod;
    return (vec);
}

t_ray init_rayy(int i, int j, t_camera *cam)
{
    t_vec s;
    t_ray r;
    t_vec cam_u;
    t_vec cam_v;
    t_vec cam_w;

    cam_w = normalize(vec_sub(cam->look_from, cam->cam_dir));
    cam_u = normalize(vec_cross(cam->up, cam_w));
    cam_v = vec_cross(cam_w, cam_u);
    s = vec_sub(cam->look_from, vec_product(cam->cam_dir, 2000));
    s = vec_sub(s, vec_product(cam_u, (i - (HEIGHT / 2))));
    s = vec_add(s, vec_product(cam_v, ((HEIGHT / 2) - j)));
    r.dir = vec_sub(s, cam->look_from);
    r.o = cam->look_from;
    r.dir = normalize((r.dir));
    return (r);
}

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



void ray_tracer(t_data *data)
{
    t_vec color;
    t_vec dif;
    t_obj *head;
    t_obj *save;
    int y;
    int x;
    double PI = 22 / 7;
    double alpha = 60 * PI / 180;
    t_vec L;
    t_vec V;
    double intensite_pixel;
    y = 0;
    t_vec n;
    t_vec p;
    double t;
    int i = 0;
    double yes;
    int check = 1;
    double t1 = -1;
    // t_camera shadow;
    t_ray shadow;
    t_vec hit;
    double len1;
    double len2;

    /*
	while (y < HEIGHT)
    {
        x = -1;
        while (x++ < WIDTH)
        {
			save = get_col(data, ray);
			save(color ,hit, t);
			if(save.t != -1)
			{

			}
		}
	}
	*/
    while (y < HEIGHT)
    {
        x = -1;
        while (x++ < WIDTH)
        {
            data->ray = get_ray(x, y, data->camera);
            // printf("x = %f y = %f z %f",data->ray.dir.x, data->ray.dir.y, data->ray.dir.z);
            t1 = -1;
            head = data->obj;
            while (head)
            {
                t = head->inter(&(data->ray), head);
                if ((t <= t1 && t1 > 0 && t > 0) || (t >= t1 && t1 < 0 && t > 0))
                {
                    t1 = t;
                    save = head;
                }
                head = head->next;
            }
            if (t1 != -1)
            {
                // shadow.o = 	vec_add(data->ray.o, vec_product(data->ray.dir, t1));
                // shadow.dir = vec_sub(data->light->pos, shadow.o );
                // 	 t1 = -1;
                // head = data->obj;
                // while(head)
                // {
                //     t = head->inter(&(shadow), head);
                // 	    if (t != -1 && save->id != head->id)
                // 		{
                // 			t1 = t;
                // 			break;
                // 		}
                // 	head = head->next;
                // }
                // if (t1 != -1)
                // color = (t_vec){0,0,0};
                // else
                color = light_it_up(data, x, y, save, t1);
                hit = vec_add(data->ray.o, vec_product(data->ray.dir, t1));
                shadow.o = data->light->pos;
                shadow.dir = normalize(vec_sub(hit, data->light->pos));
                head = data->obj;
                while (head)
                {
                    // if (save != head)
                        t = head->inter(&(shadow), head);
                    if (x == 107 && y == 736)
                        ft_putendl("");
                    if (t > 0 && save != head)
                    {
                        t_vec hit2 = vec_add(shadow.o, vec_product(shadow.dir, t));
                        len1 = dot_product(vec_product(shadow.dir, t), vec_product(shadow.dir, t));
                        len2 = dot_product(vec_sub(hit, data->light->pos), vec_sub(hit, data->light->pos));

                        if (len1 < len2)
                        {
                            color.x = color.x * 0.1;
                            color.y = color.y * 0.1;
                            color.z = color.z * 0.1;
                            break;
                        }
                    }
                    head = head->next;
                }

                data->mlx.d[(y * WIDTH + x)] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
            }
        }
        y++;
    }
}

int mouse_move(int x, int y, t_data *data)
{
    double PI = 22 / 7;
    double alpha = 60 * PI / 180;
    // data->camera->look_from.x = x - (HEIGHT / 2);
   
    ft_putendl("");
    
    ft_putnbr(x);
    ft_putendl("");
    ft_putnbr(y);
    image_clear(data->mlx.d);
    ray_tracer(data);
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img, 0, 0);
    // mlx_pixel_put(data->mlx.ptr, data->mlx.win,data->light->pos.x,data->light->pos.y,0xFFFFFF);
    return 1;
}

int key_press(int key, t_data *data)
{
    double p;

    // if (key == 35)
    // 	mlx->up = 1;
    // if (key == 31)
    // 	mlx->up = 0;
    // if (key == 34)
    // 	init_mlx(mlx, mlx->key);
    if (key == 124 || key == 123)
    {
        // p = (mlx->max_r - mlx->min_r) / 10;
        data->light->pos.x += key == 123 ? data->light->pos.x++ : data->light->pos.x;
        data->light->pos.x += key == 123 ? data->light->pos.x-- : data->light->pos.x;
    }
    image_clear(data->mlx.d);
    ray_tracer(data);
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img, 0, 0);
    return (0);
}

int main(int ac, char **av)
{
    t_data *data;
    if (ac != 2)
        exit(0);

    init_data(&data, av[1]);
    ac = 0;

    char **tab;
    int i = 0;

    if (ft_checker(&data) < 0)
    {
        ft_putendl("error");
        exit(0);
    }
    int bpp;
    t_mlx f;

    f.ptr = mlx_init();
    f.win = mlx_new_window(f.ptr, WIDTH, HEIGHT, "RTV1");
    mlx_hook(f.win, 17, 0, ft_close, &data);
    mlx_hook(f.win, 2, 0, keyhook, data);
    f.img = mlx_new_image(f.ptr, WIDTH, HEIGHT);
    f.d = (int *)mlx_get_data_addr(f.img, &bpp, &bpp, &bpp);
    data->mlx = f;
   
    ray_tracer(data);
    mlx_hook(data->mlx.win, 6, 0, mouse_move, data);
    // mlx_hook(data->mlx.win, 2, 0, key_press, data);
    mlx_put_image_to_window(f.ptr, f.win, f.img, 0, 0);
    mlx_loop(f.ptr);
    return (0);
}
