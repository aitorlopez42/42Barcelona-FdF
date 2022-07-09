/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:26:13 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 13:26:21 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/get_next_line.h"
#include "../lib/libft/libft.h"
#include "../inc/map.h"
#include "../inc/utils.h"
#include "../inc/draw_utils.h"
#include <stdio.h>
#include <fcntl.h>

void	show_info(t_map *map)
{
	printf("\nMapa Leido [%d][%d][%d][%d] - SIZE[%d] \n", (int)map->limits.axis[x], (int)map->limits.axis[y], (int)map->limits.axis[z], map->zmin, map->len);
}


/* 
*	Acording the z value of the point and de max and min values of the map
*	this function set the color needed of the point received.
*	All the colors are defined in fdf.h 
*/

void	load_color(int max, int min, t_point *point, t_colors	colors)
{
	point->color = DEFAULT_COLOR;
	if (point->axis[z] == max)
		point->color = colors.topcolor;
	else if (point->axis[z] == 0)
		point->color = colors.groundcolor;
	else if (point->axis[z] == min && min != 0)
		point->color = colors.bottomcolor;
	else if (point->axis[z] > 0)
		point->color = gradient(colors.groundcolor, colors.topcolor, max, point->axis[z]);
	else
		point->color = gradient(colors.bottomcolor, colors.groundcolor, -min, - (min - point->axis[z]));
}


/* 
*	Splits the info of line to storage
*	the points in the map->point array. 
*	Using map->len as index of the array
*/

void	load_points(char *line, t_map *map, int numline)
{
	char	**splited;
	char	**color;
	int		i;

	write(1, ".", 1);
	splited = ft_split(line, ' ');
	i = 0;
	while (splited[i])
	{
		map->points[map->len].axis[z] = ft_atoi(&splited[i][0]);
		map->points[map->len].axis[x] = i - map->limits.axis[x] / 2;
		map->points[map->len].axis[y] = numline - map->limits.axis[y] / 2;
		load_color((int)map->limits.axis[z], map->zmin, &map->points[map->len], map->colors);
		if (ft_strchr(splited[i], ',') != 0)
		{
			color = ft_split(splited[i], ',');
			map->points[map->len].color = strtol(color[1] + 2, NULL, 16);
			dbl_free(color);
		}
		i++;
		map->len++;
	}
	dbl_free(splited);
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
	int valor;

	i = 0;
	while (splited[i])
	{
		valor = ft_atoi(&splited[i][0]);
		if (map->limits.axis[z] < valor)
			map->limits.axis[z] = valor;
		if (map->zmin > valor)
			map->zmin = valor;
		i++;
	}
}

/* 
*	This function determinates the max values x, y, z of the map
*	and return -1 if the maps has different line sizes.
*/

int	map_size(int fd, t_map *map)
{
	char	*line;
	char	**splited;
	int		linelen;

	map->len = 0;

	map->limits.axis[y] = 0;
	map->limits.axis[z] = 0;
	map->zmin = 0;
	line = get_next_line(fd);
	map->limits.axis[x] = line_elems(line);	
	while (line != NULL)
	{
		write(1, "*", 1);
		splited = ft_split(line, ' ');
		z_limits(splited, map);
		linelen = line_elems(line);
		if (map->limits.axis[x] != linelen)
		{
			printf( "Map Error\n");
			return (-1);
		}
		map->limits.axis[x] = linelen;
		map->len += map->limits.axis[x];
		map->limits.axis[y]++;
		dbl_free(splited);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}



int	load_map(t_map *map, char *path)
{
	int		fd;
	char	*line;
	int		numline;

	map_ini(map);
	fd = open(path, O_RDONLY);
	if (fd < 2)
		return (-1);
	if (map_size(fd, map) < 0)
		return (-1);
	map->points = ft_calloc (map->len, sizeof(t_point));
	close (fd);
	fd = open(path, O_RDONLY);
	if (fd < 2)
		return (-1);
	numline = 0;
	map->len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		numline++;
		load_points(line, map, numline);
		free(line);
		line = get_next_line(fd);
	}
	show_info(map);
	return (1);
}

