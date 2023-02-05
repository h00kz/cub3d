#include "../../inc/cub3D.h"

t_player	*init_player()
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player->position = ft_calloc(1, sizeof(t_vec));
	player->walk_dir = ft_calloc(1, sizeof(t_vec));
	player->turn_dir = ft_calloc(1, sizeof(t_vec));
	player->rays = init_rays(NB_RAYS);
	player->position->x = (10 * MAP_TILE / 2) * MINIMAP_SCALE_FACTOR;
	player->position->y = (10 * MAP_TILE / 2) * MINIMAP_SCALE_FACTOR;
	player->walk_dir->x = 0;
	player->walk_dir->y = 0;
	player->turn_dir->x = 0;
	player->turn_dir->y = 0;
	player->rot_angle = 2 / PI;
	player->walk_speed = 100;
	player->turn_speed = 45 * (PI / 180.0);
	return (player);
}

void	render_minimap_player(t_game *game)
{
	t_vec	end_line;
	t_vec	pos_offset;

	pos_offset = *(game->player->position);
	pos_offset.x -= 5/2;
	pos_offset.y -= 5/2;
	end_line.x = (game->player->position->x) + cos(game->player->rot_angle) * (40 * MINIMAP_SCALE_FACTOR);
	end_line.y = (game->player->position->y) + sin(game->player->rot_angle) * (40 * MINIMAP_SCALE_FACTOR);
	draw_line(game, game->player->position, &end_line, 0);
	draw_rect(game, pos_offset, (t_vec){5, 5}, rgba2int(10, 230, 12, 255));
}

void	move_minimap_player(t_game *game)
{
	float	move_step;
	t_vec	new_pos;

	normalize_angle(&(game->player->rot_angle));
	game->player->rot_angle += game->player->turn_dir->x * game->player->turn_speed * game->mlx->delta_time;
	move_step = game->player->walk_dir->x * game->player->walk_speed * game->mlx->delta_time;
	new_pos.x = game->player->position->x + cos(game->player->rot_angle) * move_step;
	new_pos.y = game->player->position->y + sin(game->player->rot_angle) * move_step;
	if (!get_collision(game, new_pos))
	{
		game->player->position->x = new_pos.x;
		game->player->position->y = new_pos.y;
	}
}