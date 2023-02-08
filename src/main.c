#include "../inc/cub3D.h"

int get_width(char **map)
{
	int i;

	i = 0;
	while (map[0][i])
		i++;
	return (i + 1);
}

int get_height(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int main(int argc, char **argv)
{
	t_game	*game;

	game = init_game();
	game->map->map = parse(argc, argv, game);
	game->map->map = ft_verif_map(game->map->map);
	game->map->height = get_height(game->map->map);
	game->map->width = get_width(game->map->map);
	game->last_time = mlx_get_time();
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	input_handler(game);
	render(game);
	update(game);
	mlx_terminate(game->mlx);
	return (0);
}