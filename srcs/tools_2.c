/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 09:57:34 by ramoukha          #+#    #+#             */
/*   Updated: 2021/02/27 14:38:35 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_atof(char *str)
{
	int		i;
	int		j;
	int		signe;
	double	res;

	i = 0;
	res = 0;
	signe = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
	|| str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
		signe = str[i++] == '-' ? -1 : 1;
	while (str[i] <= '9' && str[i] >= '0')
		res = (res * 10) + str[i++] - '0';
	j = 0;
	if (str[i] == '.')
		while (str[i] <= '9' && str[i] >= '0' && j <= 3)
			res = res + (double)((str[i++] - '0') / pow(10.0, (double)++j));
	return (res * signe);
}

int			ft_lines(int fd)
{
	char	*line;
	int		count;

	line = NULL;
	count = 0;
	while (get_next_line(fd, &line))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}
