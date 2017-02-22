/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2017/02/22 04:23:08 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_drawer.h"
#include <math.h>
#include <stdio.h>
#include "camera.h"
#include "color.h"

void	fdf_draw_img(t_env *env)
{
	t_fdf		*fdf;
	t_camera	*cam;
	t_2ipair	c;
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
			to_camera_space(&p->pos, &p->c_space, cam);
			if (p->c_space.z > 0)
			{
				p->d = (p->c_space.x * p->c_space.x) + (p->c_space.y * p->c_space.y) + (p->c_space.z * p->c_space.z);
				if (p->d < fdf->range)
				{
					p->draw = 1;
					camera_project_vertex(&p->c_space, &p->c_view, cam);
					if (c.x > 0 && pts[c.y][c.x - 1].draw
							&& (pts[c.y][c.x - 1].c_space.z > 0 || pts[c.y][c.x].c_space.z > 0)
							&& (((pts[c.y][c.x - 1].c_view.x < cam->size.x && pts[c.y][c.x - 1].c_view.x >= 0)
									|| (pts[c.y][c.x].c_view.x < cam->size.x && pts[c.y][c.x].c_view.x >= 0))
								&& ((pts[c.y][c.x - 1].c_view.y < cam->size.y && pts[c.y][c.x - 1].c_view.y >= 0)
									|| (pts[c.y][c.x].c_view.y < cam->size.y && pts[c.y][c.x].c_view.y >= 0))))
						fdf_draw_line(&pts[c.y][c.x], &pts[c.y][c.x - 1], cam);
					if (c.y > 0 && pts[c.y - 1][c.x].draw
							&& (pts[c.y - 1][c.x].c_space.z > 0 || pts[c.y][c.x].c_space.z > 0)
							&& (((pts[c.y - 1][c.x].c_view.x < cam->size.x && pts[c.y - 1][c.x].c_view.x >= 0)
									|| (pts[c.y][c.x].c_view.x < cam->size.x && pts[c.y][c.x].c_view.x >= 0))
								&& ((pts[c.y - 1][c.x].c_view.y < cam->size.y && pts[c.y - 1][c.x].c_view.y >= 0)
									|| (pts[c.y][c.x].c_view.y < cam->size.y && pts[c.y ][c.x].c_view.y >= 0))))
						fdf_draw_line(&pts[c.y][c.x], &pts[c.y - 1][c.x], cam);
				}
				else
					p->draw = 0;
			}
			else
				p->draw = 0;
			c.x++;
		}
		c.y++;
	}
}

void	fdf_draw_line(t_point* p1, t_point *p2, t_camera *cam)
{
	t_2dpair	d;
	t_2ipair	inc;
	t_2ipair	point;
	double			cumul;
	int			i;
	double		di;
	double		ds;
	t_2dpair	zs;
	int			tmp;

	tmp = 0;
	point.x = p1->c_view.x;
	point.y = p1->c_view.y;
	d.x = p2->c_view.x - p1->c_view.x;
	d.y = p2->c_view.y - p1->c_view.y;
	inc.x = (d.x > 0) ? 1 : -1;
	inc.y = (d.y > 0) ? 1 : -1;
	d.x = fabs(d.x);
	d.y = fabs(d.y);
	di = p1->d;
	zs.x = p2->pos.z - p1->pos.z;
	zs.y = p1->pos.z;
	if (d.x > d.y)
	{
		ds = (p2->d - p1->d) / d.x;
		zs.x = (zs.x / d.x);
		cumul = d.x / 2 ;
		for (i = 1; i <= d.x; i++)
		{
			point.x += inc.x;
			cumul += d.y;
			zs.y += zs.x;
			if (cumul >= d.x)
			{
				cumul -= d.x;
				point.y += inc.y;
			}
			if (point.x < cam->size.x && point.x >= 0 && point.y < cam->size.y && point.y >= 0)
			{
				di += ds;
				if (di < cam->pixels[point.y][point.x].z_buffer || cam->pixels[point.y][point.x].z_buffer == -1)
				{
					cam->pixels[point.y][point.x].color = fdf_getcolor(round(zs.y));
					cam->pixels[point.y][point.x].z_buffer = di;
				}
			}
			else
			{
				tmp++;
			if (tmp != i)
				return;
			}
		}
	}
	else
	{
		ds = (p2->d - p1->d) / d.y;
		zs.x = (zs.x / d.y);
		cumul = d.y / 2 ;
		for (i = 1 ; i <= d.y; i++)
		{
			point.y += inc.y;
			cumul += d.x;
			zs.y += zs.x;
			if (cumul >= d.y)
			{
				cumul -= d.y;
				point.x += inc.x;
			}
			if (point.x < cam->size.x && point.x >= 0 && point.y < cam->size.y && point.y >= 0)
			{
				di += ds;
				if ((di < cam->pixels[point.y][point.x].z_buffer || cam->pixels[point.y][point.x].z_buffer == -1))
				{
					cam->pixels[point.y][point.x].color = fdf_getcolor(round(zs.y));
					cam->pixels[point.y][point.x].z_buffer = di;
				}
			}
			else
			{
				tmp++;
			if (tmp != i)
				return;
			}
		}
	}
}

t_color	fdf_getcolor(int z)
{
	t_color	c;

	if (z <= 0)
	{
		c.r = 0;
		c.g = 0;
		if (z >= -255)
			c.b = z + 255;
		else
			c.b = 0;
	}
	else if (z < 50)
	{
		c.r = 0;
		c.g = z + 45;
		c.b = 0;
	}
	else
	{
		c.r = (z % 255) + 55;
		c.g = (z % 128) + 55;
		c.b = (z % 64) + 55;
	}
	return (c);
}
