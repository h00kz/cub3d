#include "../../inc/cub3D.h"

void	ft_get_rgb(char *line, t_color *color)
{
	int i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	i++;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (line[i] < '0' || line[i] > '9')
		printf("error\n");
	color->r = ft_atoi(&line[i]);
	if (color->r > 255)
		printf("error\n");
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	i++;
	color->g = ft_atoi(&line[i]);
	if (color->g > 255)
		printf("error\n");
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	i++;
	color->b = ft_atoi(&line[i]);
	if (color->b > 255)
		printf("error\n");
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (line[i])
		printf("error\n");
}

void	ft_get_info_map(char *file, t_game *game)
{
	int fd;
	int i;
	char *line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		if (line[i] == 'N')
		{
			if (line[i + 1] == 'O')
			{
				game->map->wall_texture->N->path = ft_strdup(&line[i]);
				game->map->wall_texture->N->path = ft_strtrim(game->map->wall_texture->N->path, " ");
			}
		}
		else if (line[i] == 'S')
		{
			if (line[i + 1] == 'O')
			{
				game->map->wall_texture->S->path = ft_strdup(&line[i]);
				game->map->wall_texture->S->path = ft_strtrim(game->map->wall_texture->S->path, " ");

			}
		}
		else if (line[i] == 'W')
		{
			if (line[i + 1] == 'E')
			{
				game->map->wall_texture->W->path = ft_strdup(&line[i]);
				game->map->wall_texture->W->path = ft_strtrim(game->map->wall_texture->W->path, " ");
			}
		}
		else if (line[i] == 'E')
		{
			if (line[i + 1] == 'A')
			{
				game->map->wall_texture->E->path = ft_strdup(&line[i]);
				game->map->wall_texture->E->path = ft_strtrim(game->map->wall_texture->E->path, " ");
			}
		}
		else if (line[i] == 'F')
			ft_get_rgb(line, game->map->floor);
		else if (line[i] == 'C')
			ft_get_rgb(line, game->map->cell);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		if (line[i] == '0' || line[i] == '1')
		{
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line)
	{
		map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

char	**ft_parse_next(char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("error\n");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		if (line[i] == '0' || line[i] == '1')
			break ;
		free(line);
		line = get_next_line(fd);
	}
	i = 1;
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
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
	{
		printf("invalid number of arguments\n");
		exit(1);
	}
	while (argv[1][i])
		i++;
	if (i < 4)
	{
		printf("wrong extension\n");
		exit(1);
	}
	if (argv[1][i - 4] != '.' || argv[1][i - 3] != 'c' || argv[1][i - 2] != 'u' || argv[1][i - 1] != 'b')
	{
		printf("wrong extension\n");
		exit(1);
	}
	ft_get_info_map(argv[1], game);
	free(game->map->map);
	map = ft_parse_next(argv[1]);
	return (map);
}
