/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 03:01:09 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_drawer.h"
#include <math.h>

static void	fdf_put_pixel_img(t_point *point, t_env *env)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = floor(point->projected.x) * env->img.bpp / 8;
	y = floor(point->projected.y) * env->img.line_size;
	env->img.data[x + y + i++] = mlx_get_color_value(env->mlx, 255);
	env->img.data[x + y + i++] = mlx_get_color_value(env->mlx, 255);
	env->img.data[x + y + i++] = mlx_get_color_value(env->mlx, 255);
	env->img.data[x + y + i++] = mlx_get_color_value(env->mlx, 0);
}

static void	fdf_normalize_point(t_point *point, t_env* env)
{
	t_pair	*min;
	t_pair	*max;

	min = &env->map->min;
	max = &env->map->max;
	point->projected.x = ((point->projected.x - min->x) / (max->x - min->x)) * (env->win.size.x - 1);
	point->projected.y = ((point->projected.y - min->y) / (max->y - min->y)) * (env->win.size.y - 1);
}

static void	fdf_draw_line(t_point* p1, t_point *p2, t_env *env)
{
	int		step;
	t_pair	d;
	t_pair	incr;
	t_point	point;

	d.x = p2->projected.x - p1->projected.x;
	d.y = p2->projected.y - p1->projected.y;
	step = fabs(d.x) > fabs(d.y) ? fabs(d.x) : fabs(d.y);
	incr.x = d.x / (float)step;
	incr.y = d.y / (float)step;
	d.x = 0;
	point = *p1;
	while (d.x++ < step)
	{
		point.projected.x += incr.x;
		point.projected.y += incr.y;
		fdf_put_pixel_img(&point, env);
	}
}

void	fdf_draw_img(t_env *env)
{
	t_point	**points;
	int		x;
	int		y;

	x = 0;
	points = env->map->points;
	while (x < env->map->width)
	{
		y = 0;
		while (y < env->map->height)
		{
			fdf_normalize_point(&points[y][x], env);
			fdf_put_pixel_img(&points[y][x], env);
			if (x > 0)
				fdf_draw_line(&points[y][x], &points[y][x - 1], env);
			if (y > 0)
				fdf_draw_line(&points[y][x], &points[y - 1][x], env);
			y++;
		}
		x++;
	}
}

void	fdf_display_img(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win.mlx_win, env->img.mlx_img, 0, 0);
}
