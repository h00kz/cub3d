#include "../../inc/cub3D.h"

void	check_player_pos(char **map)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'O' || map[i][j] == 'E' || map[i][j] == 'S')
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
		return ;
	printf("Error\n");
	exit(0);
}