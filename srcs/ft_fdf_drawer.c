/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2016/12/14 00:08:34 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_drawer.h"
#include <math.h>

static void	fdf_put_pixel_img(t_point *point, t_env *env)
{
	int	i;
	int	x;
	int	y;

	if (point->projected.x < env->win.size.x
			&& point->projected.y < env->win.size.y
			&& point->projected.x >= 0
			&& point->projected.y >= 0)
	{
		i = 0;
		x = floor(point->projected.x) * env->img.bpp / 8;
		y = floor(point->projected.y) * env->img.line_size;
		env->img.data[x + y + i++] = mlx_get_color_value(env->mlx, point->color.b);
		env->img.data[x + y + i++] = mlx_get_color_value(env->mlx, point->color.g);
		env->img.data[x + y + i++] = mlx_get_color_value(env->mlx, point->color.r);
		env->img.data[x + y + i++] = mlx_get_color_value(env->mlx, 0);
	}
}

static void	fdf_normalize_point(t_point *point, t_env* env)
{
	t_pair	*min;
	t_pair	*max;

	min = &env->map->min;
	max = &env->map->max;
	point->projected.x = ((((point->projected.x - min->y) / (max->y - min->y))) * (env->win.size.y - 1));;
	point->projected.y = ((((point->projected.y - min->y) / (max->y - min->y))) * (env->win.size.y - 1));
}

static void	fdf_draw_line(t_point* p1, t_point *p2, t_env *env)
{
	int		step;
	t_pair	d;
	t_pair	incr;
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
		color_step.r = -(p1->color.r - p2->color.r) / step;
		color_step.g = -(p1->color.g - p2->color.g) / step;
		color_step.b = -(p1->color.b - p2->color.b) / step;
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
	mlx_destroy_image(env->mlx, env->img.mlx_img);
	if ((env->img.mlx_img = mlx_new_image(env->mlx, env->win.size.x, env->win.size.y)) == NULL)
		fdf_exit("Could not allocate memory");
	env->img.data = mlx_get_data_addr(env->img.mlx_img, &env->img.bpp, &env->img.line_size, &env->img.endian);
}
