 #include <fcntl.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <stdio.h>
typedef struct s_camera
{
    char    **source; // looking from
 
    char    **target; // looking at
 

    //struct s_data next;
}              t_camera;
typedef struct s_sphere
{
    char	**pos;
	char	**trans;
	char	**rot;
	char	**color;
	char	*radius;
	struct s_sphere  *next;
}			t_sphere;

typedef struct s_cone
{
    char	**pos;
	char	**trans;
	char	**axis;
	char	**rot;
	char	**color;
	char	*angle;
	struct s_cone  *next;
}			t_cone;

typedef struct s_data
{
    char **tab;

    t_camera	*camera;
	t_sphere	*sphere;
	t_cone		*cone;
}              t_data;


void	add_node(t_data **dat, int type)
{
	t_sphere *temp;
	t_sphere *p;
	t_data *data;

	data = *dat;

	if (type == 1)
		temp = ft_memalloc(sizeof(t_sphere));
	if (type == 2)
		temp = ft_memalloc(sizeof(t_cone));
	if (data->sphere == NULL)
		data->sphere = temp;
	else
	{
		p = data->sphere;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
		}
}
void	debugstr(char *str, int nl)
{
	ft_putstr_fd("|",2);
	ft_putstr_fd(str,2);
	ft_putstr_fd("|",2);
	if (nl)
		ft_putendl_fd("",2);
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

void	call_error(t_data *data)
{
	ft_putstr("parsing error");
    exit(1);
}

int ft_lines(int fd)
{
    char *line = NULL;
    int count = 0;

    while (get_next_line(fd,&line))
    {
        count++;
        free(line);
    }
    close(fd);
    return (count);
}
// int		init_data(t_data *data)
// {
// 	data = (t_data *)malloc(sizeof(t_data));
// 	data->camera = (t_camera *)malloc(sizeof(t_camera));
// }
char	**split_data(t_data *data, char *str)
{
    int		i;
    char	**ar;
    int		j;
    int		dot;

	
    i = 0;
    ar = ft_strsplit(str, ' ');
	ft_putendl(str);
    while (ar[i])
    {
        dot = 1;
        j = 0;
        while(ar[i][j])
        {
            if (!ft_isdigit(ar[i][j]))
			{
				if ((ar[i][j] == '-' && j == 0) || (ar[i][j] == '.' && dot && j != 0 && ft_isdigit(ar[i][j + 1])))
					;
				else 
					call_error(data);
				if (ar[i][j] == '.')
					dot--;
			}
			j++;
		}
        i++;
    }
    if (i != 3)
        call_error(data);
    return (ar);
}
void		camera_check(t_data **dat, int i)
{
	int		check;
	t_data *data;

	data = *dat;
	check = 1;
	while(data->tab[i + check] && check < 3)
		check++;
	if (check != 3)
		call_error(data);

	data->camera->source = split_data(data,data->tab[i + 1]);

	data->camera->target = split_data(data,data->tab[i + 2]);
	
}
void		sphere_check(t_data **dat, int i)
{
	int			check;
	t_sphere	*temp;
	t_data		*data;
	
	data = *dat;
	check = 1;
	while(data->tab[i + check] && check < 6)
		check++;

				debugstr(data->tab[i + check],1);
	if (check != 6)
		call_error(data);
	add_node(dat,1);
	temp = data->sphere;
	while(temp->next)
	temp = temp->next;
	temp->pos = split_data(data,data->tab[i + 1]);
	temp->trans = split_data(data,data->tab[i + 2]);
	temp->rot = split_data(data,data->tab[i + 3]);
	temp->color = split_data(data,data->tab[i + 4]);
	temp->radius = ft_strdup(data->tab[i + 5]);
	
}
void		cone_check(t_data **dat, int i)
{
	int			check;
	t_cone		*temp;
	t_data		*data;
	
	data = *dat;
	check = 1;
	while(data->tab[i + check] && check < 5)
		check++;
	if (check != 5)
	{
		call_error(data);
	}
	add_node(dat,2);
	temp = data->cone;
	while(temp->next)
	temp = temp->next;
	temp->pos = split_data(data,data->tab[i + 1]);
	temp->trans = split_data(data,data->tab[i + 2]);
	temp->rot = split_data(data,data->tab[i + 3]);
	temp->color = split_data(data,data->tab[i + 4]);
	temp->angle = ft_strdup(data->tab[i + 5]);
	
}
int		ft_checker(t_data **data)
{
    int i = 0;
    while ((*data)->tab[i])
    {
		ft_putnbrnl(i);
        if(ft_strcmp((*data)->tab[i],"camera") == 0)
				camera_check(data, i);
		ft_putstr("ew");
         if(ft_strcmp((*data)->tab[i],"sphere") == 0)
              sphere_check(data, i);
		

        if(ft_strcmp((*data)->tab[i],"cone") == 0)
             cone_check(data, i);
        i++;
    }
    return(0);
}

void	init_data(t_data **data)
{
    (*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->camera = (t_camera *)malloc(sizeof(t_camera));
	(*data)->camera->source = ft_memalloc(sizeof(char *));
	(*data)->sphere = malloc(sizeof(t_sphere));
	(*data)->sphere = NULL;
	(*data)->cone = malloc(sizeof(t_cone));
	(*data)->cone = NULL;
}

int main(int ac, char **av)
{
    t_data  *data;
	init_data(&data);
    ac = 0;
    int fd = open(av[1], O_RDONLY);
    char **tab;
    char *line;
    int i = 0;
    int count = ft_lines(fd);
    
    int fd1 = open(av[1], O_RDONLY);
    tab = (char **)malloc(sizeof(char*) * (count + 1));
	//ft_putnbrnl(count);
    while(get_next_line(fd1,&tab[i]))
	i++;
	
    tab[i] = NULL;
    data->tab = tab;
	
    if (ft_checker(&data) < 0)
        {
            ft_putendl("error");
        }
		printf("\ncamera:\n\tsource|%s|%s|%s|\n\ttarget|%s|%s|%s|\nsphere:\n\tposition|%s|%s|%s|\n\ttranslation",data->camera->source[0],data->camera->source[1],data->camera->source[2],data->camera->target[0],data->camera->target[1],data->camera->target[2],data->sphere->next->pos[0],data->sphere->pos[1],data->cone->angle);
    close(fd1);
    return (0);
}
