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

void	ft_free2(t_game *game)
{
	if (game->map->wall_texture->N->path)
		free(game->map->wall_texture->N->path);
	if (game->map->wall_texture->S->path)
		free(game->map->wall_texture->S->path);
	if (game->map->wall_texture->E->path)
		free(game->map->wall_texture->E->path);
	if (game->map->wall_texture->W->path)
		free(game->map->wall_texture->W->path);
	ft_free(game);
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
	else if (msg == 4)
	{
		printf("Missing identifier\n");
		ft_free2(game);
	}
	else if (msg == 5)
	{
		printf("Not numeric color\n");
		ft_free2(game);
	}
	exit(1);
}