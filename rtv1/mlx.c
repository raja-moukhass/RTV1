

#include "mlx.h"


void    circle_calc(t_data *data)
{
    float   line;
    int	y;
	int x;
    int res;
    double PI = 22 / 7;
	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
        {
            data->ray->
        }
		y++;
	}

    
}

int main()
{
    t_data	*data;
	int		bpp;
    t_point source = {0,50,0};
    t_point target = {80,50,0};

    data = (t_data *)malloc(sizeof(t_data));
	data->cam_s = source;
    data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, WIDTH, HEIGHT, "ok");
	data->img = mlx_new_image(data->ptr, WIDTH, HEIGHT);
	data->d = (int *)mlx_get_data_addr(data->img, &bpp, &bpp, &bpp);
    render_circle(data);
    //image_clear(data->d, 200,200,100);
    mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
    mlx_loop(data->ptr);

}
