/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 06:26:13 by amya              #+#    #+#             */
/*   Updated: 2019/04/01 04:12:36 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*d1;
	char	*d2;
	size_t	i;
	int		l;

	i = 0;
	d1 = (char *)s1;
	d2 = (char *)s2;
	l = ft_strlen(d1);
	while (d2[i] && i < n)
	{
		d1[l] = d2[i];
		l++;
		i++;
	}
	d1[l] = '\0';
	s1 = d1;
	return (s1);
}