GREEN	= \033[1;32m
RED		= \033[0;31m
BLUE	= \033[0;34m
YELLOW	= \033[1;33m
CYAN	= \033[0;36m
RESET	= \033[0m

NAME		=	cub3D

CC			=	cc

FLAG		=	-Wall -Werror -Wextra -g3 -I./minilibx-linux -I./includes

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_LIB 	=	./minilibx-linux/libmlx.a -lX11 -lXext

C_FILE		=	main/main							\
				main/free							\
				main/exit							\
				parsing/init_parsing				\
				parsing/parsing						\
				parsing/parsing_utils				\
				parsing/parsing_walls				\
				parsing/parsing_checker				\
				render/render						\
				render/minimap						\
				render/move							\

SRC_DIR		=	./srcs/

SRC			=	$(addsuffix .c, $(addprefix $(SRC_DIR),$(C_FILE)))

OBJ			=	$(SRC:.c=.o)

.c.o:
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	@echo "$(BLUE)Compiling $(LIBFT_PATH)...$(RESET)"
	@make -sC $(LIBFT_PATH)
	@echo "$(GREEN)libft.a created$(RESET)"

${MLX_LIB}:
	@echo "$(BLUE)Compiling MLX...$(RESET)"
	@make -sC ./minilibx-linux
	@echo "$(GREEN)MLX created$(RESET)"

$(NAME): $(LIBFT_LIB) ${MLX_LIB} $(OBJ)
	@echo "$(BLUE)Compiling $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(LIBFT_LIB) ${MLX_LIB} $(FLAG) -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created$(RESET)"

clean:
	@echo "$(RED)Deleting object files in $(LIBFT_PATH)...$(RESET)"
	@make clean -sC $(LIBFT_PATH)
	@echo "$(GREEN)Done$(RESET)"
	@echo "$(RED)Deleting object files in MLX...$(RESET)"
	@make clean -sC ./minilibx-linux/
	@echo "$(GREEN)Done$(RESET)"
	@echo "$(RED)Deleting $(NAME) object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)Done$(RESET)"

fclean: clean
	@echo "$(RED)Deleting $(NAME) executable...$(RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "$(GREEN)Done$(RESET)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
