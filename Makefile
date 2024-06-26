BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		=	srcs/events.c \
				srcs/double_atoi.c \
				srcs/julia_set.c	\
				srcs/mandelbrot.c \
				srcs/mlx_utils.c \
				srcs/main.c
SRCS_B		= 	srcs_bonus/main_bonus.c \
				srcs_bonus/mandelbrot_bonus.c \
				srcs_bonus/keyboard_hooks_bonus.c \
				srcs_bonus/julia_set_bonus.c \
				srcs_bonus/events_bonus.c \
				srcs_bonus/double_atoi.c	\
				srcs_bonus/mlx_utils_bonus.c	\
				srcs_bonus/zoom_events.c	\
				srcs_bonus/zoom_ratio.c	\
				srcs_bonus/burningship.c

NAME		= fractol
NAME_B		= fractol_bonus
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
CC			= cc
CC_FLAGS	= -Wall -Werror -Wextra
MLB_FLAGS	= -I -g3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm

%.o : %.c 
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CC_FLAGS) -o $(NAME) $(OBJS) $(MLB_FLAGS)
$(NAME_B): $(OBJS_B)
	@$(CC) -o $(NAME_B) $(OBJS_B) $(CC_FLAGS) $(MLB_FLAGS)
all : $(NAME)

bonus : $(NAME_B)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJS_B)
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re