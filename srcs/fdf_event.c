/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:18:34 by nboste            #+#    #+#             */
/*   Updated: 2017/06/02 10:07:55 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_event.h"
#include "fdf.h"
#include <SDL2/SDL.h>
#include "vertex_utility.h"
#include "camera.h"

static void	fdf_events_mouse(t_event *ev, t_camera *cam, t_3dvertex z)
{
	static t_2dpair	off;
	t_2dpair		d;

	if (ev->mouse.move)
	{
		d.x = ev->mouse.pos.x + off.x - (cam->size.x / 2);
		d.y = ev->mouse.pos.y + off.y - (cam->size.y / 2);
		off.x = d.x;
		off.y = d.y;
		if (d.x != 0 && d.y != 0)
		{
			d.x *= -cam->sensitivity;
			d.y *= -0.1;
			off.x /= 10;
			off.y /= 10;
			rotate_3dvertex(&cam->u, z, ft_degtorad(d.x));
			rotate_3dvertex(&cam->v, z, ft_degtorad(d.x));
			rotate_3dvertex(&cam->n, z, ft_degtorad(d.x));
			rotate_3dvertex(&cam->n, cam->u, ft_degtorad(d.y));
			rotate_3dvertex(&cam->v, cam->u, ft_degtorad(d.y));
			SDL_WarpMouseInWindow(NULL, cam->size.x / 2, cam->size.y / 2);
		}
	}
}

static void	fdf_events_controls(t_event *ev, t_camera *cam)
{
	if (ev->keys[SDL_SCANCODE_W])
	{
		cam->pos.x += cam->n.x * cam->speed;
		cam->pos.y += cam->n.y * cam->speed;
		cam->pos.z += cam->n.z * cam->speed;
	}
	if (ev->keys[SDL_SCANCODE_A])
	{
		cam->pos.x -= cam->u.x * cam->speed;
		cam->pos.y -= cam->u.y * cam->speed;
		cam->pos.z -= cam->u.z * cam->speed;
	}
	if (ev->keys[SDL_SCANCODE_S])
	{
		cam->pos.x -= cam->n.x * cam->speed;
		cam->pos.y -= cam->n.y * cam->speed;
		cam->pos.z -= cam->n.z * cam->speed;
	}
	if (ev->keys[SDL_SCANCODE_D])
	{
		cam->pos.x += cam->u.x * cam->speed;
		cam->pos.y += cam->u.y * cam->speed;
		cam->pos.z += cam->u.z * cam->speed;
	}
}

static void	fdf_events_others(t_event *ev, t_camera *cam, t_env *env)
{
	static int tmp_u;
	static int tmp_j;

	if (ev->keys[SDL_SCANCODE_O])
		cam->range *= 1.1;
	if (ev->keys[SDL_SCANCODE_L])
		cam->range *= .90;
	if (ev->keys[SDL_SCANCODE_U])
		tmp_u = 1;
	else if (tmp_u)
	{
		init_camera(env, cam->fov.y * 1.1, cam);
		tmp_u = 0;
	}
	if (ev->keys[SDL_SCANCODE_J])
		tmp_j = 1;
	else if (tmp_j)
	{
		init_camera(env, cam->fov.y * 0.9, cam);
		tmp_j = 0;
	}
}

static void	fdf_events_more(t_event *ev, t_camera *cam, t_fdf *fdf)
{
	static int tmp_m;

	if (ev->keys[SDL_SCANCODE_M])
		tmp_m = 1;
	else if (tmp_m == 1)
	{
		if (cam->projection == parallel)
			cam->projection = perspective;
		else
			cam->projection = parallel;
		tmp_m = 0;
	}
	if (ev->keys[SDL_SCANCODE_I])
		cam->speed *= 1.1;
	if (ev->keys[SDL_SCANCODE_K])
		cam->speed *= .9;
	if (ev->keys[SDL_SCANCODE_ESCAPE])
		ev->exit = 1;
	if (ev->keys[SDL_SCANCODE_UP])
		((t_3dobject *)fdf->scene.objects->content)->scale.z *= 1.1;
	if (ev->keys[SDL_SCANCODE_DOWN])
		((t_3dobject *)fdf->scene.objects->content)->scale.z *= .9;
}

void		fdf_events(t_env *env)
{
	t_event		*ev;
	t_fdf		*fdf;
	t_camera	*cam;
	t_3dvertex	z;

	ev = &env->event;
	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	z.x = 0;
	z.y = 0;
	z.z = 1;
	fdf_events_mouse(ev, cam, z);
	fdf_events_controls(ev, cam);
	fdf_events_others(ev, cam, env);
	fdf_events_more(ev, cam, fdf);
	fdf->to_draw = 1;
}
