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

float ft_deg_to_rad(float angle){
  return (angle * M_PI) / 180;
}

t_object ft_create_sphere(t_vector pos, t_vector trans, t_vector rot, float radius, t_color color){
    t_object sphere;

    sphere.pos = pos;
    sphere.trans = trans;
    sphere.rot = rot;
    sphere.radius = radius;
    sphere.color = color;
    sphere.type = SPHERE;
    return sphere;
}


t_object ft_create_cone(t_vector pos, t_vector trans, t_vector rot, t_vector axis, float angle, t_color color){
    t_object cone;

    cone.pos = pos;
    cone.trans = trans;
    cone.rot = (t_vector){ft_deg_to_rad(rot.x), ft_deg_to_rad(rot.y), ft_deg_to_rad(rot.z)};
    cone.axis = axis;
    cone.angle = ft_deg_to_rad(angle);
    cone.color = color;
    cone.type = CONE;
    return cone;
}

t_object *ft_create_object( t_object object)
{
    t_object *o;

    if ((o = (t_object *) malloc(sizeof(t_object)))){
        o->pos = object.pos;
        o->trans = object.trans;
        o->rot = object.rot;
        o->axis = object.axis;//Dont forget to add normal for plane
        o->radius = object.radius;
        o->angle = object.angle;
        o->color = object.color;
        o->type = object.type;
        o->next = NULL;
    }
    return o;
}

void ft_add_object(t_object **lst, t_object *new){
    t_object *p;
    if (!new || !lst){
        return ;
    }
    if (!*lst){
        *lst = new;
    }else{
        p = *lst;
        while (p->next)
        {
            p = p->next;
        }
        p->next = new;
    }
}

void ft_clear_object(t_object **lst){
    t_object *p;

    p = *lst;
    while (p){
        *lst = (*lst)->next;
        free(p);
        p = *lst;
    }
}