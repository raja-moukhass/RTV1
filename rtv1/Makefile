NAME= RTv1
OBJ =  main.o
FLAGS =  -g
Include= rtv1.h
SRC= main.c\

OBJ= main.o\


all: $(NAME)

$(NAME):
	gcc -g -lmlx -framework OpenGL -framework AppKit main.c transforms.c vec_calc.c libft/libft.a 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

