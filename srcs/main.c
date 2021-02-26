#include "rtv1.h"


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

int		get_closest(t_data *data, int x, int y, t_obj **save)
{
	int		t1;
	int		t;
	t_obj	*head;

	data->ray = get_ray(x, y, data->camera);
	t1 = -1;
	head = data->obj;
	while (head)
	{
		t = head->inter(&(data->ray), head);
		if ((t <= t1 && t1 > 0 && t > 0) || (t >= t1 && t1 < 0 && t > 0))
		{
			t1 = t;
			*save = head;
		}
		head = head->next;
	}
	return (t1);
}

void		get_shadow(t_obj *head, t_ray shadow, t_obj *save, t_data *data, t_vec *color)
{
	double	t;
	double	len1;
	double	len2;

	while (head)
	{
		t = head->inter(&(shadow), head);
			if (t > 0 && save != head)
			{
				t_vec hit2 = vec_add(shadow.o, vec_product(shadow.dir, t));
				len1 = dot_product(vec_product(shadow.dir, t), vec_product(shadow.dir, t));
				len2 = dot_product(vec_sub(data->hit, data->light->pos), vec_sub(data->hit, data->light->pos));
				if (len1 < len2)
				{
					
					color->x =  color->x * 0.6;
					color->y = color->y * 0.6;
					color->z = color->z * 0.6;
					break;
				}
			}
			head = head->next;
	}
}

void ray_tracer(t_data *data)
{
    t_raytracer v;
	
    v.y = -1;
    while (++v.y < HEIGHT)
    {
        v.x = -1;
        while (v.x++ < WIDTH)
        {
           v.t1 = get_closest(data, v.x, v.y, &(v.save));
            if (v.t1 != -1)
            {
				v.color = light_it_up(data, v.x, v.y, v.save, v.t1);
                data->hit = vec_add(data->ray.o, vec_product(data->ray.dir, v.t1));
                v.shadow.o = data->light->pos;
                v.shadow.dir = normalize(vec_sub(data->hit, data->light->pos));
                v.head = data->obj;
                get_shadow(v.head,v.shadow, v.save, data, &(v.color));
                data->mlx.d[(v.y * WIDTH + v.x)] = (int)v.color.x << 16 
				| (int)v.color.y << 8 | (int)v.color.z;
            }
        }
    }
}

int mouse_move(int x, int y, t_data *data)
{
    
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
        data->camera->look_from.x -= key == 123 ? 40 : 0;
        data->camera->look_from.x += key == 124 ? 40 : 0;
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
    mlx_put_image_to_window(f.ptr, f.win, f.img, 0, 0);
    mlx_loop(f.ptr);
    return (0);
}
