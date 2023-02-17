#include "../../inc/cub3D.h"

static void	check_rgb(t_game *game, char *line, t_color *color, int *i)
{
	color->r = ft_atoi(&line[(*i)]);
	if (color->r > 255)
	{
		free(line);
		ft_error(5, game);
	}
	ft_skip_number(line, i);
	(*i)++;
	color->g = ft_atoi(&line[(*i)]);
	if (color->g > 255)
	{
		free(line);
		ft_error(5, game);
	}
	ft_skip_number(line, i);
	(*i)++;
	color->b = ft_atoi(&line[(*i)]);
	if (color->b > 255)
	{
		free(line);
		ft_error(5, game);
	}
}

void	ft_get_rgb(char *line, t_color *color, t_game *game)
{
	int	i;

	i = 0;
	ft_skip_whitespace(line, &i);
	i++;
	ft_skip_whitespace(line, &i);
	if (line[i] < '0' || line[i] > '9')
	{
		free(line);
		ft_error(5, game);
	}
	check_rgb(game, line, color, &i);
	ft_skip_number(line, &i);
	ft_skip_whitespace(line, &i);
	if (line[i])
	{
		free(line);
		ft_error(5, game);
	}
}

void	ft_get_info_map(char *file, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error_file(game);
	line = get_next_line(fd);
	if (!line)
		ft_error(0, game);
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
