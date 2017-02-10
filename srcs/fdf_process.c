/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 05:34:57 by nboste            #+#    #+#             */
/*   Updated: 2017/02/10 02:29:19 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_process.h"
#include <math.h>

void	fdf_apply_matrix(t_map *map, double **matrix)
{
	int		x;
	int		y;
	t_point	*point;
	t_point	 p2;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			point = &map->points[y][x];
			p2 = *point;
			point->pos.x = matrix[0][0] * p2.pos.x + matrix[0][1] * p2.pos.y + matrix[0][2] * p2.pos.z;
			point->pos.y = matrix[1][0] * p2.pos.x + matrix[1][1] * p2.pos.y + matrix[1][2] * p2.pos.z;
			point->pos.z = matrix[2][0] * p2.pos.x + matrix[2][1] * p2.pos.y + matrix[2][2] * p2.pos.z;
			y++;
		}
		x++;
	}
}

void	fdf_translate(t_map *map, char dir, double step)
{
	int		x;
	int		y;
	t_point	*point;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			point = &map->points[y][x];
			if (dir == DIR_X)
				point->pos.x += step;
			else
				point->pos.y += step;
			y++;
		}
		x++;
	}
}
