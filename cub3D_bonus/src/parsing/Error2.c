/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:03:44 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:05:52 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	ft_error_next(int msg, t_game *game)
{
	if (msg == 4)
	{
		printf("Missing identifier\n");
		ft_free2(game);
	}
	else if (msg == 5)
	{
		printf("Missing number(s) to make a color\n");
		ft_free2(game);
	}
	else if (msg == 5)
	{
		printf("Invalid number(s) to make a color\n");
		ft_free2(game);
	}
	else if (msg == 6)
	{
		printf("Missing a map argument\n");
		ft_free2(game);
	}
	else if (msg == 7)
	{
		printf("Invalid map\n");
		ft_free2(game);
	}
}

void	ft_error(int msg, t_game *game)
{
	printf("Error\n");
	if (msg == 0)
	{
		printf("Invalid number of arguments\n");
		ft_free(game);
	}
	else if (msg == 1)
	{
		printf("Wrong extension\n");
		ft_free(game);
	}
	else if (msg == 2)
	{
		printf("There is already a path\n");
		ft_free2(game);
	}
	else if (msg == 3)
	{
		printf("No path found\n");
		ft_free2(game);
	}
	else
		ft_error_next(msg, game);
	exit(1);
}

void	ft_error_file(t_game *game)
{
	printf("Error\nInvalid file\n");
	ft_free(game);
	exit(1);
}

void	error_png2(char *msg, t_game *game)
{
	ft_putendl_fd(msg, 2);
	mlx_terminate(game->mlx);
	ft_free3(game);
	exit(1);
}
