
#include "mlx.h"
void circleBres(int *dd,int xc, int yc, int r) 
{ 
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    //
    dd[y * WIDTH + x] = 0x0ff000;
    while (y >= x) 
    { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
       // drawCircle(xc, yc, x, y); 
        dd[y * WIDTH + x] = 0x0ff000;
    } 
} 
int         intersection_sphere(t_sphere sphere, t_ray ray)
{

}
// void		draw_circle(t_data)
// {
// 	int	y;
// 	int x;
//     int res;
//     double PI = 22 / 7;
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = -1;
// 		while (x++ < WIDTH)
//         {

// 			res = (((x*x) - (2 * center_x*x) + (center_x * center_x)) + ((y*y) - (2 * center_y*y) + (center_y * center_y)));
//           if( res <= radius*radius && res >= 0)
//                 d[y * WIDTH + x] = 0x000ff0;
//         }
// 		y++;
// 	}
// }
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
