/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:54:06 by ramoukha          #+#    #+#             */
/*   Updated: 2021/01/08 18:33:45 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


void	debugstr(char *str, int nl)
{
	ft_putstr_fd("|",1);
	ft_putstr_fd(str,1);
	ft_putstr_fd("|",1);
	if (nl)
  ft_putendl_fd("",1);
}
void	debugnbr(int nbr, int nl,int fd)
{
	//ft_putstr_fd(tgetstr("cl", NULL),2);
	ft_putstr_fd("|",fd);
	ft_putnbr_fd(nbr,fd);
	ft_putstr_fd("|",fd);
	if (nl)
		ft_putendl_fd("",fd);
}

float	mot2(float A, float B)
{
	return ((A * A)- (2 + A * B) + (B * B));
}

float	dot_product(t_vec A, t_vec B)
{	
    float ret = (A.x * B.x) + (A.y * B.y) + (A.z * B.z);

	return (ret);
}
float	dot_pro(double n, t_vec A)
{	
	return (A.x * n + A.y * n+ A.z * n);
}

t_vec  vec_sub(t_vec A, t_vec B)
{
    t_vec ret = {(A.x - B.x) , (A.y - B.y) , (A.z - B.z)};
    return (ret);
}

void	normalize(t_vec *vec)
{
	t_vec tmp;

	tmp.x = vec->x;
	tmp.y = vec->y;
	tmp.z = vec->z;
	vec->x = tmp.x/sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
	vec->y = tmp.y/sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
	vec->z = tmp.z/sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
}

int		 intersection_sphere(t_data *data)
{
    //         debugnbr(y,1,1);
	float a = dot_product(data->ray.d,data->ray.d);
    float b = 2 * dot_product(data->ray.d, vec_sub(data->ray.o, data->sphere->c));
    float c = dot_product(vec_sub(data->ray.o, data->sphere->c) , vec_sub(data->ray.o, data->sphere->c)) - (data->sphere->r * data->sphere->r);
    float L = b*b - (4*a*c);
    // printf("\ngood = %lf| bad = %lf",aa,a);
    if (L< 0)
        return 0;
    return 1;
}


void    circle_calc(t_data *data)
{
    //float   line;
    int	y;
	int x;
    //int res;
    double PI = 22 / 7;
    double alpha = 60 * PI/180;
	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
        {
            data->ray.d.x = x-(HEIGHT/2);
            data->ray.d.y = y-(HEIGHT/2);
            data->ray.d.z = -WIDTH/(2*tan(alpha));
            normalize(&data->ray.d);
            if (intersection_sphere(data))
               data->d[y * WIDTH + x] = 0xff21ff;
        }
		y++;
	}
}








int main()
{
    t_data	*data;
	int		bpp;
    t_vec source = {0,0,0};
      t_vec s = {50,50,-200};
      //t_vec target = {80,50,0};
      t_sphere *sphere;
     sphere = (t_sphere *)malloc(sizeof(t_sphere));
    sphere->c = s;
    sphere->r = 30;
      //debugnbr(sphere->c.x,1,1);
    data = (t_data *)malloc(sizeof(t_data));
    data->sphere = sphere;
    //ebugstr("OFFFF",1);

	data->ray.o = source;
	//data->ray.d = target;

    data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, WIDTH, HEIGHT, "ok");
	data->img = mlx_new_image(data->ptr, WIDTH, HEIGHT);
	data->d = (int *)mlx_get_data_addr(data->img, &bpp, &bpp, &bpp);
    circle_calc(data);
    //image_clear(data->d, 200,200,100);
    mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
    mlx_loop(data->ptr);
}