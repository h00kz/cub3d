SRC					= src/main.c \
					  src/parsing/parsing.c

LIBFT				= libft/
MLX42				= MLX42/
CFLAGS				=  -g -ldl -lglfw -pthread -lm -Werror -Wextra -Wall
NAME				= cub3D
LIB					= libft/libft.a MLX42/libmlx42.a
INCLUDE				= inc/

blink				= \033[5m
NC					= \033[0m
bold				:= $(shell tput bold)
blue				:= $(shell tput setaf 4)
green				:= $(shell tput setaf 2)
red					:= $(shell tput setaf 1)
sgr0				:= $(shell tput sgr0)

all: $(NAME)

$(NAME):
	@make -sC $(LIBFT) all
	@make -sC $(MLX42) all
	@gcc $(SRC) $(LIB) -o $(NAME) -I$(INCLUDE) $(CFLAGS)
	@printf "[$(green)✔$(sgr0)] $(bold)$(green)Compiling cub3D finished!$(sgr0)\n"

clean:
	@make -sC $(LIBFT) clean
	@make -sC $(MLX42) clean

fclean: clean
	@rm -rf $(NAME)
	@make -sC $(LIBFT) fclean
	@make -sC $(MLX42) fclean
	@printf "[$(red)✔$(sgr0)] $(bold)$(blue)Removing cub3D binary and libft objs done.$(sgr0)\n"

re: fclean all

.PHONY: all clean fclean re