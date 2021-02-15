/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv1in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rv1moukhv1 <rv1moukhv1@student.42.fr>          +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:54:06 by ramoukha          #+#    #+#             */
/*   Updated: 2021/01/10 16:45:11 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rtv1.h"

t_vector ft_rotate_x(t_vector v, float angle){
  t_vector res;

  res.x = v.x;
  res.y = v.y * cos(angle) + v.z * sin(angle);
  res.z = - v.y * sin(angle) + v.z * cos(angle);
      return res;
}

t_vector ft_rotate_y(t_vector v, float angle){
  t_vector res;
  res.y = v.y;
  res.x = v.x * cos(angle) + v.z * sin(angle);
  res.z = - v.x * sin(angle) + v.z * cos(angle);
      return res;

}


t_vector ft_rotate_z(t_vector v, float angle){
  t_vector res;


  res.z = v.z;
  res.x = v.x * cos(angle) - v.y * sin(angle);
  res.y = v.x * sin(angle) + v.y * cos(angle);
    return res;
}

t_vector ft_rotate(t_vector v, t_vector rot){
  t_vector res;

  res = ft_rotate_x(v, rot.x);
  res = ft_rotate_y(res, rot.y);
  res = ft_rotate_z(res, rot.z);
  return res;
}

t_vector ft_translate(t_vector v, t_vector trans){
  t_vector res;

  res.x = v.x + trans.x;
  res.y = v.y + trans.y;
  res.z = v.z + trans.z;
  return res;
}
