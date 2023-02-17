#include "../../inc/cub3D.h"

void	ft_error_next(int msg, t_game *game)
{
	if (msg == 4)
	{
		printf("Missing identifier\n");
		ft_free2(game);
	}
	else if (msg == 5)
	{
		printf("Missing number(s) to make a color\n");
		ft_free2(game);
	}
	else if (msg == 5)
	{
		printf("Invalid number(s) to make a color\n");
		ft_free2(game);
	}
	else if (msg == 6)
	{
		printf("Missing a map argument\n");
		ft_free2(game);
	}
	else if (msg == 7)
	{
		printf("Invalid map\n");
		ft_free2(game);
	}
}

void	ft_error(int msg, t_game *game)
{
	printf("Error\n");
	if (msg == 0)
	{
		printf("Invalid number of arguments\n");
		ft_free(game);
	}
	else if (msg == 1)
	{
		printf("Wrong extension\n");
		ft_free(game);
	}
	else if (msg == 2)
	{
		printf("There is already a path\n");
		ft_free2(game);
	}
	else if (msg == 3)
	{
		printf("No path found\n");
		ft_free2(game);
	}
	else
		ft_error_next(msg, game);
	exit(1);
}
