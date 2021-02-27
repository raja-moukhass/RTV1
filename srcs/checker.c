/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:17:33 by ramoukha          #+#    #+#             */
/*   Updated: 2021/02/27 14:20:32 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_checker(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->tab[i])
	{
		if (ft_strcmp((*data)->tab[i], "camera") == 0)
			camera_check(data, i);
		if (ft_strcmp((*data)->tab[i], "sphere") == 0)
			obj_check(data, i, 1);
		if (ft_strcmp((*data)->tab[i], "cylinder") == 0)
			obj_check(data, i, 2);
		if (ft_strcmp((*data)->tab[i], "light") == 0)
			light_check(data, i);
		if (ft_strcmp((*data)->tab[i], "plane") == 0)
			obj_check(data, i, 4);
		if (ft_strcmp((*data)->tab[i], "cone") == 0)
			obj_check(data, i, 5);
		i++;
	}
	return (0);
}

int		init_obj(t_obj *temp, int i, t_data *data, int id)
{
	temp->id = id;
	temp->pos = split_data(data, data->tab[++i]);
	temp->trans = split_data(data, data->tab[++i]);
	temp->rot = split_data(data, data->tab[++i]);
	temp->color = split_data(data, data->tab[++i]);
	if (id != 4)
		temp->an_ra = ft_atof(ft_strdup(data->tab[++i]));
	if (id != 1)
	{
		temp->axis = split_data(data, data->tab[++i]);
		temp->axis = ft_transform_ray(temp);
	}
	return (i);
}

void	obj_check(t_data **dat, int i, int id)
{
	int		check;
	t_obj	*temp;
	t_data	*data;

	data = *dat;
	check = 1;
	while (data->tab[i + check] && check < 4)
		check++;
	if (check != 4)
		call_error(data);
	temp = add_node(dat);
	i = init_obj(temp, i, data, id);
	if (id == 1)
		temp->inter = &intersection_spher;
	else if (id == 2)
		temp->inter = &intersection_cylinder;
	else if (id == 4)
		temp->inter = &intersect_plane;
	else if (id == 5)
		temp->inter = &cone_intersection;
}

void	camera_check(t_data **dat, int i)
{
	int		check;
	t_data	*data;

	data = *dat;
	check = 1;
	while (data->tab[i + check] && check < 3)
		check++;
	if (check != 3)
		call_error(data);
	data->camera->look_from = split_data(data, data->tab[i + 1]);
	data->camera->cam_dir = split_data(data, data->tab[i + 2]);
}

void	light_check(t_data **dat, int i)
{
	int		check;
	t_data	*data;

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
