# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pthan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 20:01:11 by pthan             #+#    #+#              #
#    Updated: 2020/02/04 15:42:18 by atyczyns         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= wolf3d
LIB				= ./libft/
LDFLAGS			= -Llibft
LDLIBS			= -lft
SRC_PATH		= srcs
OBJ_PATH		= objs
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -Iincludes -fsanitize=address
MLX				= -lmlx -framework OpenGL -framework AppKit
SRC_NAME		= 	main.c \
					input_check.c \
					mlx.c \
					vector2d.c \
					ray_casting.c \
					textures.c \
					input_check_bis.c \
					vector2d_bis.c \
					floor_ceiling.c


OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)		:
				 	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(NAME)			:	$(OBJ)
					@make -C $(LIB)
					@$(CC) $(CFLAGS) -o $@ $^ $(LIB)libft.a $(MLX)
					@echo "Make $(NAME)$(LOG_GREEN) ✓ $(LOG_NOCOLOR)"

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
					$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: clean fclean all re
