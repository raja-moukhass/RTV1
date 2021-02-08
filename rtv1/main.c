#include "rtv1.h"

double   ft_atof(char *str)
{
    int     i;
    int     j;
    int     signe;
    double  res;
    i = 0;
    res = 0;
    signe = 1;
    while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
            || str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        signe = str[i] == '-' ? -1 : 1;
        i++;
    }
    while (str[i] <= '9' && str[i] >= '0')
    {
        res = (res * 10) + str[i] - '0';
        i++;
    }
    j = 0;
    if (str[i] == '.')
    {
        i++;
        while (str[i] <= '9' && str[i] >= '0' && j <= 3)
        {
            res = res + (double)((str[i] - '0') / pow(10.0, (double)++j));
            i++;
        }
    }
    return (res * signe);
}
void	add_node(t_data **dat, int type)
{
	
	t_data *data = *dat;


	if (type == 1)
	{
		t_sphere *temp;
		t_sphere *p;
		temp = ft_memalloc(sizeof(t_sphere));
		if (data->sphere == NULL)
			data->sphere = temp;
		else
		{
			p = data->sphere;
			while (p != NULL)
				p = p->next;
			p = temp;
			p->next = NULL;
		}
	}
	if (type == 2)
	{
		t_cone *temp;
		t_cone *p;
		temp = ft_memalloc(sizeof(t_cone));
		if (data->cone == NULL)
			data->cone = temp;
		else
		{
			p = data->cone;
			while (p != NULL)
				p = p->next;
			p = temp;
			p->next = NULL;
		}
	}
	if (type == 3)
	{

		t_cylinder *temp;
		t_cylinder *p;
		temp = ft_memalloc(sizeof(t_cylinder));
		if (data->cylinder == NULL)
			data->cylinder = temp;
		else
		{
			p = data->cylinder;
			while (p != NULL)
				p = p->next;
			p = temp;
			p->next = NULL;
		}
	}
	if (type == 4)
	{

		t_plane *temp;
		t_plane *p;
		temp = ft_memalloc(sizeof(t_plane));
		if (data->plane == NULL)
			data->plane = temp;
		else
		{
			p = data->plane;
			while (p != NULL)
				p = p->next;
			p = temp;
			p->next = NULL;
		}
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

t_vec		split_data(t_data *data, char *str)
{
    int		i;
    char	**ar;
    int		j;
    int		dot;
	t_vec	ret;

	
    i = 0;
    ar = ft_strsplit(str, ' ');
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
	ret.x = ft_atof(ar[0]);
	ret.y = ft_atof(ar[1]);
	ret.z = ft_atof(ar[2]);

    return (ret);
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

	data->light->pos = split_data(data,data->tab[i + 1]);

	data->light->color = split_data(data,data->tab[i + 2]);
	data->light->intens = ft_atof(ft_strdup(data->tab[i + 3]));
	
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
	temp->radius = ft_atof(ft_strdup(data->tab[i + 5]));
	
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
void		cylinder_check(t_data **dat, int i)
{
	int			check;
	t_cylinder		*temp;
	t_data		*data;
	
	data = *dat;
	check = 1;
	while(data->tab[i + check] && check < 5)
		check++;
	if (check != 5)
	{
		call_error(data);
	}
	add_node(dat,3);

	temp = data->cylinder;
	while(temp->next)
		temp = temp->next;
	temp->pos = split_data(data,data->tab[i + 1]);
	temp->trans = split_data(data,data->tab[i + 2]);
	temp->rot = split_data(data,data->tab[i + 3]);
	temp->rot = split_data(data,data->tab[i + 4]);
	temp->color = split_data(data,data->tab[i + 5]);
	temp->angle = ft_atof(ft_strdup(data->tab[i + 6]));
	
}
void		plane_check(t_data **dat, int i)
{
	int			check;
	t_plane		*temp;
	t_data		*data;
	ft_putstr("here");
	data = *dat;
	check = 1;
	while(data->tab[i + check] && check < 4)
		check++;
	if (check != 4)
	{
		call_error(data);
	}
	add_node(dat,4);

	temp = data->plane;
	while(temp->next)
		temp = temp->next;
	temp->pos = split_data(data,data->tab[i + 1]);
	temp->trans = split_data(data,data->tab[i + 2]);
	temp->rot = split_data(data,data->tab[i + 3]);
	temp->rot = split_data(data,data->tab[i + 4]);
	temp->color = split_data(data,data->tab[i + 5]);
	
}
int		ft_checker(t_data **data)
{
    int i = 0;
    while ((*data)->tab[i])
    {
        if(ft_strcmp((*data)->tab[i],"camera") == 0)
				camera_check(data, i);
         if(ft_strcmp((*data)->tab[i],"sphere") == 0)
              sphere_check(data, i);
		   if(ft_strcmp((*data)->tab[i],"cylinder") == 0)
             cylinder_check(data, i);
	if(ft_strcmp((*data)->tab[i],"light") == 0)
             light_check(data, i);

 if(ft_strcmp((*data)->tab[i],"plane") == 0)
             plane_check(data, i);
        if(ft_strcmp((*data)->tab[i],"cone") == 0)
             cone_check(data, i);
        i++;
    }
    return(0);
}

void	init_data(t_data **data, char *av)
{
	int		i;
	char	**tab;
    int		count;
	int fd;
	i = 0;
	fd = open(av, O_RDONLY);
	count = ft_lines(fd);
	fd = open(av, O_RDONLY);
    tab = (char **)malloc(sizeof(char*) * (count + 1));
    while(get_next_line(fd,&tab[i]))
		i++;
    close(fd);
	
    tab[i] = NULL;
	ft_putstr("here");
    (*data) = (t_data *)malloc(sizeof(t_data));
    (*data)->tab = tab;
	(*data)->camera = (t_camera *)malloc(sizeof(t_camera));
	(*data)->sphere = malloc(sizeof(t_sphere));
	(*data)->sphere = NULL;
	(*data)->cone = malloc(sizeof(t_cone));
	(*data)->cone = NULL;
	(*data)->cylinder = malloc(sizeof(t_cylinder));
	(*data)->cylinder = NULL;
}

int main(int ac, char **av)
{
    t_data  *data;
	init_data(&data, av[1]);
    ac = 0;
    
    char **tab;
    int i = 0;
    
   
	
    if (ft_checker(&data) < 0)
        {
            ft_putendl("error");
        }
		printf("%f", data->plane->pos.x);
		// printf("\ncamera:\n\tsource|%s|%s|%s|\n\ttarget|%s|%s|%s|\nsphere:\n\tposition|%s|%s|%s|\n\ttranslation",data->cylinder->pos,data->camera->source[1],data->camera->source[2],data->camera->target[0],data->camera->target[1],data->camera->target[2],data->sphere->next->pos[0],data->sphere->pos[1],data->cone->angle);
    return (0);
}
