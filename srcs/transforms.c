/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv1in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rv1moukhv1 <rv1moukhv1@student.42.fr>          +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:54:06 by ramoukha          #+#    #+#             */
/*   Updated: 2021/02/18 15:50:26 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rtv1.h"

t_vec ft_rotate_x(t_vec v, double angle){
	t_vec res;

	res.x = v.x;
	res.y = v.y * cos(angle) + v.z * sin(angle);
	res.z = - v.y * sin(angle) + v.z * cos(angle);
	return res;
}

t_vec ft_rotate_y(t_vec v, double angle){
	t_vec res;
	res.y = v.y;
	res.x = v.x * cos(angle) + v.z * sin(angle);
	res.z = - v.x * sin(angle) + v.z * cos(angle);
	return res;

}

t_ray   *ft_transform_ray(t_ray *ray, t_obj *o){
	t_vec rot;
	t_vec trans;

	rot = (t_vec){-o->rot.x, -o->rot.y, -o->rot.z};
	trans = (t_vec){-o->trans.x, -o->trans.y, -o->trans.z};

	ray->o = ft_rotate(ray->o, rot);
	ray->o = ft_translate(ray->o, trans);
	ray->dir = ft_rotate(ray->dir, rot);
	return ray;
}

t_vec ft_rotate_z(t_vec v, double angle){
	t_vec res;


	res.z = v.z;
	res.x = v.x * cos(angle) - v.y * sin(angle);
	res.y = v.x * sin(angle) + v.y * cos(angle);
	return res;
}

t_vec ft_rotate(t_vec v, t_vec rot){
	t_vec res;

	res = ft_rotate_x(v, rot.x);
	res = ft_rotate_y(res, rot.y);
	res = ft_rotate_z(res, rot.z);
	return res;
}

t_vec ft_translate(t_vec v, t_vec trans){
	t_vec res;

	res.x = v.x + trans.x;
	res.y = v.y + trans.y;
	res.z = v.z + trans.z;
	return res;
}
