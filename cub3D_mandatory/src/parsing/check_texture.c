/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:32 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 14:59:38 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	ft_check_n(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'O')
	{
		if (game->map->wall_texture->n->path)
		{
			free(line);
			ft_error(2, game);
		}
		while (line[i] && ((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] == '\0')
		{
			free(line);
			ft_error(3, game);
		}
		game->map->wall_texture->n->path = ft_strtrim(&line[i], " \n");
	}	
	else
	{
		free(line);
		ft_error(4, game);
	}
}

void	ft_check_s(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'O')
	{
		if (game->map->wall_texture->s->path)
		{
			free(line);
			ft_error(2, game);
		}
		while (line[i] && ((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] == '\0')
		{
			free(line);
			ft_error(3, game);
		}
		game->map->wall_texture->s->path = ft_strtrim(&line[i], " \n");
	}	
	else
	{
		free(line);
		ft_error(4, game);
	}
}

void	ft_check_w(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'E')
	{
		if (game->map->wall_texture->w->path)
		{
			free(line);
			ft_error(2, game);
		}
		while (line[i] && ((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] == '\0')
		{
			free(line);
			ft_error(3, game);
		}
		game->map->wall_texture->w->path = ft_strtrim(&line[i], " \n");
	}	
	else
	{
		free(line);
		ft_error(4, game);
	}
}

void	ft_check_e(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'A')
	{
		if (game->map->wall_texture->e->path)
		{
			free(line);
			ft_error(2, game);
		}
		while (line[i] && ((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] == '\0')
		{
			free(line);
			ft_error(3, game);
		}
		game->map->wall_texture->e->path = ft_strtrim(&line[i], " \n");
	}	
	else
	{
		free(line);
		ft_error(4, game);
	}
}

void	ft_check_empty_args(t_game *game)
{
	if (!(game->map->wall_texture->e->path))
		ft_error(6, game);
	if (!(game->map->wall_texture->n->path))
		ft_error(6, game);
	if (!(game->map->wall_texture->s->path))
		ft_error(6, game);
	if (!(game->map->wall_texture->w->path))
		ft_error(6, game);
	if (game->map->cell->r == -1)
		ft_error(6, game);
	if (game->map->floor->r == -1)
		ft_error(6, game);
}
