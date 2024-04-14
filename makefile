SRC_FILES = test2.c julia_set.c complex.c ft_itoa.c double_atoi.c mandelbrot.c
OBJ_FILES = $(SRC_FILES:.c=.o)
NAME = fractol
all : $(NAME)


$(NAME): $(OBJ_FILES)
	cc libmlx.dylib libmlx.a $(OBJ_FILES) -o $(NAME)
%.o : %.c
	cc -c $< -o $@
clean:
	rm -rf $(OBJ_FILES)
fclean:
	clean
	rm -rf $(NAME)
re:	fclean
	all