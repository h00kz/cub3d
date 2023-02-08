#include "../../inc/cub3D.h"

t_map	*init_map()
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	map->wall_texture = malloc(sizeof(t_wall) * 1);
	map->wall_texture->S = malloc(sizeof(t_texture) * 1);
	map->wall_texture->N = malloc(sizeof(t_texture) * 1);
	map->wall_texture->E = malloc(sizeof(t_texture) * 1);
	map->wall_texture->W = malloc(sizeof(t_texture) * 1);
	map->map = ft_calloc(sizeof(char), 1);
	map->floor = ft_calloc(sizeof(t_color), 1);
	map->cell = ft_calloc(sizeof(t_color), 1);
	return (map);
}

int	get_collision(t_game *game, t_vec pos)
{
	int	map_x_idx;
	int	map_y_idx;

	if (pos.x < 0 || pos.x > game->map->width * (MAP_TILE) || \
		pos.y < 0 || pos.y > game->map->height * (MAP_TILE))
		return (TRUE);
	map_x_idx = floor(pos.x / (MAP_TILE));
	map_y_idx = floor(pos.y / (MAP_TILE));
	return (game->map->map[map_y_idx][map_x_idx] != '1');
}

int	is_in_map(t_game *game, t_vec pos)
{
	return (pos.x >= 0 && pos.x < game->map->width * MAP_TILE && pos.y >= 0 && pos.y < game->map->height * MAP_TILE);
}

void	render_minimap(t_game *game)
{
	int	x;
	int y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			int tilex = x * MAP_TILE;
			int tiley = y * MAP_TILE;
			int tilec = game->map->map[y][x] != '1' ? rgba2int(0xff, 0xff, 0xff, 0xff) : rgba2int(0, 0, 0, 0xff);
			draw_rect(game, (t_vec){tilex * MINIMAP_SCALE_FACTOR, tiley * MINIMAP_SCALE_FACTOR}, \
							(t_vec){MAP_TILE * MINIMAP_SCALE_FACTOR, MAP_TILE * MINIMAP_SCALE_FACTOR}, tilec);
			x++;
		}
		y++;
	}
}