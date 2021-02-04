
#include "mlx.h"
#include "libft/libft.h"


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

double	mot2(double A, double B)
{
	return ((A * A)- (2 + A * B) + (B * B));
}
// int		 intersection_sphere2(t_data *data,int x, int y)
// {
//     //         debugnbr(y,1,1);
// 	double L = sqrt(mot2(data->sphere->c.x, data->ray.s.x) + mot2(data->sphere->center.y, data->ray.s.y) );
// 	double tc = (L * data->ray.t.x)+ (L * data->ray.t.y)+(L * data->ray.t.z);
// 	if ( tc < 0.0 ) 
// 		return 0;
// 		double d = sqrt((tc*tc) - (L*L));
// 		if ( d > data->sphere->r) 
// 		return 0;
// 		double t1c = sqrt( (data->sphere->r * data->sphere->r) - (d*d) );
// 		double t1 = tc - t1c;
// 		double t2 = tc + t1c;
//         data->d[y * WIDTH + x] = 0xff21ff;
//     return 1;
// }
double	dot_product2(t_vec A, t_vec B)
{	
    printf("\nDEBUG: A.x = %f b.x= %f\n",A.x, B.x);
    
    double ret = (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
    printf("\nDEBUG: ret.x = %f ret.x = %f ret.x = %f ret = %f \n",(A.x * B.x), (A.y * B.y), (A.z * B.z), ret);
exit(1);
	return (ret);
}
double	dot_product(t_vec A, t_vec B)
{	
 
    double ret = (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
  
	return (ret);
}
t_vec  vec_cross(t_vec v1, t_vec v2)
{
  t_vec c;
  c.x = v1.y * v2.z - v2.y * v1.z;
  c.y = v1.z * v2.x - v2.z * v1.x;
  c.z = v1.x * v2.y - v2.x * v1.y;
  return (c);
}
t_vec	dot_vec(t_vec A, t_vec B)
{	
    t_vec ret = {(A.x * B.x) + (A.y * B.y) + (A.z * B.z)};

	return (ret);
}
double	dot_pro_val(double n, t_vec A)
{	
	return (A.x * n + A.y * n+ A.z * n);
}

t_vec	dot_pro_vec(t_vec A, double n)
{	
    t_vec ret;
    
    ret = (t_vec){(A.x * n) , (A.y * n), (A.z * n)};
	return (ret);
}

t_vec  vec_sub(t_vec A, t_vec B)
{
    t_vec ret = {(A.x - B.x) , (A.y - B.y) , (A.z - B.z)};
    return (ret);
}
double	sub2(double n, t_vec A)
{	
	return (A.x - n + A.y - n+ A.z - n);
}
t_vec	sub3(double n, t_vec A)
{	
  t_vec ret = {(A.x - n) , (A.y - n) , (A.z - n)};
    return (ret);
}
t_vec  vec_add(t_vec A, t_vec B)
{
    t_vec ret = {(A.x + B.x) , (A.y + B.y) , (A.z + B.z)};
    return (ret);
}

t_vec	normalize(t_vec vec)
{
	t_vec ret;

	
	ret.x = vec.x/sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	ret.y = vec.y/sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	ret.z = vec.z/sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

    return ret;
}

//    t_vec delta_p = vec_sub(data->ray.o,data->cyl->o);
// 	t_vec tmp = vec_sub(data->ray.d, dot_vec(dot_vec(data->ray.d, data->cyl->ax), data->cyl->ax));
// 	double a = dot_product(tmp,tmp);
//     tmp = dot_vec(tmp, vec_sub(delta_p, dot_vec(dot_vec(data->ray.d, data->cyl->ax), dot_vec(data->cyl->ax, delta_p))));
//     t_vec tmp2 = dot_vec(dot_vec(delta_p, data->cyl->ax), data->cyl->ax);
//     tmp = vec_sub(tmp, tmp2);
//     double b = dot_pro_val(2, tmp);
//     tmp = vec_sub(delta_p, dot_vec(dot_vec(delta_p, data->cyl->ax),data->cyl->ax));
//     double c = dot_product(tmp, tmp) - (data->cyl->r*data->cyl->r);
	// n = 0;
	// l = vector_sub(ray->origin, cylinder->transform.position);
	// tmp[0] = vector_dot(ray->direction, cylinder->transform.rotation);
	// tmp[1] = vector_dot(l, cylinder->transform.rotation);
	// var.x = vector_dot(ray->direction, ray->direction) - pow(tmp[0], 2);
	// var.y = 2 * (vector_dot(ray->direction, l) - (tmp[0] * tmp[1]));
	// var.z = vector_dot(l, l) - pow(tmp[1], 2) -
	// 		pow(cylinder->shape.radius, 2);
	
	
// int		 intersection_cone(t_data *data, t_vec *p, t_vec *n)
// {
//     //         debugnbr(y,1,1);
//     // n = 0;
// 	// l = vector_sub(ray->origin, cylinder->transform.position);
// 	// tmp[0] = vector_dot(ray->direction, cylinder->transform.rotation);
// 	// tmp[1] = vector_dot(l, cylinder->transform.rotation);
// 	// var.x = vector_dot(ray->direction, ray->direction) - pow(tmp[0], 2);
// 	// var.y = 2 * (vector_dot(ray->direction, l) - (tmp[0] * tmp[1]));
// 	// var.z = vector_dot(l, l) - pow(tmp[1], 2) -
// 	// 		pow(cylinder->shape.radius, 2);
// 	double alpha = 2;
//     t_vec vec = vec_sub(data->ray.o,data->cyl->o);
// 	double tmp = dot_pro_val(alpha,)
// 	double a = dot_product(data->ray.d, data->ray.d) - pow(tmp, 2);
    
//     double tmp1 = dot_product(delta_p, data->cyl->ax);
//     double b = 2 * (dot_product(data->ray.d, delta_p) - (tmp * tmp1));
//     double c = dot_product(delta_p, delta_p) - pow(tmp1,2) - (data->cyl->r*data->cyl->r);
   
   
//     double delta = b*b - (4*a*c);
//     double t1;
//     double t2;
//     if (delta< 0)
//         return 0;
//     if (delta>0)
//      t1 = (-b - sqrt(delta))/(2*a);
//      t2 = (-b + sqrt(delta))/(2*a);
//      if (t2 < 0)
//      return 0;
//     double t;
//     if (t1 > 0)
//         t = t1;
//     else
//         t = t2;
    
//     // if (delta == 0)
//     //  t1 = -b /2*a;

//     //printf("\ngood = %deltaf| bad = %deltaf",tonorm.x, n->x);

//     *p = vec_add(data->ray.o, dot_pro_vec(data->ray.d, t));
//     t_vec tonorm = vec_sub(vec_sub( data->cyl->o, *p), dot_vec(dot_vec(data->cyl->ax, vec_sub(data->cyl->o, *p)), data->cyl->ax));
//     // t_vec tonorm = sub3(dot_product(dot_vec(data->cyl->ax, vec_sub(data->cyl->o, *p)), data->cyl->ax), vec_sub( data->cyl->o, *p));

  

//     *n = normalize(tonorm);

//     return 1;
// }

int		 intersection_cylinder(t_data *data, t_vec *p, t_vec *n)
{
    //         debugnbr(y,1,1);
    // n = 0;
	// l = vector_sub(ray->origin, cylinder->transform.position);
	// tmp[0] = vector_dot(ray->direction, cylinder->transform.rotation);
	// tmp[1] = vector_dot(l, cylinder->transform.rotation);
	// var.x = vector_dot(ray->direction, ray->direction) - pow(tmp[0], 2);
	// var.y = 2 * (vector_dot(ray->direction, l) - (tmp[0] * tmp[1]));
	// var.z = vector_dot(l, l) - pow(tmp[1], 2) -
	// 		pow(cylinder->shape.radius, 2);
    t_vec delta_p = vec_sub(data->ray.o,data->cyl->o);
    // delta_p = normalize(delta_p);
	double tmp = dot_product(data->ray.d,data->cyl->ax);
	double a = dot_product(data->ray.d, data->ray.d) - pow(tmp, 2);
    
    double tmp1 = dot_product(delta_p, data->cyl->ax);
    double b = 2 * (dot_product(data->ray.d, delta_p) - (tmp * tmp1));
    double c = dot_product(delta_p, delta_p) - pow(tmp1,2) - (data->cyl->r*data->cyl->r);
   
   
    double delta = b*b - (4*a*c);
    double t1;
    double t2;
    if (delta< 0)
        return 0;
     t1 = (-b - sqrt(delta))/(2*a);
     t2 = (-b + sqrt(delta))/(2*a);
    double t;
   if (t1 < 0 && t2 < 0)
	return 0;
   if (t1 > 0 && t2 > 0)
   {
	   if (t1 > t2 )
		t = t2;
		else
		t = t1;
		}
		else if ( (t1 > 0 && t2 < 0) ||( t2 < 0 && t2 >0))
		{
			if (t1 > t2)
				t = t1;
			else
				t = t2;
		}

		
	// printf("%f \n",t);	

	

    
    // if (delta == 0)
    //  t1 = -b /2*a;

    //printf("\ngood = %deltaf| bad = %deltaf",tonorm.x, n->x);

    *p = vec_add(data->ray.o, dot_pro_vec(data->ray.d, t));
    t_vec tonorm = vec_sub(vec_sub(*p,data->cyl->o), dot_pro_vec(data->cyl->ax, dot_product(data->cyl->ax, vec_sub(*p, data->cyl->o))));
    // t_vec tonorm = sub3(dot_product(dot_vec(data->cyl->ax, vec_sub(data->cyl->o, *p)), data->cyl->ax), vec_sub( data->cyl->o, *p));

  

    *n = normalize(tonorm);

    return 1;
}

int		 intersection_sphere(t_data *data, t_vec *p, t_vec *n)
{
    //         debugnbr(y,1,1);
	double a = dot_product(data->ray.d,data->ray.d);
    double b = 2 * dot_product(data->ray.d, vec_sub(data->ray.o, data->sphere->c));
    double c = dot_product(vec_sub(data->ray.o, data->sphere->c) , vec_sub(data->ray.o, data->sphere->c)) - (data->sphere->r * data->sphere->r);
   
   
    double delta = b*b - (4*a*c);
    double t1;
    double t2;
    if (delta< 0)
        return 0;
    if (delta>0)
     t1 = (-b - sqrt(delta))/(2*a);
     t2 = (-b + sqrt(delta))/(2*a);
     if (t2 < 0)
     return 0;
    double t;
    if (t1 > 0)
        t = t1;
    else
        t = t2;
    
    // if (delta == 0)
    //  t1 = -b /2*a;

    //printf("\ngood = %deltaf| bad = %deltaf",tonorm.x, n->x);
    *p = vec_add(data->ray.o, dot_pro_vec(data->ray.d, t));
    t_vec tonorm = vec_sub( *p, data->sphere->c);
    *n = normalize(tonorm);
    return 1;
}
double		map(double value, double in_max, double in_min, double out_min, double out_max)
{
	return ((value - in_min) * (out_max - out_min)
	/ (in_max - in_min) + out_min);
}
double  get_norm_2(t_vec v)
{
    double ret;
    ret = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    return ret;
}
int intersect_plane(t_data *data, double *t) 
{ 
    // assuming vectors are all normalized
    float denom = dot_product(data->plane->n, data->ray.d); 
    if (denom > 0.0000001) { 

        t_vec p0l0 = vec_sub(data->plane->o , data->ray.o); 
        *t = dot_product(p0l0, data->plane->n) / denom; 
        // if (*t > 0.0)
    // printf("%f\n",*t);
        return (1); 
    } 
 
    return 0; 
}
void    draw_plane(double p1, double p2,int x, int y, t_data *data)
{
     if (p1 > 0.0 && p2 > 0.0 && p1 < p2)
      data->d[(y * WIDTH + x) + 0] = 255 << 8;
      else if   (p1 > 0.0 && p2 > 0.0 && p1 > p2)
      data->d[(y * WIDTH + x) + 0] = 255 ;
    else if ((p1 < 0.0 || p2 < 0.0) && p1 < p2)
            data->d[(y * WIDTH + x) + 0] = 255 << 8;
            
    else if ((p1 < 0.0 || p2 < 0.0) && p1 > p2)
    {             data->d[(y * WIDTH + x) + 0] = 255 ;
            }
    // printf("p1 = %lf  p2 = %lf\n",p1,p2);
    
}

t_ray   get_ray(double u, double v, t_camera *camera)
{
  // /t_vector   dir;
  t_vec   horizontal;
  t_vec   vertical;
  t_vec   cam_u;
  t_vec   cam_v;
  t_vec   cam_w;
  t_ray      new;   
  
  //t_vector ray;
  //camera = NULL;
  u = 2 * (u + 0.5) / ( 600 -1) - 1;
  v = 1 - 2 * (v + 0.5) / ( 600 -1);
  double  half_h;
  double  half_w;
  new.o = camera->look_from;
  half_h = tan((camera->fov * M_PI /180) / 2);
  half_w = half_h;
  cam_w = normalize(vec_sub(camera->look_from, camera->cam_dir));
  cam_u = vec_cross(camera->up, cam_w);
  cam_v = vec_cross(cam_w, cam_u); 
  horizontal = dot_pro_vec(cam_u, half_w);
  vertical = dot_pro_vec(cam_v, half_h);
  camera->low_left_corner = vec_sub(camera->look_from, cam_w);
  camera->low_left_corner = vec_sub(camera->low_left_corner,dot_pro_vec(horizontal, 1/2));
  camera->low_left_corner = vec_sub(camera->low_left_corner,dot_pro_vec(vertical, 1/2));
  new.d = vec_sub(camera->low_left_corner, new.o);
  new.d = vec_add(new.d, dot_pro_vec(horizontal, u));
  new.d = vec_add(new.d, dot_pro_vec(vertical, v));
  new.d = normalize(new.d);

  return new;

//   new.dir = vec_add(dir, camera->cam_dir);
//   new.start = camera->look_from;
//   return (new);


}
void    circle_calc(t_data *data)
{
    double   line;
    int	y;
	int x;
    int a = -100;
    int b = -100;
    int c = -100;
    int res;
    double PI = 22 / 7;
    double alpha = 60 * PI/180;
    t_vec L;
    t_vec V;
            double intensite_pixel;
	y = 0;
    t_vec n;
    t_vec p;
    t_vec   color = {255,0,0};
    double t;
    // int intensite_lum =  ;
    data->sphere->color = color;
    int i = 0;
    double yes;
    int check = 1;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
        {
            // data->ray = get_ray(x, y, data->camera);
            data->ray.d.x = x-(HEIGHT/2);
            data->ray.d.y = y-(HEIGHT/2);
            data->ray.d.z = -WIDTH/(2*tan(alpha));
          
            // printf("\n%f",data->ray.d.z);
            data->ray.d = normalize(data->ray.d);

            // if (intersection_cone(data, &p, &(data->n))){


			// }
            double p1 = 0;
            double p2 = 0;
                 data->plane->n = (t_vec){0,1,0};
            data->plane->o = (t_vec){0,-1,-30};
//             t = 0;
//            if ( intersect_plane(data, &t) )
//            { 
//                p1 = t;
//             //    if (t > 0.0)
            //  printf("%f",data->ray.d.z);
            //  exit(1);
//    { 
//                sleep(5);}
//                }
//             else 
//             p1 = -10000;
//             data->plane->n = (t_vec){1,0,0};
//             data->plane->o = (t_vec){200,-2,-30};
//             if (intersect_plane(data, &t))
//             p2 = t;
//             else 
//             p2 = -10000;
//             draw_plane(p1,p2,x,y,data);
            //  if (intersect_plane(data, &t))
            // {
            //      data->d[(y * WIDTH + x) + 0] = 255;
            // }
            if (intersection_sphere(data, &p, &(data->n))){



   double ang_norm_light =  fmax(0,dot_product(normalize(vec_sub(data->lum_pos, p)), data->n));
                L = normalize(vec_sub( data->lum_pos,p));
                V = normalize(vec_sub(data->ray.o, p));
                t_vec dd = dot_pro_vec(data->n,dot_product(L,data->n));
                t_vec Rm = vec_sub(dot_pro_vec(dd, 2),L);
                double ka = 0, kd = 0, ks = 1;
double intensite_pixel = ka + (kd * ang_norm_light) + (ks *pow(fmax(0, dot_product(Rm,V)),40));
            int colorr = (int)(255);
            if(colorr > 255)
                colorr = 255;
            data->d[(y * WIDTH + x) + 0] = colorr ;
            color.x = (int)(((data->d[(y * WIDTH + x) + 0]>> 16)&255) + 255* intensite_pixel);
            color.y = (int)(((data->d[(y * WIDTH + x) + 0]>> 8)&255)+255 * intensite_pixel);
            color.z = (int)((data->d[(y * WIDTH + x) + 0] &255) + 255 * intensite_pixel);
            if (color.x > 255)
                color.x = 255;
                 if (color.y > 255)
                color.y = 255;
                 if (color.z > 255)
                color.z = 255;
                                  data->d[(y * WIDTH + x) + 0] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
								  
   
            }
            
        }
		y++;
	}
               
}

void		image_clear(int *d)
{
	int	y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
			d[y * WIDTH + x] = 0x000000;
		y++;
	}
}
int    mouse_move(int x, int y,t_data *data)
{
     double PI = 22 / 7;
    double alpha = 60 * PI/180;
data->lum_pos.x =  x-(HEIGHT/2);
// data->lum_pos.y =  y-(HEIGHT/2);

// data->lum_pos.z = ;

// data->sphere->c.z -= 10;
image_clear(data->d);
circle_calc(data);
mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
return 1;
}

