/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:03:57 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:03:57 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
