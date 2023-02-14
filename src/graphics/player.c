#include "../../inc/cub3D.h"

t_player	*init_player(t_game *game)
{
	t_player	*player;
	t_vec		pos;

	
	player = ft_calloc(1, sizeof(t_player));
	player->position = ft_calloc(1, sizeof(t_vec));
	player->walk_dir = ft_calloc(1, sizeof(t_vec));
	player->turn_dir = ft_calloc(1, sizeof(t_vec));
	player->rays = init_rays(NB_RAYS);
	player->dir = get_player_pos(game->map->map, &pos);
	player->position->x = (MINIMAP_TILE * (pos.x)) + MINIMAP_TILE / 2;
	player->position->y = (MINIMAP_TILE * (pos.y)) + MINIMAP_TILE / 2;
	player->walk_dir->x = 0;
	player->walk_dir->y = 0;
	player->turn_dir->x = 0;
	player->turn_dir->y = 0;
	player->rot_angle = set_player_dir(player->dir);
	player->walk_speed = 100.0;
	player->turn_speed = 90.0 * (PI / 180.0);
	return (player);
}

float	set_player_dir(char dir)
{
	if (dir == 'N')
		return (-90.0 * (PI / 180.0));
	else if (dir == 'S')
		return (90.0 * (PI / 180.0));
	else if (dir == 'E')
		return ((PI / 180.0));
	else if (dir == 'W')
		return (-180.0 * (PI / 180.0));
	return (0);
}

char	get_player_pos(char **map, t_vec *pos)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
			{
				pos->x = j;
				pos->y = i;
				return(map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	render_minimap_player(t_game *game)
{
	t_vec	end_line;
	t_vec	pos_offset;

	pos_offset = *(game->player->position);
	pos_offset.x -= (5 / 2) * MINIMAP_SCALE_FACTOR;
	pos_offset.y -= (5 / 2) * MINIMAP_SCALE_FACTOR;
	end_line.x = (game->player->position->x) + cos(game->player->rot_angle) * (40 * MINIMAP_SCALE_FACTOR);
	end_line.y = (game->player->position->y) + sin(game->player->rot_angle) * (40 * MINIMAP_SCALE_FACTOR);
	draw_line(game, game->player->position, &end_line, 0);
	draw_rect(game, pos_offset, (t_vec){5 * MINIMAP_SCALE_FACTOR, 5 * MINIMAP_SCALE_FACTOR}, rgba2int(10, 230, 12, 255));
}

void	move_player(t_game *game)
{
	float	move_step_lr;
	float	move_step_fb;
	t_vec	new_pos_fb;
	t_vec	new_pos_lr;

	// BONUS SOURIS
	// int x,y = 0;
	// int	xoffset, yoffset = 0;
	// mlx_get_mouse_pos(game->mlx, &x, &y);
	// xoffset = WIN_HALF_W;
	// yoffset = WIN_HALF_H;
	// (void)yoffset;
	// normalize_angle(&(game->player->rot_angle));
	// float mouse_x = x - xoffset;
	// game->player->rot_angle += (mouse_x * 0.001);
	// mlx_set_mouse_pos(game->mlx, xoffset, yoffset);

	// MANDATORY (sans mouse)
	game->player->rot_angle += (game->player->turn_dir->x * game->player->turn_speed) * game->mlx->delta_time;

	move_step_fb = game->player->walk_dir->x * game->player->walk_speed * game->mlx->delta_time;
	move_step_lr = game->player->walk_dir->y * game->player->walk_speed * game->mlx->delta_time;
	new_pos_lr.x = game->player->position->x + cos(game->player->rot_angle + (PI / 2.0)) * move_step_lr;
	new_pos_lr.y = game->player->position->y + sin(game->player->rot_angle + (PI / 2.0)) * move_step_lr;
	if (get_collision(game, new_pos_lr))
	{
		game->player->position->x = new_pos_lr.x;
		game->player->position->y = new_pos_lr.y;
	}
	new_pos_fb.x = game->player->position->x + cos(game->player->rot_angle) * move_step_fb;
	new_pos_fb.y = game->player->position->y + sin(game->player->rot_angle) * move_step_fb;
	if (get_collision(game, new_pos_fb))
	{
		game->player->position->x = new_pos_fb.x;
		game->player->position->y = new_pos_fb.y;
	}
}