int main()
{
    t_data	*data;
	int		bpp;
   t_vec source = {0,0,0};
      t_vec s = {0,30,-200};
       t_vec spher = {0,0,-100};
 t_vec lum_pos = {0,0,0};
 t_vec n = {0,1,0};
 t_vec plane_o = {0,0,-30};
    t_sphere *sphere;
     sphere = (t_sphere *)malloc(sizeof(t_sphere));
    t_cylinder *cyl;
    cyl = (t_cylinder *)malloc(sizeof(t_cylinder));
    t_vec cyl_ax = {0,1,0};
	t_vec cyl_o = s;
    cyl->ax = cyl_ax;
	cyl->o = s;
	cyl->r = 30;
	sphere->c = spher;
    sphere->r = 30;
	debugnbr(sphere->c.x,1,1);
	data = (t_data *)malloc(sizeof(t_data));
    t_camera *cam;
    cam = (t_camera *)malloc(sizeof(t_camera));
    cam->look_from = (t_vec){0, 0, -80};
    cam->cam_dir = (t_vec){0, 0, -1};
    cam->up = (t_vec){0, 1, 0};
    cam->fov = 60;
    data->camera = cam;
    t_plane *plane;
    plane = (t_plane *)malloc(sizeof(t_plane));
    plane->o = plane_o;
    plane->n = n;
    data->plane = plane;
    data->cyl = cyl;
 data->cyl_center_calc = 1;
	data->sphere = sphere;
	debugstr("EEEEEWWWW",1);
    data->lum_pos = lum_pos;
	data->ray.o = source;
	//data->ray.d = target;

    data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, WIDTH, HEIGHT, "ok");
	data->img = mlx_new_image(data->ptr, WIDTH, HEIGHT);
	data->d = (int *)mlx_get_data_addr(data->img, &bpp, &bpp, &bpp);

    circle_calc(data);
    // image_clear(data->d, 200,200,100);
    mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
    mlx_hook(data->win, 6, 0, mouse_move, data);
    mlx_loop(data->ptr);

}
