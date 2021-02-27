/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <moukhassraja@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 09:43:51 by ramoukha          #+#    #+#             */
/*   Updated: 2021/02/27 09:56:16 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		keyhook(int key, void *p)
{
	(void)p;
	if (key == 53)
	ft_close();
	return (0);
}

int		ft_close(void)
{
	exit(1);
	return (0);
}

void	call_error(t_data *data)
{
	ft_putstr("parsing error");
	exit(1);
}

void	image_clear(int *d)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		d[y * WIDTH + x] = 0x000000;
		y++;
	}
}

t_obj	*add_node(t_data **dat)
{
	int		i;
	t_obj	*temp;
	t_obj	*p;

	i = 1;
	t_data *data = *dat;

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

int		ft_lines(int fd)
{
	char	*line = NULL;
	int		count;
	
	count = 0;
	while (get_next_line(fd, &line))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}
