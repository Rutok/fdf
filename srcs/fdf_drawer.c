/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2017/01/09 18:28:54 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_drawer.h"
#include "drawer.h"
#include <math.h>

static void	fdf_put_pixel_img(t_point *point, t_env *env)
{
	int	i;
	t_2ipair	p;
	uint32		color;

	if (point->projected.x < env->win.size.x
			&& point->projected.y < env->win.size.y
			&& point->projected.x >= 0
			&& point->projected.y >= 0)
	{
		i = 0;
		p.x = floor(point->projected.x);
		p.y = floor(point->projected.y);
		color = point->color.r;
		color <<= 8;
		color += point->color.g;
		color <<= 8;
		color += point->color.b;
		color <<= 8;
		drawer_put_pixel(p, color, &env->rend);
	}
}

static void	fdf_normalize_point(t_point *point, t_env* env)
{
	t_fdf		*fdf;
	t_2ipair	*min;
	t_2ipair	*max;

	fdf = (t_fdf *)env->app.d;
	min = &fdf->map->min;
	max = &fdf->map->max;
	point->projected.x = ((((point->projected.x - min->y) / (max->y - min->y))) * (env->win.size.y - 100)) + 50;
	point->projected.y = ((((point->projected.y - min->y) / (max->y - min->y))) * (env->win.size.y - 100)) + 50;
}

static void	fdf_draw_line(t_point* p1, t_point *p2, t_env *env)
{
	int		step;
	t_2dpair	d;
	t_2dpair	incr;
	t_point	point;
	t_color	color_step;

	d.x = p2->projected.x - p1->projected.x;
	d.y = p2->projected.y - p1->projected.y;
	step = fabs(d.x) > fabs(d.y) ? fabs(d.x) : fabs(d.y);
	if (step)
	{
		incr.x = d.x / (float)step;
		incr.y = d.y / (float)step;
		d.x = 0;
		point = *p1;
		color_step.r = (p2->color.r - p1->color.r) / step;
		color_step.g = (p2->color.g - p1->color.g) / step;
		color_step.b = (p2->color.b - p1->color.b) / step;
		while (d.x++ < step)
		{
			point.projected.x += incr.x;
			point.projected.y += incr.y;
			point.color.r += color_step.r;
			point.color.g += color_step.g;
			point.color.b += color_step.b;
			fdf_put_pixel_img(&point, env);
		}
	}
}

void	fdf_normalize_points(t_env *env)
{
	t_point	**points;
	t_fdf	*fdf;
	int		x;
	int		y;

	fdf = (t_fdf *)env->app.d;
	x = 0;
	points = fdf->map->points;
	while (x < fdf->map->width)
	{
		y = 0;
		while (y < fdf->map->height)
		{
			fdf_normalize_point(&points[y][x], env);
			if (x > 0 && y > 0)
			{
			//	fdf_update_zbuffer
			}
			y++;
		}
		x++;
	}
}

void	fdf_draw_img(t_env *env)
{
	t_point	**points;
	t_fdf	*fdf;
	int		x;
	int		y;

	x = 0;
	fdf = (t_fdf *)env->app.d;
	points = fdf->map->points;
	while (x < fdf->map->width)
	{
		y = 0;
		while (y < fdf->map->height)
		{
			fdf_put_pixel_img(&points[y][x], env);
			if (x > 0 && y > 0)
			{
				fdf_draw_line(&points[y][x], &points[y][x - 1], env);
				fdf_draw_line(&points[y][x], &points[y - 1][x], env);
			}
			y++;
		}
		x++;
	}
}
