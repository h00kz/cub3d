/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:21 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/15 14:51:43 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_rect(t_game *game, t_vec pos, t_vec size, int color)
{
	int	y;
	int	x;

	y = pos.y;
	while (y <= pos.y + size.y)
	{
		x = pos.x;
		while (x <= pos.x + size.x)
		{
			put_pixel(game->mlx_img, x, y, color);
			x++;
		}
		y++;
	}
}
