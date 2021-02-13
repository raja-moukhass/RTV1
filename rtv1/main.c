#include "rtv1.h"

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
    //ft_putstr_fd(tgetstr("cl", NULL),2);
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
    // assuming vectors are all normalized
    float denom = dot_product(plane->axis, r->dir); 
    if (denom == 0 || (denom > 0 &&  nomin > 0) ||  (denom < 0 &&  nomin < 0) ) 
        return 0;

    t = -nomin / denom; 
    //     // if (t > 0.0)
    // printf("%f\n",t);
    // // if (t > 0)
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

}
// void		cone_check(t_data **dat, int i)
// {
// 	int			check;
// 	t_cone		*temp;
// 	t_data		*data;

// 	data = *dat;
// 	check = 1;
// 	while(data->tab[i + check] && check < 5)
// 		check++;
// 	if (check != 5)
// 	{
// 		call_error(data);
// 	}
// 	add_node(dat);
// 	temp = data->cone;
// 	while(temp->next)
// 		temp = temp->next;
// 	temp->pos = split_data(data,data->tab[i + 1]);
// 	temp->trans = split_data(data,data->tab[i + 2]);
// 	temp->rot = split_data(data,data->tab[i + 3]);
// 	temp->color = split_data(data,data->tab[i + 4]);
// 	temp->angle = ft_strdup(data->tab[i + 5]);

// }
// void		cylinder_check(t_data **dat, int i)
// {
// 	int			check;
// 	t_cylinder		*temp;
// 	t_data		*data;

// 	data = *dat;
// 	check = 1;
// 	while(data->tab[i + check] && check < 5)
// 		check++;
// 	if (check != 5)
// 	{
// 		call_error(data);
// 	}
// 	add_node(dat,3);

// 	temp = data->cylinder;
// 	while(temp->next)
// 		temp = temp->next;
// 	temp->pos = split_data(data,data->tab[i + 1]);
// 	temp->trans = split_data(data,data->tab[i + 2]);
// 	temp->axis = split_data(data,data->tab[i + 3]);
// 	temp->rot = split_data(data,data->tab[i + 4]);
// 	temp->color = split_data(data,data->tab[i + 5]);
// 	temp->angle = ft_atof(ft_strdup(data->tab[i + 6]));

// }
// /*
// fun
// while (table[i])
// {
//     if (strcm(spher) || strcm(sphplan) ...)
//         {
//             pars(obj)
//             aloc next
//             obje -next;
//         }
// }

// fun raytracing
// t1 = -1;
// pos = head;
// while (head)
// {
//     t = inter(obj, ray);
//     if (t != -1)
//     {
//         if (t1 == -1)
//         {
//             t1 = t;
//             pos = head;
//         }
//         else
//         {
//             if (t < t1)
//             {
//                 t1 = t;
//                 pos = head;
//             }
//         }
//     }
//     head++
// }
// t closet one
// pos (obj) closet;
// pos->t = t1;
// return (pos);
// */
// void		plane_check(t_data **dat, int i)
// {
// 	int			check;
// 	t_plane		*temp;
// 	t_data		*data;
// 	data = *dat;
// 	check = 1;
// 	while(data->tab[i + check] && check < 4)
// 		check++;
// 	if (check != 4)
// 	{
// 		call_error(data);
// 	}
// 	add_node(dat,4);
// 	ft_putstr("here");

// 	temp = data->plane;
// 	while(temp->next)
// 		temp = temp->next;
// 	temp->pos = split_data(data,data->tab[i + 1]);
// 	temp->trans = split_data(data,data->tab[i + 2]);
// 	temp->axis = split_data(data,data->tab[i + 3]);
// 	temp->rot = split_data(data,data->tab[i + 4]);
// 	temp->color = split_data(data,data->tab[i + 5]);

// }
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
    (*data)->camera->fov = 60;
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
    double a = dot_product(r->dir, r->dir);
    double t1;
    double t2;

    t_vec dist = vec_sub(r->o, s->pos);
    //printf("(%lf, %lf, %lf)\n", dist.x, dist.y, dist.z);
    double b = 2 * dot_product(r->dir, dist);
    double c = dot_product(dist, dist) - (s->an_ra * s->an_ra);
    //printf("\na = %lf b = %lf c = %lf", a,b,c);
    double discr = b * b - 4 * a * c;
    if (discr < 0)
        return -1;
    else
    {
        t1 = (-b - sqrtf(discr)) / 2 * a;
        t2 = (-b + sqrtf(discr)) / 2 * a;
    }
    if (t1 > 0 && t1 < t2)
        return (t1);
    else if (t2 > 0)
        return (t2);
    return -1;
}
t_vec get_camera_direction(t_camera cam, t_vec get_ray)
{
    t_vec ray;
    cam.low_left_corner = vec_add(cam.look_from, get_ray);
    ray = vec_sub(cam.low_left_corner, cam.look_from);
    return ray;
}

