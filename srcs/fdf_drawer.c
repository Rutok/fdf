/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2017/02/09 02:18:29 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_drawer.h"
#include "drawer.h"
#include <math.h>
#include "camera.h"
#include <stdio.h>
#include "color.h"

static void	fdf_draw_line(t_point* p1, t_point *p2, t_camera *cam)
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
			if (round(point.projected.x) < cam->size.x && round(point.projected.y) < cam->size.y && point.projected.x >= 0 && point.projected.y >= 0)
			{
				cam->pixels[(int)round(point.projected.y)][(int)round(point.projected.x)].color = point.color;
				cam->pixels[(int)round(point.projected.y)][(int)round(point.projected.x)].z_buffer = 1;
			}
		}
	}
}

static void	fdf_put_pixel_img(t_2dpair *o, t_2ipair coord, t_point **points, t_camera *cam, t_3dvertex v)
{
	t_2ipair	p;
	double		d;
	t_color		*c;

	c = &points[coord.y][coord.x].color;
	p.x = round(((o->x + cam->ratio) * cam->size.x)  / (2 * cam->ratio));
	p.y = round(((o->y + 1) * cam->size.y)  / (2));
	points[coord.y][coord.x].projected.x = p.x;
	points[coord.y][coord.x].projected.y = p.y;
	d = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	points[coord.y][coord.x].d = d;
	if (p.x < cam->size.x
			&& p.y < cam->size.y
			&& p.x >= 0
			&& p.y >= 0)
	{
		if (cam->pixels[p.y][p.x].z_buffer == -1 || d < cam->pixels[p.y][p.x].z_buffer)
		{
			cam->pixels[p.y][p.x].color = *c;
			cam->pixels[p.y][p.x].z_buffer = d;
		}
	}
	if (coord.x > 0)
		fdf_draw_line(&points[coord.y][coord.x], &points[coord.y][coord.x - 1], cam);
	if (coord.y > 0)
		fdf_draw_line(&points[coord.y][coord.x], &points[coord.y - 1][coord.x], cam);
}

void	fdf_draw_img(t_env *env)
{
	t_fdf	*fdf;
	t_camera	*cam;
	t_2ipair	c;
	t_3dvertex	v;
	t_2dpair		p;

	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	reset_camera_pixels(cam);
	c.y = 0;
	while (c.y < fdf->map->height)
	{
		c.x = 0;
		while (c.x < fdf->map->width)
		{
			v.x = fdf->map->points[c.y][c.x].x;
			v.y = fdf->map->points[c.y][c.x].y;
			v.z = fdf->map->points[c.y][c.x].z;
			to_camera_space(&v, cam);
			if (v.z > cam->d)
			{
				p = camera_project_vertex(&v, cam);
				fdf_put_pixel_img(&p, c, fdf->map->points, cam, v);
			}
			c.x++;
		}
		c.y++;
	}
	c.y = 0;
	while (c.y < cam->size.y)
	{
		c.x = 0;
		while (c.x < cam->size.x)
		{
			if (cam->pixels[c.y][c.x].z_buffer != -1)
				drawer_put_pixel(c, t_colortouint32(&cam->pixels[c.y][c.x].color), &env->rend);
			else
				drawer_put_pixel(c, 0, &env->rend);
			c.x++;
		}
		c.y++;
	}
}
