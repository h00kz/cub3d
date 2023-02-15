/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:12:18 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/01 14:49:48 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static float	ft_float(char *str)
{
	float	value;
	int		i;

	i = 0;
	value = 0;
	if (str[i] <= '0' && str[i] >= '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	i--;
	while (i >= 0)
	{
		value = (value / 10) + (str[i] - 48);
		i--;
	}
	value /= 10;
	return (value);
}

float	ft_atof(char *str)
{
	int		i;
	float	sign;
	float	value;
	float	verif;

	i = 0;
	verif = 0;
	sign = 1;
	value = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] == '.')
		verif = ft_float(&str[++i]);
	return (((value + verif) * sign));
}
