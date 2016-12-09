/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 05:34:57 by nboste            #+#    #+#             */
/*   Updated: 2016/12/09 05:41:18 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_process.h"
#include <math.h>

void	fdf_project_iso(t_map *map)
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
			point = &map->points[x][y];
			point->xp = (sqrt(2) / 2) * (point->x - point->y);
			point->yp = (sqrt(2 / 3) * point->z) - ((1 / sqrt(6)) * (point->x + point->y));
			y++;
		}
		x++;
	}
}
