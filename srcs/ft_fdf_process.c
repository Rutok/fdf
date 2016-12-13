/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 05:34:57 by nboste            #+#    #+#             */
/*   Updated: 2016/12/12 22:53:24 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_process.h"
#include <math.h>

static void	fdf_update_minmax(t_map *map, t_point *point)
{
	static int call;
	t_pair	*proj;

	proj = &point->projected;
	if (!call)
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
	call++;
}

void	fdf_apply_matrix(t_map *map, double **matrix)
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
			point->x = matrix[0][0] * point->x + matrix[0][1] * point->y + matrix[0][2] * point->z;
			point->y = matrix[1][0] * point->x + matrix[1][1] * point->y + matrix[1][2] * point->z;
			point->z = matrix[2][0] * point->x + matrix[2][1] * point->y + matrix[2][2] * point->z;
			y++;
		}
		x++;
	}
}

void	fdf_project_iso(t_map *map)
{
	static int	t;
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
			proj->x = (sqrt(2) / 2.0) * (point->x - point->y);
			proj->y = (sqrt(2 / 3.0) * -0.25 * point->z) - ((1.0 / sqrt(6)) * (point->x + point->y));
			if (t == 0)
				fdf_update_minmax(map, point);
			y++;
		}
		x++;
	}
	t++;
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
				point->x += step;
			else
				point->y += step;
			y++;
		}
		x++;
	}
}
