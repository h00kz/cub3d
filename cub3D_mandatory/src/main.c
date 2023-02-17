/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:58:42 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 14:58:43 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	get_width(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
		i++;
	return (i + 1);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game(argc, argv);
	mlx_loop_hook(game->mlx, &game_routine, game);
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	ft_free3(game);
	return (0);
}
