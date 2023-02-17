#include "../../inc/cub3D.h"

void	check_player_pos(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (game->map->map[i][j] != ' ' \
				&& game->map->map[i][j] != '1' \
					&& game->map->map[i][j] != '0' \
						&& game->map->map[i][j] != '2')
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
		return ;
	ft_free_split(game->map->map);
	ft_error(7, game);
}

int	count_door_pos(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (game->map->map[i][j] == 'D')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
