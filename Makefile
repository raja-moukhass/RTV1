# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 12:17:42 by ramoukha          #+#    #+#              #
#    Updated: 2021/02/16 15:06:05 by ramoukha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMP = gcc 
SRC = srcs/main.c srcs/vec_calc.c  srcs/transforms.c srcs/ft_intersection.c
OB =  srcs/main.o srcs/vec_calc.o srcs/transforms.o  srcs/ft_intersection.o
INC_DIR = ./includes/
INC = ./includes/rtv1.h
OB = $(SRC:.c=.o)
NAME =  RTV1
LIBFLAGS = -L ./libft -lft -lpthread -L ./miniLibX -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME): $(OB)
	@make -C libft/
	@make -C miniLibX/
	$(COMP) -g -o $(NAME) $(OB) $(LIBFLAGS)
	@printf "\033[00;32m"
	@printf "BINARY CREATED\n"
	@printf "\033[00;0m"

%.o : %.c $(INC)
	$(COMP) -c -o $@ $< -I $(INC_DIR)

clean:
	@make -C libft/ clean
	@make -C miniLibX clean
	@rm -f $(OB)
	@printf "\033[00;32m"
	@printf "OBJECTS REMOVED\n"
	@printf "\033[00;0m"

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@printf "\033[00;32m"
	@printf "BINARY REMOVED\n"
	@printf "\033[00;0m"
re: fclean all