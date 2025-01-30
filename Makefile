# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phautena <phautena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 13:20:42 by phautena          #+#    #+#              #
#    Updated: 2025/01/30 13:26:24 by phautena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc -Wall -Wextra -Werror -ggdb -I./minilibx-linux -I./includes

SRC_DIR = ./srcs/

SRC_FILES = main.c

SRC = ${addprefix ${SRC_DIR},${SRC_FILES}}

OBJ = ${SRC:.c=.o}

MLX_LIB = ./minilibx-linux/libmlx.a -lX11 -lXext
LIBFT_LIB = ./Libft/libft.a
FT_PRINTF_LIB = ./ft_printf/libftprintf.a
GNL_LIB = ./get_next_line/gnl.a

.c.o:
	${CC} -c $< -o $@

all: ${NAME}

${NAME}: ${MLX_LIB} ${LIBFT_LIB} ${FT_PRINTF_LIB} ${GNL_LIB} ${OBJ}
	${CC} ${OBJ} ${LIBFT_LIB} ${FT_PRINTF_LIB} ${MLX_LIB} ${GNL_LIB} -o ${NAME}

${MLX_LIB}:
	${MAKE} -C ./minilibx-linux

${LIBFT_LIB}:
	${MAKE} -C ./Libft

${FT_PRINTF_LIB}:
	${MAKE} -C ./ft_printf

${GNL_LIB}:
	${MAKE} -C ./get_next_line

clean:
	${MAKE} clean -C ./minilibx-linux/
	${MAKE} clean -C ./Libft/
	${MAKE} clean -C ./ft_printf/
	${MAKE} clean -C ./get_next_line/
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}
	rm -f ./Libft/libft.a
	rm -f ./ft_printf/libftprintf.a
	rm -f ./get_next_line/gnl.a

re: fclean all

.PHONY: all clean fclean re
