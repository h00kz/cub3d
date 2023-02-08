#include "../../inc/cub3D.h"

int	ft_map_length(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_find_big_line(char **map)
{
	int i;
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


int	ft_check_map_close(char **map)
{
	int i;
	int j;

	i = 0;	
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if (map[i + 1][j] == '0')
					return (0);
				if (map[i][j - 1] == '0')
					return (0);
				if (map[i - 1][j] == '0')
					return (0);
				if (map[i][j + 1] == '0')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}



char	**ft_verif_map(char **map)
{	
	int i;
	int j;
	int l;
	int k;
	char **new_map;

	i = 0;
	j = 0;
	new_map = ft_calloc(sizeof(char *), (ft_map_length(map) + 5));
	while (i < (ft_map_length(map) + 4))
	{
		new_map[i] = ft_calloc(sizeof(char), ft_find_big_line(map) + 4);
		i++;
	}
	i = 0;
	j = 0;
	while (j <= ft_find_big_line(map) + 2)
	{
		new_map[0][j] = '1';
		j++;
	}
	j = 0;
	while (j <= ft_find_big_line(map) + 2)
	{
		if (j == 0 || j == ft_find_big_line(map) + 2)
			new_map[1][j] = '1';
		else
			new_map[1][j] = ' ';
		j++;
	}
	j = 0;
	while (j <= ft_find_big_line(map) + 2)
	{
		new_map[ft_map_length(map) + 3][j] = '1';
		j++;
	}
	j = 0;
	while (j <= ft_find_big_line(map) + 2)
	{
		if (j == 0 || j == ft_find_big_line(map) + 2)
			new_map[ft_map_length(map) + 2][j] = '1';
		else
			new_map[ft_map_length(map) + 2][j] = ' ';
		j++;
	}
	i = 2;
	j = 0;
	while (i <= ft_map_length(map) + 1)
	{
		new_map[i][0] = '1';
		new_map[i][1] = ' ';
		new_map[i][ft_find_big_line(map) + 2] = '1';
		new_map[i][ft_find_big_line(map) + 1] = ' ';
		i++;
	}
	i = 2;
	k = 0;
	while (map[k])
	{
		l = 0;
		j = 2;
		while (new_map[i][j] != '1')
		{
			if (j - 2 >= (int)ft_strlen(map[k]) || map[k][j - 2] == '\n')
			{
				new_map[i][j] = ' ';
				j++;
			}
			else
			{
				new_map[i][j] = map[k][l];
				j++;
				l++;
			}
		}
		i++;
		k++;
	}
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	if (ft_check_map_close(new_map) == 0)
	{
		printf("map error not close\n");
		exit (0);
	}
	return (new_map);
}
