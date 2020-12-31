#ifndef RTV1_H
# define RTV1_H
# include <stdio.h>
# include <math.h>
# include <mlx.h>
#include <stdlib.h>
# define WIDTH  600
# define HEIGHT 600
# define BPP 3
# define PSIZE (4 - (600 * 3) % 4) % 4
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40


typedef struct	s_data
{
	int		*d;
	void	*ptr;
	void	*win;
	void	*img;


}				t_data;
#endif