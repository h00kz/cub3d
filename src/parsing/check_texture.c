#include "../../inc/cub3D.h"

void	ft_check_n(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'O')
	{
		if (game->map->wall_texture->N->path)
			printf("error\n");
		ft_skip_whitespace(line, &i);
		i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] == '\0')
			printf("error\n");
		while (line[i] && ((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] != '\0')
			printf("error\n");
		game->map->wall_texture->N->path = ft_strdup(&line[i]);
		game->map->wall_texture->N->path \
			= ft_strtrim(game->map->wall_texture->N->path, " \n");
	}
	else
		printf("error");
	printf("%s\n",game->map->wall_texture->N->path );
}

void	ft_check_s(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'O')
	{
		if (game->map->wall_texture->S->path)
			printf("error\n");
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] == '\0')
			printf("error\n");
		while (line[i] && ((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		if (line[i] != '\0')
			printf("error\n");
		game->map->wall_texture->S->path = ft_strdup(&line[i]);
		game->map->wall_texture->S->path \
			= ft_strtrim(game->map->wall_texture->S->path, " \n");
	}
	else
		printf("error");
}

void	ft_check_w(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'E')
	{
		if (game->map->wall_texture->W->path)
			printf("error\n");
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] == '\0')
			printf("error\n");
		while (line[i] && ((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		if (line[i] != '\0')
			printf("error\n");
		game->map->wall_texture->W->path = ft_strdup(&line[i]);
		game->map->wall_texture->W->path \
			= ft_strtrim(game->map->wall_texture->W->path, " \n");
	}
	else
		printf("error");
}

void	ft_check_e(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'A')
	{
		if (game->map->wall_texture->E->path)
			printf("error\n");
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		i++;
		ft_skip_whitespace_newline(line, &i);
		if (line[i] == '\0')
			printf("error\n");
		while (line[i] && ((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		if (line[i] != '\0')
			printf("error\n");
		game->map->wall_texture->E->path = ft_strdup(&line[i]);
		game->map->wall_texture->E->path \
			= ft_strtrim(game->map->wall_texture->E->path, " \n");
	}
	else
		printf("error");
}

void	ft_check_empty_args(t_game *game)
{
	if (!(game->map->wall_texture->E->path))
		printf("error\n");
	if (!(game->map->wall_texture->N->path))
		printf("error\n");
	if (!(game->map->wall_texture->S->path))
		printf("error\n");
	if (!(game->map->wall_texture->W->path))
		printf("error\n");
}
