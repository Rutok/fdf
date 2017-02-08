/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2017/02/08 04:06:25 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_drawer.h"
#include "drawer.h"
#include <math.h>
#include "camera.h"
#include <stdio.h>

static void	fdf_put_pixel_img(t_2dpair *o, t_color *c, t_camera *cam, t_env *env, t_3dvertex v)
{
	t_2ipair	p;
	uint32		color;
	double		d;

	p.x = floor(((o->x + cam->ratio) * cam->size.x)  / (2 * cam->ratio));
	p.y = floor(((o->y + 1) * cam->size.y)  / (2));
	if (p.x < cam->size.x
			&& p.y < cam->size.y
			&& p.x >= 0
			&& p.y >= 0)
	{
		p = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
		if (p < cam->pixels[p.y][p.x])
		{
			cam->pixels[p.y][p.x].color = *c;
			cam->pixels[p.y][p.x].z_buffer = p;
		}
		//drawer_put_pixel(p, color, &env->rend);
	}
}

/*static void	fdf_draw_line(t_point* p1, t_point *p2)
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
//fdf_put_pixel_img(&point, env);
}
}
}*/

void	fdf_draw_img(t_env *env)
{
	t_fdf	*fdf;
	t_camera	*cam;
	t_2ipair	c;
	t_3dvertex	v;
	t_2dpair		p;

	c.x = 0;
	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	reset_camera_pixels(camera);
	while (c.x < fdf->map->width)
	{
		c.y = 0;
		while (c.y < fdf->map->height)
		{
			v.x = fdf->map->points[c.y][c.x].x;
			v.y = fdf->map->points[c.y][c.x].y;
			v.z = fdf->map->points[c.y][c.x].z;
			to_camera_space(&v, cam);
			if (v.z > cam->d)
			{
				p = camera_project_vertex(&v, cam);
				fdf_put_pixel_img(&p, &(fdf->map->points[c.y][c.x].color), cam, env, v);
			}
			c.y++;
		}
		c.x++;
	}
}
