#include "../../inc/cub3D.h"

void	ft_skip_whitespace(char *line, int *i)
{
	while ((line[(*i)] >= 9 && line[(*i)] <= 13) || line[(*i)] == 32)
		(*i)++;
}

void	ft_skip_whitespace_newline(char *line, int *i)
{
	while ((line[(*i)] >= 9 && line[(*i)] <= 13) \
		|| line[(*i)] == 32 || line[(*i)] == '\n')
		(*i)++;
}

void	ft_skip_number(char *line, int *i)
{
	while (line[(*i)] >= '0' && line[(*i)] <= '9')
		(*i)++;
}

void	ft_get_rgb(char *line, t_color *color)
{
	int	i;

	i = 0;
	ft_skip_whitespace(line, &i);
	i++;
	ft_skip_whitespace(line, &i);
	if (line[i] < '0' || line[i] > '9')
		printf("error\n");
	color->r = ft_atoi(&line[i]);
	if (color->r > 255)
		printf("error\n");
	ft_skip_number(line, &i);
	i++;
	color->g = ft_atoi(&line[i]);
	if (color->g > 255)
		printf("error\n");
	ft_skip_number(line, &i);
	i++;
	color->b = ft_atoi(&line[i]);
	if (color->b > 255)
		printf("error\n");
	ft_skip_number(line, &i);
	ft_skip_whitespace(line, &i);
	if (line[i])
		printf("error\n");
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

void	ft_check_n(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (line[i + 1] == 'O')
	{
		if (game->map->wall_texture->N->path)
			printf("error\n");
		ft_skip_whitespace(line, &i);
		i += 2;
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
		i += 2;
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
		i += 2;
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
		i += 2;
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

void	ft_check_f_next(char **check)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (check[i])
	{
		j = 0;
		count = 0;
		while (check[i][j])
		{
			if (check[i][j] <= '9' && check[i][j] >= '0')
				count++;
			if ((check[i][j] > '9' || check[i][j] < '0') \
				&& (check[i][j] != '\n' || check[i][j] != '\0') \
				&& ((check[i][j] < 9 && check[i][j] > 13) || check[i][j] == 32))
				printf("error\n");
			j++;
		}
		if (count == 0)
			printf("error\n");
		i++;
	}
	if (i != 3)
		printf("error1\n");
}

void	ft_check_f(char *line, t_game *game)
{
	int		i;
	int		j;
	char	**check;

	i = 1;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
	check = ft_split(&line[i], ',');
	if (check == NULL)
		printf("error\n");
	i = 0;
	ft_check_f_next(check);
	while (check[i])
	{
		free(check[i]);
		i++;
	}
	free(check);
}

void	ft_check_c_next(char **check)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	while (check[i])
	{
		j = 0;
		count = 0;
		while (check[i][j])
		{
			if (check[i][j] <= '9' && check[i][j] >= '0')
				count++;
			if ((check[i][j] > '9' || check[i][j] < '0') \
				&& (check[i][j] != '\n' || check[i][j] != '\0') \
				&& ((check[i][j] < 9 && check[i][j] > 13) || check[i][j] == 32))
				printf("error\n");
			j++;
		}
		if (count == 0)
			printf("error\n");
		i++;
	}
	if (i != 3)
		printf("error\n");
}

void	ft_check_c(char *line, t_game *game)
{
	int		i;
	int		j;
	char	**check;

	i = 1;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
	check = ft_split(&line[i], ',');
	if (check == NULL)
		printf("error\n");
	i = 0;
	ft_check_c_next(check);
	while (check[i])
	{
		free(check[i]);
		i++;
	}
	free(check);
}

void	ft_check_texture(char *line, int i, t_game *game)
{
	if (line[i] == 'N')
		ft_check_n(line, game);
	else if (line[i] == 'S')
		ft_check_s(line, game);
	else if (line[i] == 'W')
		ft_check_w(line, game);
	else if (line[i] == 'E')
		ft_check_e(line, game);
}

void	ft_check_rgb(char *line, int i, t_game *game)
{
	if (line[i] == 'F')
	{
		ft_check_f(line, game);
		ft_get_rgb(line, game->map->floor);
	}
	else if (line[i] == 'C')
	{
		ft_check_c(line, game);
		ft_get_rgb(line, game->map->cell);
	}
}

void	ft_get_info_map(char *file, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		ft_check_texture(line, i, game);
		ft_check_rgb(line, i, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_check_empty_args(game);
}

void	ft_get_map(char *filename, char **map)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		ft_skip_whitespace(line, &i);
		if (line[i] == '0' || line[i] == '1')
			break ;
		free(line);
		line = get_next_line(fd);
	}
	i = -1;
	while (line)
	{
		map[++i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_count_line(char **line, int fd, int *i)
{
	while ((*line))
	{
		(*i) = 0;
		ft_skip_whitespace((*line), i);
		if ((*line)[(*i)] == '0' || (*line)[(*i)] == '1')
			break ;
		free((*line));
		(*line) = get_next_line(fd);
	}
	(*i) = 1;
	while ((*line))
	{
		(*i)++;
		free((*line));
		(*line) = get_next_line(fd);
	}
}

char	**ft_parse_next(char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		printf("error\n");
	line = get_next_line(fd);
	ft_count_line(&line, fd, &i);
	if (line)
		free(line);
	close(fd);
	map = ft_calloc(sizeof(char *), (i + 2));
	ft_get_map(filename, map);
	return (map);
}

char	**parse(int argc, char **argv, t_game *game)
{
	int		i;
	char	**map;

	i = 0;
	if (argc != 2)
		printf("invalid number of arguments\n");
	while (argv[1][i])
		i++;
	if (i < 4)
		printf("wrong extension\n");
	if (argv[1][i - 4] != '.' || argv[1][i - 3] != 'c' \
		|| argv[1][i - 2] != 'u' || argv[1][i - 1] != 'b')
		printf("wrong extension\n");
	ft_get_info_map(argv[1], game);
	free(game->map->map);
	map = ft_parse_next(argv[1]);
	return (map);
}