// void    ft_camera(t_camera *cam, t_vec vup , double aspect)
// {
//   t_vec i;
//   t_vec j;
//   t_vec k;

// //   new.dir = vec_add(dir, camera->cam_dir);
// //   new.start = camera->look_from;
// //    return (new);

//   double  half_h;
//   double  half_w;

//   half_h = tan((cam->fov * M_PI /180) / 2);
//   half_w = aspect * half_h;
//   i = normalize(vec_product(cam->cam_dir,-1));
//   j = normalize(vec_cross(vup,i));
//   k = vec_cross(i,j);
//   cam->low_left_corner.x = cam->look_from.x - half_w * j.x - half_h * k.x - i.x;
//   cam->low_left_corner.y = cam->look_from.y - half_w * j.y - half_h * k.y - i.y;
//   cam->low_left_corner.z = cam->look_from.z - half_w * j.z - half_h * k.z - i.z;
//   cam->hotizontal = vec_product(j, 2 *half_w);
//   cam->vertical = vec_product(k, 2 * half_h);

// }

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
    u = 2 * (u + 0.5) / (HEIGHT - 1) - 1;
    v = 1 - 2 * (v + 0.5) / (HEIGHT - 1);
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
// void  sphere_calculation(t_data **data)
// {
//     int x;
//     int y = 0;
//     double hit;
//     t_sphere s;
//     t_ray r;

//     t_material materials;
//     materials.diffuse.red = 1;
//     materials.diffuse.green = 0;
//     materials.diffuse.blue = 0;
//     materials.reflection = 0.2;

//     t_light lights;
//     lights.pos.x = 0;
//     lights.pos.y = 0;
//     lights.pos.z = -100;

//     lights.intensity.red = 1;
//     lights.intensity.blue = 1;
//     lights.intensity.green =1;

//     //double t = 20000.0f;
//     s.pos.x = 0;
//     s.pos.y = 0;
//     s.pos.z = 0;

//     s.radius = 1;

//     t_camera cam;
//     //init camera
//     cam.look_from = (t_vec){0, 5, 0};
//     cam.cam_dir = (t_vec){0, 0, 0};
//     cam.up = (t_vec){0, 1, 0};
//     cam.fov = 60;
//     while (y < HEIGHT)
//     {
//       r.dir.y = y-(WIDTH/2);
//       x = 0;

//       while(x < WIDTH)
//       {
//         //r.dir.x = x-(WIDTH/2);
//         //r.dir.z =  -WIDTH/(2*tan(alpha));
//         //map x and y between -1 < < 1;
//         r = get_ray(x, y, &cam);
//         hit = intersection(&r,&s);
//         if (hit >= 0)
//         {
//           t_vec hits;
//           hits = vec_add(r.start, vec_product((r.dir), hit));

//           t_vec nr = normalize(vec_sub(hits, s.pos));
//           t_vec ldir = normalize(vec_sub((t_vec){-200,10,0}, hits));
//           //t_vec refl = normalize(vec_add(ldir, r.dir));
//           double dot = dot_product(nr, ldir);
//           t_color rgb;
//          // printf("%lf", dot);
//           rgb = (t_color){1,1,1};
//           rgb.red = ((rgb.red) * dot);
//           rgb.green = ((rgb.green) * dot);
//           rgb.blue = ((rgb.blue) * dot);
//           if (rgb.red > 1.0)
//             rgb.red = 1.0;
//           if (rgb.green > 1.0)
//             rgb.green = 1.0;
//           if (rgb.blue > 1.0)
//             rgb.blue = 1.0;
//           int color = (((int)(rgb.red*255) << 16) | ((int)(rgb.green*255) << 8) | (int)((rgb.blue*255)));
//           //int color = 0xff;
//           if (dot >= 0)
//           {
//             data->mlx.d[y*WIDTH + x] = color;

