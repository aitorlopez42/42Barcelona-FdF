/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:34:10 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/12 13:34:13 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/libft/libft.h"
#include "../inc/map.h"
#include "../inc/utils.h"
#include <stdio.h>

void	show_info(t_map *map)
{
	printf("\nMapa Leido [%d][%d][%d][%d] - SIZE[%d] \n", \
	(int)map->limits.axis[X], (int)map->limits.axis[Y], \
	(int)map->limits.axis[Z], map->zmin, map->len);
}

int	line_elems(char *line)
{
	int		i;
	char	**split;

	split = ft_split(line, ' ');
	i = 0;
	while (split[i])
		i++;
	dbl_free(split);
	return (i);
}

void	z_limits(char **splited, t_map *map)
{
	int	i;
	int	valor;

	write(1, "🧱", 4);
	i = 0;
	while (splited[i])
	{
		valor = ft_atoi(&splited[i][0]);
		if (map->limits.axis[Z] < valor)
			map->limits.axis[Z] = valor;
		if (map->zmin > valor)
			map->zmin = valor;
		i++;
	}
}
