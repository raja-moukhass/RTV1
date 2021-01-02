/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:54:06 by ramoukha          #+#    #+#             */
/*   Updated: 2021/01/02 12:26:39 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
#include <stdbool.h>

t_vector	vectorsub(t_vector *v1, t_vector *v2)
{
	t_vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
	return(result);
}

int main()
{
  t_mlx f;
  
  f.ptr = mlx_init();
  f.win = mlx_new_window(f.ptr, 500, 500, "Title");
  mlx_loop(f.ptr);
  
  return (0);
}

//  /* Needed for boolean datatype */


// /* The vector structure */
// typedef struct{
//       float x,y,z;
// }vector;

// /* The sphere */
// typedef struct{
//         vector pos;
//         float  radius;
// }sphere; 

// /* The ray */
// typedef struct{
//         vector start;
//         vector dir;
// }ray;

// /* Subtract two vectors and return the resulting vector */
// vector vectorSub(vector *v1, vector *v2){
// 	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
// 	return result;
// }

// /* Multiply two vectors and return the resulting scalar (dot product) */
// float vectorDot(vector *v1, vector *v2){
// 	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
// }


// /* Check if the ray and sphere intersect */
// bool intersectRaySphere(ray *r, sphere *s){
	
// 	/* A = d.d, the vector dot product of the direction */
// 	float A = vectorDot(&r->dir, &r->dir); 
	
// 	/* We need a vector representing the distance between the start of 
// 	 * the ray and the position of the circle.
// 	 * This is the term (p0 - c) 
// 	 */
// 	vector dist = vectorSub(&r->start, &s->pos);
	
// 	/* 2d.(p0 - c) */  
// 	float B = 2 * vectorDot(&r->dir, &dist);
	
// 	/* (p0 - c).(p0 - c) - r^2 */
// 	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
	
// 	/* Solving the discriminant */
// 	float discr = B * B - 4 * A * C;
	
// 	/* If the discriminant is negative, there are no real roots.
// 	 * Return false in that case as the ray misses the sphere.
// 	 * Return true in all other cases (can be one or two intersections)
// 	 */
// 	if(discr < 0)
// 		return false;
// 	else
// 		return true;
// }


// int main(){
	
// 	/* Our ray and a sphere */
// 	sphere s;
// 	ray r;
	
// 	/* x, y for screen 'resolution' */
// 	int x,y;	

// 	/* Intersect ray/sphere or not */
// 	bool hit;

// 	/* Position the sphere */
// 	s.pos.x = 20;
// 	s.pos.y = 20;
// 	s.pos.z = 20;

// 	/* Sphere radius */
// 	s.radius = 10;

// 	/* Direction of the ray */
// 	r.dir.x = 0;
// 	r.dir.y = 0;
// 	r.dir.z = 1;

// 	/* Start position of the ray, z coordinate */
// 	r.start.z = 0;

// 	/* Iterate over every 'pixel' of our screen
// 	 * We use a 40x40 virtual ASCII screen for now
// 	 */
// 	for(y=0;y<40;y++){
// 		/* Set the y-coordinate of the start position of the ray */
// 		r.start.y = y; 
// 		for(x=0;x<40;x++){
// 			/* Set the x-coordinate of the start position of the ray */
// 			r.start.x = x;

// 			/* Check if the ray intersects with the shpere */
// 			hit = intersectRaySphere(&r, &s);
// 			if(hit)
//       {
      
// 				printf("++");
//         mlxinit();
        
//       }
// 			else
// 				printf("--");
// 		}
    
// 		/* First row of the screen done, move to next row */
// 		printf("\n");
// 	}

// }