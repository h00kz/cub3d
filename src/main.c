#include "../inc/cub3D.h"

int main(int argc, char **argv)
{
	t_game	*game;

	// char	**map;

	// map = parse(argc, argv);
	// ft_verif_map(map);
	(void)argc;
	(void)argv;
	game = init_game();
	game->last_time = mlx_get_time();
	input_handler(game);
	render(game);
	update(game);
	mlx_terminate(game->mlx);
	return (0);
}