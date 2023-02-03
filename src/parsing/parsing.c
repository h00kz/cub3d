#include "../../inc/cub3D.h"

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
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
}

char	**ft_parse_next(char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	map = malloc(sizeof(char *) * i);
	ft_get_map(filename, map);
	return (map);
}

char	**parse(int argc, char **argv)
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
	map = ft_parse_next(argv[1]);
	return (map);
}
