SRC					= src/main.c \
					  src/graphics/rect.c \
					  src/graphics/3d_projection.c \
					  src/graphics/map.c \
					  src/graphics/player.c \
					  src/graphics/dda.c \
					  src/logics/raycasting/ray.c \
					  src/utils/color.c \
					  src/utils/pixel_utils.c \
					  src/parsing/parsing.c \
					  src/parsing/verif_map.c \
					  src/parsing/check_player_pos.c \
					  src/inits/game_init.c \
					  src/logics/game_logic.c \
					  src/parsing/skip_char.c \
					  src/parsing/fill_line.c \
					  src/parsing/map_info.c \
					  src/parsing/get_info.c \
					  src/parsing/check_c_f.c \
					  src/parsing/check_texture.c \

LIBFT				= libft/
MLX42				= MLX42/
CFLAGS				=  -g -ldl -lglfw -pthread -lm 
NAME				= cub3D
LIB					= libft/libft.a MLX42/libmlx42.a
INCLUDE				= inc/
# INCLUDEMLX			= MLX42/

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