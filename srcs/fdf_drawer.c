/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2017/02/17 22:23:49 by nboste           ###   ########.fr       */
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
	t_2ipair	d;
	t_2ipair	inc;
	t_2ipair	point;
	int			cumul;
	int			i;
	double		z;
	double		z_step;
	t_color		color_step;
	t_color		c;
	double		di;
	double		ds;
	t_point		*tt;

	if (p2->c_space.z > p1->c_space.z)
	{
		tt = p2;
		p2 = p1;
		p1 = tt;
	}
	point.x = p1->c_view.x;
	point.y = p1->c_view.y;
	d.x = p2->c_view.x - p1->c_view.x;
	d.y = p2->c_view.y - p1->c_view.y;
	inc.x = (d.x > 0) ? 1 : -1;
	inc.y = (d.y > 0) ? 1 : -1;
	d.x = abs(d.x);
	d.y = abs(d.y);
	z = p1->c_space.z;
	di = p1->d;
	c = p1->color;
	if (d.x > d.y)
	{
		color_step.r = (p2->color.r - p1->color.r) / (float)d.x;
		color_step.g = (p2->color.g - p1->color.g) / (float)d.x;
		color_step.b = (p2->color.b - p1->color.b) / (float)d.x;

		ds = (p2->d - p1->d) / d.x;
		z_step = (p2->c_space.z - p1->c_space.z) / d.x;
		cumul = d.x / 2 ;
		for (i = 1; i <= d.x; i++)
		{
			c.r += color_step.r;
			c.g += color_step.g;
			c.b += color_step.b;

			point.x += inc.x;
			cumul += d.y;
			if (cumul >= d.x)
			{
				cumul -= d.x;
				point.y += inc.y;
			}
			if (point.x < cam->size.x && point.x > 0 && point.y < cam->size.y && point.y > 0)
			{
				di += ds;
				if (z > cam->d)
				{
					if (di < cam->pixels[point.y][point.x].z_buffer || cam->pixels[point.y][point.x].z_buffer == -1)
					{
						cam->pixels[point.y][point.x].color = c;
						cam->pixels[point.y][point.x].z_buffer = di;
					}
				}
				else
					return;
			}
			z += z_step;
		}
	}
	else
	{
		color_step.r = (p2->color.r - p1->color.r) / (float)d.y;
		color_step.g = (p2->color.g - p1->color.g) / (float)d.y;
		color_step.b = (p2->color.b - p1->color.b) / (float)d.y;

		ds = (p2->d - p1->d) / d.y;
		z_step = (p2->c_space.z - p1->c_space.z) / d.y;
		cumul = d.y / 2 ;
		for (i = 1 ; i <= d.y; i++)
		{
			point.y += inc.y;
			cumul += d.x;
			c.r += color_step.r;
			c.g += color_step.g;
			c.b += color_step.b;
			if (cumul >= d.y)
			{
				cumul -= d.y;
				point.x += inc.x;
			}
			if (point.x < cam->size.x && point.x > 0 && point.y < cam->size.y && point.y > 0)
			{
				di += ds;
				if (z > cam->d)
				{
					if ((di < cam->pixels[point.y][point.x].z_buffer || cam->pixels[point.y][point.x].z_buffer == -1))
				{
					cam->pixels[point.y][point.x].color = c;
					cam->pixels[point.y][point.x].z_buffer = di;
				}
				}
				else
					return;
			}
			z += z_step;
		}
	}
}

static void	fdf_draw_point(t_2ipair coord, t_point **points, t_camera *cam)
{
	t_2ipair	p;
	double		d;
	t_point		*point;

	point = &points[coord.y][coord.x];
	p.x = round(((point->c_view.x + cam->ratio) * cam->size.x)  / (2 * cam->ratio));
	p.y = round(((point->c_view.y + 1) * cam->size.y)  / (2));
	point->c_view.x = p.x;
	point->c_view.y = p.y;
	d = (point->c_space.x * point->c_space.x) + (point->c_space.y * point->c_space.y) + (point->c_space.z * point->c_space.z);
	point->d = d;
}

void	fdf_draw_img(t_env *env)
{
	t_fdf		*fdf;
	t_camera	*cam;
	t_2ipair	c;
	t_3dvertex	v;
	t_point		*p;
	t_point		**pts;

	fdf = (t_fdf *)env->app.d;
	pts = fdf->map->points;
	cam = &fdf->scene.camera;
	c.y = 0;
	while (c.y < fdf->map->height)
	{
		c.x = 0;
		while (c.x < fdf->map->width)
		{
			p = &fdf->map->points[c.y][c.x];
			v = p->pos;
			p->c_space = to_camera_space(&v, cam);
			p->c_view = camera_project_vertex(&p->c_space, cam);
			fdf_draw_point(c, fdf->map->points, cam);
			if (c.x > 0 && (pts[c.y][c.x - 1].c_space.z > 0 || pts[c.y][c.x].c_space.z > 0))
				fdf_draw_line(&pts[c.y][c.x], &pts[c.y][c.x - 1], cam);
			if (c.y > 0 && (pts[c.y - 1][c.x].c_space.z > 0 || pts[c.y][c.x].c_space.z > 0))
				fdf_draw_line(&pts[c.y][c.x], &pts[c.y - 1][c.x], cam);
			c.x++;
		}
		c.y++;
	}
}
