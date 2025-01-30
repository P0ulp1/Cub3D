# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phautena <phautena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 12:00:44 by phautena          #+#    #+#              #
#    Updated: 2024/06/10 14:16:20 by phautena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIRSRC = srcs/

SRC = c_conversion.c di_conversion.c ft_printf.c function_summary.c p_conversion.c \
       print_char.c print_percent.c s_conversion.c x_conversion.c x_upper_conversion.c \
       u_conversion.c

SRCS = ${addprefix ${DIRSRC}, ${SRC}}

OBJ = ${SRCS:.c=.o}

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -c -I./includes/
RM = rm -f

NAME = libftprintf.a

all: ${NAME}

${NAME}: ${OBJ}
	ar rc ${NAME} ${OBJ}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
