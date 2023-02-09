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
	game = init_game(argc, argv);
	input_handler(game);
	render(game);
	update(game);
	mlx_terminate(game->mlx);
	return (0);
}