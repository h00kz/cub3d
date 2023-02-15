#include "../../inc/cub3D.h"

void	ft_check_f_next(char **check, t_game *game)
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
				ft_error(5, game);
			j++;
		}
		if (count == 0)
			printf("error1\n");
		i++;
	}
	if (i != 3)
		printf("error2\n");
}

void	ft_check_f(char *line)
{
	int		i;
	char	**check;

	i = 1;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
	check = ft_split(&line[i], ',');
	if (check == NULL)
		printf("error\n");
	i = 0;
	ft_check_f_next(check, game);
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
			printf("error1\n");
		i++;
	}
	if (i != 3)
		printf("error2\n");
}

void	ft_check_c(char *line)
{
	int		i;
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
