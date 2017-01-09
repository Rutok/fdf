/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_zbuffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 00:57:30 by nboste            #+#    #+#             */
/*   Updated: 2016/12/15 01:49:13 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_zbuffer.h"

t_zbuffer	*init_zbuffer(int width, int height)
{
	t_zbuffer	*b
	int			i;
	t_color		black;

	i = 0;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	if (!(b = (t_zbuffer **)malloc(sizeof(t_zbuffer *) * height)))
		ftf_exit("Mem");
	while (i < height)
	{
		if (!(b[i] = (t_zbuffer *)malloc(sizeof(t_zbuffer) * width)))
			fdf_exit("Mem");
		i++;
	}
	b->size.x = width;
	b->size.y = height;
	reset_buffer(b, black);
	return (b);
}

void	reset_zbuffer(t_zbuffer *b, t_color bckgrnd)
{
	int	x;
	int	y;

	y = 0;
	while (y < b->size.y)
	{
		x = 0;
		while (x < b->size.x)
		{
			b->points[y][x].depth = ZB_MIN_DEPTH;
			b->points[y][x].color = bckgrnd;
			x++;
		}
		y++;
	}
}
