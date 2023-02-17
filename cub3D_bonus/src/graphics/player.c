/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:04:19 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:04:19 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

t_player	*init_player(t_game *game)
{
	t_player	*player;
	t_vec		pos;

	player = ft_calloc(1, sizeof(t_player));
	player->position = ft_calloc(1, sizeof(t_vec));
	player->walk_dir = ft_calloc(1, sizeof(t_vec));
	player->turn_dir = ft_calloc(1, sizeof(t_vec));
	player->weapon = ft_calloc(4, sizeof(t_texture));
	player->rays = init_rays(NB_RAYS);
	player->dir = get_player_pos(game->map->map, &pos);
	player->position->x = (MAP_TILE * (pos.x)) + MAP_TILE / 2;
	player->position->y = (MAP_TILE * (pos.y)) + MAP_TILE / 2;
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
	int	i;
	int	j;

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
				return (map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	look_mouse(t_game *game)
{
	int	x;
	int	y;
	int	xoffset;
	int	yoffset;

	xoffset = WIN_HALF_W;
	yoffset = WIN_HALF_H;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	normalize_angle(&(game->player->rot_angle));
	game->player->rot_angle += ((x - xoffset) * 0.001);
	mlx_set_mouse_pos(game->mlx, xoffset, yoffset);
}

void	weapon_fire(t_game *game, int frame, int *i_frame)
{
	if (game->player->fire)
	{
		if (!(frame % 2))
		{
			mlx_draw_texture(game->weapon, \
				game->player->weapon[*i_frame].tex_img, 0, 0);
			(*i_frame)++;
		}
		if (*i_frame == 4)
		{
			*i_frame = 0;
			mlx_draw_texture(game->weapon, \
				game->player->weapon[*i_frame].tex_img, 0, 0);
			game->player->fire = false;
		}
	}
}
