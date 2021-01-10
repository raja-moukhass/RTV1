# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 12:17:42 by ramoukha          #+#    #+#              #
#    Updated: 2021/01/10 17:00:27 by ramoukha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMP = gcc -Werror -Wextra -Wall
SRC = srcs/main.c srcs/vec_calculation.c
OB =  main.o 
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