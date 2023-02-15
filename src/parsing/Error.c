#include "../../inc/cub3D.h"

void	ft_free(t_game *game)
{
	free(game->ray_inter_v.interc);
	free(game->ray_inter_v.next_touch);
	free(game->ray_inter_v.to_check);
	free(game->ray_inter_v.step);
	free(game->ray_inter_h.interc);
	free(game->ray_inter_h.next_touch);
	free(game->ray_inter_h.to_check);
	free(game->ray_inter_h.step);
	free(game->map->wall_texture->S);
	free(game->map->wall_texture->N);
	free(game->map->wall_texture->E);
	free(game->map->wall_texture->W);
	free(game->map->wall_texture);
	free(game->map->map);
	free(game->map->floor);
	free(game->map->cell);
	free(game->map);
	free(game);
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
		printf("Error there is already a path\n");
	exit(1);
}