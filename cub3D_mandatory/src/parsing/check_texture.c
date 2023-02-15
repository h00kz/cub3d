#include "../../inc/cub3D.h"

void	ft_check_n(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'O')
	{
		if (game->map->wall_texture->N->path)
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
		game->map->wall_texture->N->path = ft_strtrim(&line[i], " \n");
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
		if (game->map->wall_texture->S->path)
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
		game->map->wall_texture->S->path = ft_strtrim(&line[i], " \n");
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
		if (game->map->wall_texture->W->path)
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
		game->map->wall_texture->W->path = ft_strtrim(&line[i], " \n");
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
		if (game->map->wall_texture->E->path)
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
		game->map->wall_texture->E->path = ft_strtrim(&line[i], " \n");
	}	
	else
	{
		free(line);
		ft_error(4, game);
	}
}

void	ft_check_empty_args(t_game *game)
{
	if (!(game->map->wall_texture->E->path))
		ft_error(6, game);
	if (!(game->map->wall_texture->N->path))
		ft_error(6, game);
	if (!(game->map->wall_texture->S->path))
		ft_error(6, game);
	if (!(game->map->wall_texture->W->path))
		ft_error(6, game);
}
