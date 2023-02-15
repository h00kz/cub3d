/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:31:50 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/15 18:24:15 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_line(t_game *game, t_vec *start, t_vec *end, int color)
{
	t_vec	delta;
	t_vec	pos_inc;
	t_vec	current_pos;
	float	longest_side_len;
	int		i;

	i = 0;
	delta.x = (end->x - start->x);
	delta.y = (end->y - start->y);
	longest_side_len = fmax(fabs(delta.x), fabs(delta.y));
	pos_inc.x = delta.x / longest_side_len;
	pos_inc.y = delta.y / longest_side_len;
	current_pos.x = start->x;
	current_pos.y = start->y;
	while (i < longest_side_len)
	{
		put_pixel(game->mlx_img, current_pos.x, current_pos.y, color);
		current_pos.x += pos_inc.x;
		current_pos.y += pos_inc.y;
		i++;
	}
}

void	draw_line_mipmap(t_game *game, t_vec *start, t_vec *end, int color)
{
	t_vec	delta;
	t_vec	pos_inc;
	t_vec	current_pos;
	float	longest_side_len;
	int		i;

	i = 0;
	delta.x = (end->x - start->x);
	delta.y = (end->y - start->y);
	longest_side_len = fmax(fabs(delta.x), fabs(delta.y));
	pos_inc.x = delta.x / longest_side_len;
	pos_inc.y = delta.y / longest_side_len;
	current_pos.x = start->x;
	current_pos.y = start->y;
	while (i < longest_side_len)
	{
		if (current_pos.x >= 0 && current_pos.x < WIN_WIDTH / 5 && current_pos.y >= 0 && current_pos.y < WIN_HEIGHT / 5)
			put_pixel(game->minimap, current_pos.x, current_pos.y, color);
		current_pos.x += pos_inc.x;
		current_pos.y += pos_inc.y;
		i++;
	}
}

