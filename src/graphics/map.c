#include "../../inc/cub3D.h"

t_map	*init_map()
{
	t_map	*map;

	int map_tmp[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
	map = ft_calloc(1, sizeof(t_map));
	ft_memmove(map->map_tab, map_tmp, 4 * (10*10));
	return (map);
}

int	get_collision(t_game *game, t_vec pos)
{
	int	map_x_idx;
	int	map_y_idx;

	if (pos.x < 0 || pos.x > 10 * MAP_TILE * MINIMAP_SCALE_FACTOR || \
		pos.y < 0 || pos.y > 10 * MAP_TILE * MINIMAP_SCALE_FACTOR)
		return (TRUE);
	map_x_idx = (int)floor(pos.x / MAP_TILE);
	map_y_idx = (int)floor(pos.y / MAP_TILE);
	return (game->map->map_tab[map_y_idx][map_x_idx] != 0);
}

int	is_in_map(t_vec pos)
{
	return (pos.x >= 0 && pos.x < 10 * MAP_TILE && pos.y >= 0 && pos.y < 10 * MAP_TILE);
}

void	render_minimap(t_game *game)
{
	int	x;
	int y;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			int tilex = x * MAP_TILE;
			int tiley = y * MAP_TILE;
			int tilec = game->map->map_tab[y][x] != 1 ? rgba2int(0xff, 0xff, 0xff, 0xff) : rgba2int(0, 0, 0, 0xff);
			draw_rect(game, (t_vec){tilex * MINIMAP_SCALE_FACTOR, tiley * MINIMAP_SCALE_FACTOR}, \
							(t_vec){MAP_TILE * MINIMAP_SCALE_FACTOR, MAP_TILE * MINIMAP_SCALE_FACTOR}, tilec);
			x++;
		}
		y++;
	}
}