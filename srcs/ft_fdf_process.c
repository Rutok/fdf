/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 05:34:57 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 02:37:19 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_process.h"
#include <math.h>

static void	fdf_update_minmax(t_map *map, t_point *point)
{
	t_pair	*proj;

	proj = &point->projected;
	if (!point->x && !point->y)
	{
		map->min.x = proj->x;
		map->min.y = proj->y;
		map->max.x = proj->x;
		map->max.y = proj->y;
	}
	else
	{
		map->min.x = proj->x < map->min.x ? proj->x : map->min.x;
		map->min.y = proj->y < map->min.y ? proj->y : map->min.y;
		map->max.x = proj->x > map->max.x ? proj->x : map->max.x;
		map->max.y = proj->y > map->max.y ? proj->y : map->max.y;
	}
}

void	fdf_project_iso(t_map *map)
{
	int		x;
	int		y;
	t_point	*point;
	t_pair	*proj;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			point = &map->points[y][x];
			proj = &point->projected;
			proj->x = (sqrt(2) / 2) * (point->x - point->y);
			proj->y = (sqrt(2 / 3.0) * point->z) - ((1 / sqrt(6)) * (point->x + point->y));
			fdf_update_minmax(map, point);
			y++;
		}
		x++;
	}
}
