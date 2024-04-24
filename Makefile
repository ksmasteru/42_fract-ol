# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:04:45 by tnard             #+#    #+#              #
#    Updated: 2024/04/19 22:24:42 by hes-saqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		=	srcs/complex.c \
			srcs/events.c \
			srcs/double_atoi.c \
			srcs/keyboard_hooks.c \
			srcs/julia_set.c	\
			srcs/mandelbrot.c \
			srcs/main.c
SRCS_B		= 	srcs_bonus/main_bonus.c \
				srcs_bonus/utils_bonus.c \
				srcs_bonus/utils_2_bonus.c \
\
				srcs_bonus/editor_maps/key.c \
				srcs_bonus/editor_maps/updating.c \
\
				srcs_bonus/global_handling/launch_wins.c \
				srcs_bonus/global_handling/global_update.c \
				srcs_bonus/global_handling/global_update_2.c \
				srcs_bonus/global_handling/update_and_key_call.c \
\
				srcs_bonus/displaying/map_bonus.c \
				srcs_bonus/displaying/score_bonus.c \
				srcs_bonus/displaying/map_win_bonus.c \
\
				srcs_bonus/handling/clock_bonus.c \
				srcs_bonus/handling/key_bonus.c \
				srcs_bonus/handling/update_bonus.c \
\
				srcs_bonus/guards/list_bonus.c \
				srcs_bonus/guards/random_bonus.c \
				srcs_bonus/guards/check_bonus.c \
\
				srcs_bonus/menu/menu.c \
				srcs_bonus/menu/update.c \
				srcs_bonus/menu/key.c \
\
				srcs_bonus/editor/map_and_map_top.c \
				srcs_bonus/editor/map_blocks.c \
				srcs_bonus/editor/key.c \
				srcs_bonus/editor/special_key.c \
				srcs_bonus/editor/mini.c \
				srcs_bonus/editor/updating.c \
\
				srcs_bonus/editor_menu/key.c \
				srcs_bonus/editor_menu/updating.c \
				srcs_bonus/editor_menu/parsing.c \
\
				srcs_bonus/generate/parsing_bonus.c \
				srcs_bonus/generate/parsing_2_bonus.c \
				srcs_bonus/generate/image_bonus.c \
				srcs_bonus/generate/init_global.c \
				srcs_bonus/generate/init_global_2.c \
				srcs_bonus/generate/map_bonus.c \
				srcs_bonus/generate/free_bonus.c \
				srcs_bonus/generate/textures/mini.c \
				srcs_bonus/generate/textures/player.c \
				srcs_bonus/generate/textures/slime.c \
				srcs_bonus/generate/textures/special.c \
				srcs_bonus/generate/textures/sprites.c \
				srcs_bonus/generate/textures/wall.c

NAME		= fractol
NAME_B		= fractol_bonus
minilibx	= mlx/libmlx.a
OBJS_DIR	= objs/
OBJS_DIR_B	= objs_b/
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJECTS_PREFIXED_B = $(addprefix $(OBJS_DIR_B), $(OBJS_B))
CC			= gcc
CC_FLAGS	= -Wall -Werror -Wextra -g
MLB_FLAGS	= -I -g3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm libft/libft.a ft_printf/libftprintf.a

$(OBJS_DIR)%.o : %.c includes/fractol.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@$(CC) -g -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(OBJS_DIR_B)%.o : %.c includes_bonus/so_long_bonus.h
	@mkdir -p $(OBJS_DIR_B)
	@mkdir -p $(OBJS_DIR_B)srcs_bonus
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME_B)]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -g -o $(NAME) $(OBJECTS_PREFIXED) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

$(NAME_B): $(OBJECTS_PREFIXED_B) maker
	@$(CC) -o $(NAME_B) $(OBJECTS_PREFIXED_B) $(CC_FLAGS) $(MLB_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME_B)$(END)\n"

all: $(NAME)

bonus:	$(NAME_B)

maker:
	@make -C mlx
	@make bonus -C libft
	@make -C ft_printf

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIR_B)
	@make clean -C libft
	@make clean -C ft_printf
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@make clean -C mlx
	@make fclean -C libft
	@make fclean -C ft_printf
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re