//           }
//           else

//           {
//             data->mlx.d[y*WIDTH + x] = 0;

//           }
//           //data->mlx.d[y*WIDTH + x] = 0xff;

//         }
//         x++;
//       }
//       y++;
//     }
// }

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

// int		 intersection_sphere(t_data *data, t_vec *p, t_vec *n)
// {
//     //         debugnbr(y,1,1);
// 	double a = dot_product(data->ray.dir,data->ray.dir);
//     double b = 2 * dot_product(data->ray.dir, vec_sub(data->ray.o, data->sphere->pos));
//     double c = dot_product(vec_sub(data->ray.o, data->sphere->pos) , vec_sub(data->ray.o, data->sphere->pos)) - (data->sphere->radius * data->sphere->radius);

//     double delta = b*b - (4*a*c);
//     double t1;
//     double t2;
//     if (delta< 0)
//         return 0;
//      t1 = (-b - sqrt(delta))/(2*a);
//      t2 = (-b + sqrt(delta))/(2*a);
//     double t;
//    if (t1 < 0 && t2 < 0)
// 	return 0;
//    if (t1 > 0 && t2 > 0)
//    {
// 	   if (t1 > t2 )
// 		t = t2;
// 		else
// 		t = t1;
// 		}
// 		else if ( (t1 > 0 && t2 < 0) ||( t2 < 0 && t2 >0))
// 		{
// 			if (t1 > t2)
// 				t = t1;
// 			else
// 				t = t2;
// 		}

//     // if (delta == 0)
//     //  t1 = -b /2*a;

//     //printf("\ngood = %deltaf| bad = %deltaf",tonorm.x, n->x);
//     *p = vec_add(data->ray.o, vec_product(data->ray.dir, t));
//     t_vec tonorm = vec_sub( *p, data->sphere->pos);
//     *n = normalize(tonorm);
//     return 1;
// }

double intersection_cylinder(t_ray *ray, t_obj *cylinder)
{
    //         debugnbr(y,1,1);
    // n = 0;
    // l = vector_sub(ray->origin, cylinder->transform.position);
    // tmp[0] = vector_dot(ray->direction, cylinder->transform.rotation);
    // tmp[1] = vector_dot(l, cylinder->transform.rotation);
    // var.x = vector_dot(ray->direction, ray->direction) - pow(tmp[0], 2);
    // var.y = 2 * (vector_dot(ray->direction, l) - (tmp[0] * tmp[1]));
    // var.z = vector_dot(l, l) - pow(tmp[1], 2) -
    // 		pow(cylinder->shape.radius, 2);
    t_vec delta_p = vec_sub(ray->o, cylinder->pos);
    // delta_p = normalize(delta_p);
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

    // printf("%f \n",t);

    // if (delta == 0)
    //  t1 = -b /2*a;

    //printf("\ngood = %deltaf| bad = %deltaf",tonorm.x, n->x);

    // *p = vec_add(data->ray.o, vec_product(data->ray.dir, t));
    // t_vec tonorm = vec_sub(vec_sub(*p,data->cylinder->pos), vec_product(data->cylinder->axis, dot_product(data->cylinder->axis, vec_sub(*p, data->cylinder->pos))));
    // // t_vec tonorm = sub3(dot_product(dot_vec(data->cylinder->axis, vec_sub(data->cyl->o, *p)), data->cylinder->axis), vec_sub( data->cyl->o, *p));

    // *n = normalize(tonorm);

    return t;
}

