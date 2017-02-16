/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2017/02/16 04:34:56 by nboste           ###   ########.fr       */
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
				z += z_step;
				di += ds;
				if (z > cam->d && (di < cam->pixels[point.y][point.x].z_buffer || cam->pixels[point.y][point.x].z_buffer == -1))
				{
					cam->pixels[point.y][point.x].color = c;
					cam->pixels[point.y][point.x].z_buffer = di;
				}
			}
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
				z += z_step;
				di += ds;
				if (z > cam->d && (di < cam->pixels[point.y][point.x].z_buffer || cam->pixels[point.y][point.x].z_buffer == -1))
				{
					cam->pixels[point.y][point.x].color = c;
					cam->pixels[point.y][point.x].z_buffer = di;
				}
			}
		}
	}
}

/*static void	fdf_draw_line(t_point* p1, t_point *p2, t_camera *cam)
  {
  int			step;
  t_2dpair	d;
  t_2dpair	incr;
  t_point		point;
  t_color		color_step;
  t_2dpair	z_step;

  d.x = p2->c_view.x - p1->c_view.x;
  d.y = p2->c_view.y - p1->c_view.y;
  step = fabs(d.x) > fabs(d.y) ? fabs(d.x) : fabs(d.y);
  z_step.x = p2->c_space.z - p1->c_space.z;
  if (step)
  {
  incr.x = d.x / (float)step;
  incr.y = d.y / (float)step;
  z_step.y = z_step.x / (float)step;
  d.x = 0;
  point = *p1;
  color_step.r = (p2->color.r - p1->color.r) / step;
  color_step.g = (p2->color.g - p1->color.g) / step;
  color_step.b = (p2->color.b - p1->color.b) / step;
  while (d.x++ < step)
  {
  point.c_view.x += incr.x;
  point.c_view.y += incr.y;
  point.c_space.z += z_step.y;
  point.color.r += color_step.r;
  point.color.g += color_step.g;
  point.color.b += color_step.b;
  if (point.c_space.z <= cam->d)
  return;
  if (point.c_space.z > cam->d && round(point.c_view.x) < cam->size.x && round(point.c_view.y) < cam->size.y && point.c_view.x >= 0 && point.c_view.y >= 0)
  {
  cam->pixels[(int)(point.c_view.y)][(int)(point.c_view.x)].color = point.color;
  cam->pixels[(int)(point.c_view.y)][(int)(point.c_view.x)].z_buffer = point.d;
  }
  }
  }
  }*/

static void	fdf_draw_point(t_2ipair coord, t_point **points, t_camera *cam)
{
	t_2ipair	p;
	double		d;
	t_color		*c;
	t_point		*point;

	c = &points[coord.y][coord.x].color;
	point = &points[coord.y][coord.x];
	p.x = round(((point->c_view.x + cam->ratio) * cam->size.x)  / (2 * cam->ratio));
	p.y = round(((point->c_view.y + 1) * cam->size.y)  / (2));
	point->c_view.x = p.x;
	point->c_view.y = p.y;
	d = (point->c_space.x * point->c_space.x) + (point->c_space.y * point->c_space.y) + (point->c_space.z * point->c_space.z);
	point->d = d;
	if (p.x < cam->size.x && p.y < cam->size.y && p.x >= 0 && p.y >= 0)
	{
		if (point->c_space.z > cam->d && (cam->pixels[p.y][p.x].z_buffer == -1 || d < cam->pixels[p.y][p.x].z_buffer))
		{
			cam->pixels[p.y][p.x].color = *c;
			cam->pixels[p.y][p.x].z_buffer = d;
		}
	}
}

void	fdf_draw_img(t_env *env)
{
	t_fdf		*fdf;
	t_camera	*cam;
	t_2ipair	c;
	t_3dvertex	v;
	t_point		*p;

	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	reset_camera_pixels(cam);
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
			c.x++;
		}
		c.y++;
	}
	t_point **pts = fdf->map->points;;
	c.y = 0;
	while (c.y < fdf->map->height)
	{
		c.x = 0;
		while (c.x < fdf->map->width)
		{
			if (c.x > 0)
				fdf_draw_line(&pts[c.y][c.x], &pts[c.y][c.x - 1], cam);
			if (c.y > 0)
				fdf_draw_line(&pts[c.y][c.x], &pts[c.y - 1][c.x], cam);
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
