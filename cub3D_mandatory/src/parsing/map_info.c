#include "../../inc/cub3D.h"

int	ft_map_length(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_find_big_line(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if (len < (int)ft_strlen(map[i]))
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}