t_vec   light_it_up(t_data *data, int x, int y,t_obj *obj, double t)
{
    t_vec hit;
    t_vec   n;
    t_vec color;
    if (obj->id == 2)
    {
        hit = vec_add(data->ray.o, vec_product(data->ray.dir, t));
        t_vec tonorm = vec_sub(vec_sub(hit ,obj->pos), vec_product(obj->axis, dot_product(obj->axis, vec_sub(hit, obj->pos))));
        n = normalize(tonorm);
           double ang_norm_light =  fmax(0,dot_product(normalize(vec_sub(data->light->pos, hit)), n));
                            t_vec L = normalize(vec_sub(data->light->pos, hit));
                            t_vec V = normalize(vec_sub(data->ray.o, hit));
                            t_vec dd = vec_product(n,dot_product(L,n));
                            t_vec Rm = vec_sub(vec_product(dd, 2),L);
                            double ka = 0, kd = 0.6, ks = 1;
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
    // int intensite_lum =  ;
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

            /*
                function return color ---->get color function shadow
                get_color{
                    funtion sp amp def --color
                    init ray (hit . position light)
                    col = shadow (ray , data)
                }
                shadow (){
                    while(head)
            {
                t = head->inter(&(data->ray), head);
            	
            	    if ((t < t1 && t1 > 0 && t > 0) || (t > t1 && t1 < 0 && t > 0))
            		{
                        return (col.x *0.6 ...)
            		}
            	head = head->next;
            }
            }
            */
            // head = head->next;
            // printf("%f", head->pos.z);
            // if (head)
            // save = head;
            // save->t = t1;
            // t1 = data->obj->inter(&(data->ray), head);
            if (t1 > 0 && save->id == 2)
            {
                color = light_it_up(data, x, y, save, t1);
                data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
            }
            else if (t1 > 0)
                data->mlx.d[(y * WIDTH + x) + 0] = (int)save->color.x << 16 | (int)save->color.y << 8 | (int)save->color.z;

            // init ray;
            // t = func _ find _ close(data , ray);
            // t_vect col = get color(t , id/pos);
            //get color (color -- > lighting -- > shadow);
            //shadow (ray -- >  - ligght position - hit position);
            //interse all objects
            //color
            //print color

                    //    if (intersect_plane(&(data->ray), head)>0)
                    //        data->mlx.d[(y * WIDTH + x) + 0] = (int)save->color.x << 16 | (int)save->color.y << 8 | (int)save->color.z;

            //    double ang_norm_light =  fmax(0,dot_product(normalize(vec_sub(data->light->pos, p)), data->var.n));
            //                 L = normalize(vec_sub(data->light->pos, p));
            //                 V = normalize(vec_sub(data->ray.o, p));
            //                 t_vec dd = vec_product(data->var.n,dot_product(L,data->var.n));
            //                 t_vec Rm = vec_sub(vec_product(dd, 2),L);
            //                 double ka = 0, kd = 0.6, ks = 1;
            // double intensite_pixel = ka + (kd * ang_norm_light) + (ks *pow(fmax(0, dot_product(Rm,V)),40));
            // dif.x = data->cylinder->color.x * 0.3;
            // dif.y = data->cylinder->color.y * 0.3;
            // dif.z = data->cylinder->color.x * 0.3;
            //            color.x =  fmin(255, data->cylinder->color.x*ang_norm_light + dif.x);
            // 		    color.y =  fmin(255, data->cylinder->color.y*ang_norm_light + dif.y);
            // 			 color.z =  fmin(255, data->cylinder->color.z*ang_norm_light + dif.z);
            //             data->mlx.d[(y * WIDTH + x) + 0] =  (int)color.x << 16 | (int)color.y<< 8 | (int)color.z;
            //             color.x = (int)(((data->mlx.d[(y * WIDTH + x) + 0]>> 16)&255) + data->light->color.x * intensite_pixel);
            //             color.y = (int)(((data->mlx.d[(y * WIDTH + x) + 0]>> 8)&255)+data->light->color.y * intensite_pixel);
            //             color.z = (int)((data->mlx.d[(y * WIDTH + x) + 0] &255) + data->light->color.z * intensite_pixel);
            //             if (color.x > 255)
            //                 color.x = 255;
            //                  if (color.y > 255)
            //                 color.y = 255;
            //                  if (color.z > 255)
            //                 color.z = 255;
            //                                   data->mlx.d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;

            // }
        }
        y++;
    }
}

int mouse_move(int x, int y, t_data *data)
{
    double PI = 22 / 7;
    double alpha = 60 * PI / 180;
    data->light->pos.x = x - (HEIGHT / 2);
    data->light->pos.y = y - (HEIGHT / 2);

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
        //   mlx_hook(data->mlx.win, 6, 0, mouse_move, data);
      mlx_loop(f.ptr);
    // printf("\ncamera:\n\tsource|%s|%s|%s|\n\ttarget|%s|%s|%s|\nsphere:\n\tposition|%s|%s|%s|\n\ttranslation",data->cylinder->pos,data->camera->source[1],data->camera->source[2],data->camera->target[0],data->camera->target[1],data->camera->target[2],data->sphere->next->pos[0],data->sphere->pos[1],data->cone->angle);
    return (0);
}
