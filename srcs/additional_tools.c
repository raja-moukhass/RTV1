#include "rtv1.h"


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
