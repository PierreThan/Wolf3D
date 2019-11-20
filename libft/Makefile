# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pthan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 19:42:35 by pthan             #+#    #+#              #
#    Updated: 2019/11/04 17:01:24 by pthan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME 	= 	libft.a

# Compilation
CC		= 	@cc
CFLAGS	= 	-Wall -Wextra -Werror
LIBFLAGS = -Iincludes

# Files && Objs

SRC_PATH	= srcs

PRINTF_PATH = ft_printf

CONV_PATH 	= convs

UTILS_PATH  = utils

OBJ_PATH	= objs

INC_PATH	= includes

LDFLAGS		= -Llibft
LDLIBS		= -lft


# SRCS && OBJS
SRC_NAME 	=	ft_atoi.c									\
				ft_atoi_base.c								\
				ft_bzero.c									\
				ft_isalnum.c								\
				ft_isalpha.c								\
				ft_isascii.c								\
				ft_isdigit.c								\
				ft_islower.c								\
				ft_isprint.c								\
				ft_iswhitespace.c							\
				ft_itoa.c									\
				ft_isupper.c									\
				ft_lstadd.c									\
				ft_lstaddend.c								\
				ft_lstdel.c									\
				ft_lstdelone.c								\
				ft_lstiter.c								\
				ft_lstlast.c								\
				ft_lstmap.c									\
				ft_lstnew.c									\
				ft_lstreverse.c								\
				ft_lstsize.c								\
				ft_memalloc.c								\
				ft_memccpy.c								\
				ft_memchr.c									\
				ft_memcmp.c									\
				ft_memcpy.c									\
				ft_memdel.c									\
				ft_memmove.c								\
				ft_memset.c									\
				ft_power.c									\
				ft_putchar_fd.c								\
				ft_putchar.c								\
				ft_putendl_fd.c								\
				ft_putendl.c								\
				ft_putnbr_fd.c								\
				ft_putnbr.c									\
				ft_putstr_fd.c								\
				ft_putstr.c									\
				ft_strcat.c									\
				ft_strchr.c									\
				ft_strclr.c									\
				ft_strcmp.c									\
				ft_strcpy.c									\
				ft_strdel.c									\
				ft_strdup.c									\
				ft_strequ.c									\
				ft_striter.c								\
				ft_striteri.c								\
				ft_strjoin.c								\
				ft_strlcat.c								\
				ft_strlen.c									\
				ft_strmap.c									\
				ft_strmapi.c								\
				ft_strncat.c								\
				ft_strncmp.c								\
				ft_strncpy.c								\
				ft_strnequ.c								\
				ft_strnew.c									\
				ft_strnstr.c								\
				ft_strrchr.c								\
				ft_strsplit.c								\
				ft_strstr.c									\
				ft_strsub.c									\
				ft_strtrim.c								\
				ft_tolower.c								\
				ft_toupper.c								\
				get_next_line.c								\
				$(PRINTF_PATH)/$(CONV_PATH)/cast_nbrs.c		\
				$(PRINTF_PATH)/$(CONV_PATH)/char_strings.c	\
				$(PRINTF_PATH)/$(CONV_PATH)/float_args.c	\
				$(PRINTF_PATH)/$(CONV_PATH)/float.c			\
				$(PRINTF_PATH)/$(CONV_PATH)/numbers.c		\
				$(PRINTF_PATH)/$(CONV_PATH)/pct_ptr.c		\
				$(PRINTF_PATH)/$(CONV_PATH)/pct_ptr.c		\
				$(PRINTF_PATH)/$(SRC_PATH)/buffer.c			\
				$(PRINTF_PATH)/$(SRC_PATH)/check_flag_pad.c \
				$(PRINTF_PATH)/$(SRC_PATH)/conv_specifiers.c\
				$(PRINTF_PATH)/$(SRC_PATH)/ft_printf.c		\
				$(PRINTF_PATH)/$(SRC_PATH)/padding.c		\
				$(PRINTF_PATH)/$(SRC_PATH)/parse_args.c		\
				$(PRINTF_PATH)/$(UTILS_PATH)/find_conv.c	\
				$(PRINTF_PATH)/$(UTILS_PATH)/find_flag.c	\
				$(PRINTF_PATH)/$(UTILS_PATH)/ft_get_wchar.c \
				$(PRINTF_PATH)/$(UTILS_PATH)/ft_lltoa_base.c\
				$(PRINTF_PATH)/$(UTILS_PATH)/ft_nbrlen.c	\
				$(PRINTF_PATH)/$(UTILS_PATH)/ft_wcharlen.c 	\
				$(PRINTF_PATH)/$(UTILS_PATH)/ft_wstrlen.c 	\
				$(PRINTF_PATH)/$(UTILS_PATH)/maths.c		\
				$(PRINTF_PATH)/$(UTILS_PATH)/to_upper.c		\

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

#  *********************************************************************** #
# COLORS

LOG_CLEAR		= \033[2K
LOG_UP			= \033[A
LOG_NOCOLOR		= \033[0m
LOG_BOLD		= \033[1m
LOG_UNDERLINE	= \033[4m
LOG_BLINKING	= \033[5m
LOG_BLACK		= \033[1;30m
LOG_RED			= \033[1;31m
LOG_GREEN		= \033[1;32m
LOG_YELLOW		= \033[1;33m
LOG_BLUE		= \033[1;34m
LOG_VIOLET		= \033[1;35m
LOG_CYAN		= \033[1;36m
LOG_WHITE		= \033[1;37m

# *********************************************************************** #


# Protect

.PHONY:	all clean fclean re

# RULES

# Main rules
all				: 	$(OBJ_PATH) $(NAME)

re				: 	fclean all

# Compilation rules
$(OBJ_PATH)		:
					@mkdir $(OBJ_PATH) 2> /dev/null || true
					@mkdir $(OBJ_PATH)/$(PRINTF_PATH) 2> /dev/null || true
					@mkdir $(OBJ_PATH)/$(PRINTF_PATH)/$(CONV_PATH) 2> /dev/null || true
					@mkdir $(OBJ_PATH)/$(PRINTF_PATH)/$(SRC_PATH) 2> /dev/null || true
					@mkdir $(OBJ_PATH)/$(PRINTF_PATH)/$(UTILS_PATH) 2> /dev/null || true

$(NAME)			:	$(OBJ)
					@ar rc $(NAME)  $(OBJ)
					@ranlib $(NAME)
					@echo "Make $(NAME)$(LOG_GREEN) ✓ $(LOG_NOCOLOR)"

$(OBJ_PATH)/%.o: 	$(SRC_PATH)/%.c
					$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ -c $<

# Clean rules
clean			:
					@rm -rf $(OBJ_PATH)
					@echo "Removes all .o & $(OBJ_PATH) $(LOG_GREEN) ✓ $(LOG_NOCOLOR)"


fclean			: 	clean
					@rm -f $(NAME)
					@echo "Remove $(NAME)$(LOG_GREEN) ✓ $(LOG_NOCOLOR)"

norme:
					@norminette $(SRC)
					@norminette $(INC_PATH)/
# **************************************************************************** #
