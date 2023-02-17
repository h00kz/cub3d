/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:04:10 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:04:10 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	move_straf(t_game *game, t_vec *new_pos_lr, float move_step_lr)
{
	new_pos_lr->x = game->player->position->x + \
		cos(game->player->rot_angle + (PI / 2.0)) * move_step_lr;
	new_pos_lr->y = game->player->position->y + \
		sin(game->player->rot_angle + (PI / 2.0)) * move_step_lr;
	if (get_collision(game, *new_pos_lr))
	{
		game->player->position->x = new_pos_lr->x;
		game->player->position->y = new_pos_lr->y;
	}
}

void	move_player(t_game *game)
{
	float	move_step_lr;
	float	move_step_fb;
	t_vec	new_pos_fb;
	t_vec	new_pos_lr;

	look_mouse(game);
	move_step_fb = game->player->walk_dir->x * \
		game->player->walk_speed * game->mlx->delta_time;
	move_step_lr = game->player->walk_dir->y * \
		game->player->walk_speed * game->mlx->delta_time;
	move_straf(game, &new_pos_lr, move_step_lr);
	new_pos_fb.x = game->player->position->x \
		+ cos(game->player->rot_angle) * move_step_fb;
	new_pos_fb.y = game->player->position->y \
		+ sin(game->player->rot_angle) * move_step_fb;
	if (get_collision(game, new_pos_fb))
	{
		game->player->position->x = new_pos_fb.x;
		game->player->position->y = new_pos_fb.y;
	}
}
