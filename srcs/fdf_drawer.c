/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:20 by nboste            #+#    #+#             */
/*   Updated: 2017/03/15 15:51:59 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_drawer.h"
#include <math.h>
#include <stdio.h>
#include "camera.h"
#include "camera_drawer.h"
#include "color.h"

void	fdf_draw_img(t_env *env)
{
	t_fdf		*fdf;
	t_camera	*cam;
	t_2ipair	c;
	t_fdfpoint		*p;
	t_fdfpoint		**pts;
	t_point		p1;
	t_point		p2;

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
			p->d = (p->c_space.x * p->c_space.x) + (p->c_space.y * p->c_space.y) + (p->c_space.z * p->c_space.z);
			if (p->c_space.z > 0)
			{
				if (p->d < fdf->range)
				{
					p->draw = 1;
					camera_project_vertex(&p->c_space, &p->c_view, cam);
					p1.z = p->d;
					p1.pos.x = round(p->c_view.x);
					p1.pos.y = round(p->c_view.y);
					p1.c = p->color;
					if (c.x > 0 && pts[c.y][c.x - 1].draw
							&& (pts[c.y][c.x - 1].c_space.z > 0 || pts[c.y][c.x].c_space.z > 0))
					{
						p2.z = pts[c.y][c.x - 1].d;
						p2.pos.x = round(pts[c.y][c.x - 1].c_view.x);
						p2.pos.y = round(pts[c.y][c.x - 1].c_view.y);
						p2.c = pts[c.y][c.x - 1].color;
						camera_draw_line(&p1, &p2, cam, env);
					}
					if (c.y > 0 && pts[c.y - 1][c.x].draw
							&& (pts[c.y - 1][c.x].c_space.z > 0 || pts[c.y][c.x].c_space.z > 0))
					{
						p2.z = pts[c.y - 1][c.x].d;
						p2.pos.x = round(pts[c.y - 1][c.x].c_view.x);
						p2.pos.y = round(pts[c.y - 1][c.x].c_view.y);
						p2.c = pts[c.y - 1][c.x].color;
						camera_draw_line(&p1, &p2, cam, env);
					}
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
