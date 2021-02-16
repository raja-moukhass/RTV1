#include "rtv1.h"




double		ft_min_ray(float t1, float t2, double *t)
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

double				intersect_cone( t_ray *r, t_obj *c)
{
    double      t;
	t_delta		d;
	t_vec	dist;
	float		anglesin;
	float		anglecos;

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

double      get_norm(t_vec v)
{
    double ret;
    ret = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    return (ret);
}

t_obj *add_node(t_data **dat)
{
    int i = 1;
    t_data *data = *dat;

    t_obj *temp;
    t_obj *p;
    temp = ft_memalloc(sizeof(t_obj));
    if (data->obj == NULL)
        data->obj = temp;
    else
    {
        p = data->obj;
        while (p->next != NULL)
        {
            p = p->next;
            i++;
        }
        p->next = temp;
    }
    temp->id = i;
    return (temp);
}
void debugstr(char *str, int nl)
{
    ft_putstr_fd("|", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("|", 2);
    if (nl)
        ft_putendl_fd("", 2);
}

void debugnbr(int nbr, int nl, int fd)
{
    ft_putstr_fd("|", fd);
    ft_putnbr_fd(nbr, fd);
    ft_putstr_fd("|", fd);
    if (nl)
        ft_putendl_fd("", fd);
}

void call_error(t_data *data)
{
    ft_putstr("parsing error");
    exit(1);
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

double  intersect_plane(t_ray *r, t_obj *plane) 
{ 
    double  t;

    t_vec p0l0 = vec_sub(r->dir, plane->pos ); 
    double nomin = dot_product(p0l0, plane->axis);
    float denom = dot_product(plane->axis, r->dir); 
    if (denom == 0 || (denom > 0 &&  nomin > 0) ||  (denom < 0 &&  nomin < 0) ) 
        return 0;

    t = -nomin / denom; 
  
        return (t); 
  
}

void camera_check(t_data **dat, int i)
{
    int check;
    t_data *data;

    data = *dat;
    check = 1;
    while (data->tab[i + check] && check < 3)
        check++;
    if (check != 3)
        call_error(data);

    data->camera->look_from = split_data(data, data->tab[i + 1]);

    data->camera->cam_dir = split_data(data, data->tab[i + 2]);
}
void light_check(t_data **dat, int i)
{
    int check;
    t_data *data;

    data = *dat;
    check = 1;
    while (data->tab[i + check] && check < 3)
        check++;
    if (check != 3)
        call_error(data);

    data->light->pos = split_data(data, data->tab[i + 1]);

    data->light->color = split_data(data, data->tab[i + 2]);
    data->light->intens = ft_atof(ft_strdup(data->tab[i + 3]));
}
void obj_check(t_data **dat, int i, int id)
{
    int check;
    t_obj *temp;
    t_data *data;

    data = *dat;
    check = 1;
    while (data->tab[i + check] && check < 4)
        check++;

    if (check != 4)
        call_error(data);
    temp = add_node(dat);
    temp->id = id;
    temp->pos = split_data(data, data->tab[++i]);
    temp->trans = split_data(data, data->tab[++i]);
    temp->rot = split_data(data, data->tab[++i]);
    temp->color = split_data(data, data->tab[++i]);
    if (id != 4)
    temp->an_ra = ft_atof(ft_strdup(data->tab[++i]));
    if (id != 1)
        temp->axis = split_data(data, data->tab[++i]);
    if (id == 1)
        temp->inter = &intersection_spher;
    else if (id == 2)
        temp->inter = &intersection_cylinder;
    else if (id == 4)
        temp->inter = &intersect_plane;
    else if (id == 5)
        temp->inter = &intersect_cone;

}

int ft_checker(t_data **data)
{
    int i = 0;
    while ((*data)->tab[i])
    {
        //id obj -> fun
        if (ft_strcmp((*data)->tab[i], "camera") == 0)
            camera_check(data, i);
        if (ft_strcmp((*data)->tab[i], "sphere") == 0)
            obj_check(data, i, 1);
        if (ft_strcmp((*data)->tab[i], "cylinder") == 0)
            obj_check(data, i, 2);
        if (ft_strcmp((*data)->tab[i], "light") == 0)
            light_check(data, i);
        if(ft_strcmp((*data)->tab[i],"plane") == 0)
            obj_check(data, i, 4);
        if (ft_strcmp((*data)->tab[i], "cone") == 0)
            obj_check(data, i, 5);
        i++;
    }
    return (0);
}

void image_clear(int *d)
{
    int y;
    int x;

    y = 0;
    while (y < HEIGHT)
    {
        x = -1;
        while (x++ < WIDTH)
            d[y * WIDTH + x] = 0x000000;
        y++;
    }
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
    (*data)->camera->fov = 10;
}
/////--------**********************************************************************

int ft_close(void)
{
    exit(1);
    return (0);
}

int keyhook(int key, void *p)
{
    (void)p;
    if (key == 53)
        ft_close();
    return (0);
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

    if (t2 < 0 && t1 < 0)
        return (-1);
    else if (t1 > 0 && t2 < 0)
        t = t1;
    else if (t2 > 0 && t1 < 0)
        t = t2;
    else
        t = fmin(t1, t2);
    return (t);
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
    // /t_vec   dir;
    t_vec horizontal;
    t_vec vertical;
    t_vec cam_u;
    t_vec cam_v;
    t_vec cam_w;
    t_ray new;

    //t_vector ray;
    //camera = NULL;
    u = 2 * (u + 0.5) / (HEIGHT) - 1;
    v = 1 - 2 * (v + 0.5) / (HEIGHT);
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

    //   new.dir = vec_add(dir, camera->cam_dir);
    //   new.start = camera->look_from;
    //   return (new);
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

t_ray       init_rayy(int i, int j, t_camera *cam)
{
    t_vec  s;
    t_ray   r;
    t_vec cam_u;
    t_vec cam_v;
    t_vec cam_w;

    cam_w = normalize(vec_sub(cam->look_from, cam->cam_dir));
    cam_u = normalize(vec_cross(cam->up, cam_w));
    cam_v = vec_cross(cam_w, cam_u);
    s = vec_sub(cam->look_from, vec_product(cam->cam_dir, 2000));
    s = vec_sub(s, vec_product (cam_u, (i - (HEIGHT / 2))));
    s = vec_add(s, vec_product(cam_v, ((HEIGHT / 2) - j)));
    r.dir = vec_sub(s, cam->look_from);
    r.o = cam->look_from;
   r.dir =  normalize((r.dir));
    return (r);
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
    if (t1 < 0 && t2 < 0)
        return 0;
    if (t1 > 0 && t2 > 0)
    {
        if (t1 > t2)
            t = t2;
        else
            t = t1;
    }
    else if ((t1 > 0 && t2 < 0) || (t2 < 0 && t2 > 0))
    {
        if (t1 > t2)
            t = t1;
        else
            t = t2;
    }
    return t;
}

t_vec   light_it_up(t_data *data, int x, int y,t_obj *obj, double t)
{
    t_vec hit;
    t_vec   n;
    t_vec color;
        hit = vec_add(data->ray.o, vec_product(data->ray.dir, t));
    if (obj->id == 2)
    {
        n = vec_sub(vec_sub(hit ,obj->pos), vec_product(obj->axis, dot_product(obj->axis, vec_sub(hit, obj->pos))));
        n = normalize(n);
           double ang_norm_light =  fmax(0,dot_product(normalize(vec_sub(data->light->pos, hit)), n));
                            t_vec L = normalize(vec_sub(data->light->pos, hit));
                            t_vec V = normalize(vec_sub(data->ray.o, hit));
                            t_vec dd = vec_product(n,dot_product(L,n));
                            t_vec Rm = vec_sub(vec_product(dd, 2),L);
                            double ka = 0, kd = 0, ks = 1;
            double intensite_pixel = ka + (kd * ang_norm_light) + (ks *pow(fmax(0, dot_product(Rm,V)),40));
            color.x = obj->color.x * 0.3;
            color.y = obj->color.y * 0.3;
            color.z = obj->color.x * 0.3;
                       color.x =  fmin(255, obj->color.x*ang_norm_light + color.x);
            		    color.y =  fmin(255, obj->color.y*ang_norm_light + color.y);
            			 color.z =  fmin(255, obj->color.z*ang_norm_light + color.z);
                        data->mlx.d[(y * WIDTH + x) + 0] =  (int)color.x << 16 | (int)color.y<< 8 | (int)color.z;
                        color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0]>> 16)&255) + data->light->color.x * intensite_pixel);
                        color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0]>> 8)&255)+data->light->color.y * intensite_pixel);
                        color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] &255) + data->light->color.z * intensite_pixel);
                        if (color.x > 255)
                            color.x = 255;
                             if (color.y > 255)
                            color.y = 255;
                             if (color.z > 255)
                            color.z = 255;
    }
    else if (obj->id == 1)
    {
        n = normalize(vec_sub( hit, obj->pos));
          double ang_norm_light =  fmax(0,dot_product(normalize(vec_sub(data->light->pos, hit)), n));
                            t_vec L = normalize(vec_sub(data->light->pos, hit));
                            t_vec V = normalize(vec_sub(data->ray.o, hit));
                            t_vec dd = vec_product(n,dot_product(L,n));
                            t_vec Rm = vec_sub(vec_product(dd, 2),L);
                            double ka = 0, kd = 0, ks = 1;
            double intensite_pixel = ka + (kd * ang_norm_light) + (ks *pow(fmax(0, dot_product(Rm,V)),40));
            color.x = obj->color.x * 0.3;
            color.y = obj->color.y * 0.3;
            color.z = obj->color.x * 0.3;
                       color.x =  fmin(255, obj->color.x*ang_norm_light + color.x);
            		    color.y =  fmin(255, obj->color.y*ang_norm_light + color.y);
            			 color.z =  fmin(255, obj->color.z*ang_norm_light + color.z);
                        data->mlx.d[(y * WIDTH + x) + 0] =  (int)color.x << 16 | (int)color.y<< 8 | (int)color.z;
                        color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0]>> 16)&255) + data->light->color.x * intensite_pixel);
                        color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0]>> 8)&255)+data->light->color.y * intensite_pixel);
                        color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] &255) + data->light->color.z * intensite_pixel);
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
    while (y < HEIGHT)
    {
        x = -1;
        while (x++ < WIDTH)
        {
            data->ray = get_ray(x, y, data->camera);
                        // data->ray = init_rayy(x, y, data->camera);

            // data->ray.dir.x = x-(HEIGHT/2);
            // data->ray.dir.y = y-(HEIGHT/2);
            // data->ray.dir.z = -WIDTH/(2*tan(alpha));

            t1 = -1;
            head = data->obj;
            while(head)
            {
                t = head->inter(&(data->ray), head);
            	
            	    if ((t < t1 && t1 > 0 && t > 0) || (t > t1 && t1 < 0 && t > 0))
            		{
            			t1 = t;
            			save=head;
            		}
            	head = head->next;
            }

           
             if (t1 > 0 && (save->id == 2 || save->id == 1))
            {
                color = light_it_up(data, x, y, save, t1);
                data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
            }
          

            else if (t1 > 0)
            {
                     data->mlx.d[(y * WIDTH + x) + 0] = (int)save->color.x << 16 | (int)save->color.y << 8 | (int)save->color.z;
            }

        }
        y++;
    }
}

int mouse_move(int x, int y, t_data *data)
{
    double PI = 22 / 7;
    double alpha = 60 * PI / 180;
    data->obj->pos.x = x - (HEIGHT / 2);
    // data->light->pos.y = y - (HEIGHT / 2);

    // data->lum_pos.z = ;
    // data->sphere->c.z -= 10;
    image_clear(data->mlx.d);
    ray_tracer(data);
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img, 0, 0);
    return 1;
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
    // printf("here %d", data->obj->next->next->id);
    int bpp;
    t_mlx f;

      f.ptr = mlx_init();
      f.win = mlx_new_window(f.ptr, WIDTH, HEIGHT, "RTV1");
      mlx_hook(f.win,17,0,ft_close,&data);
      mlx_hook(f.win, 2,0,keyhook,data);
      f.img = mlx_new_image(f.ptr,WIDTH,HEIGHT);
      f.d   = (int *)mlx_get_data_addr(f.img, &bpp, &bpp, &bpp);
      data->mlx = f;
    debugstr("CHECK",1);
    ray_tracer(data);
    mlx_put_image_to_window(f.ptr, f.win, f.img,0 ,0);
     mlx_loop(f.ptr);
    return (0);
}
