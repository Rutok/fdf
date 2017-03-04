/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:18:34 by nboste            #+#    #+#             */
/*   Updated: 2017/02/24 23:56:16 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_event.h"
#include "fdf.h"
#include "fdf_process.h"
#include <SDL2/SDL.h>
#include "vertex_utility.h"

void	fdf_events(t_env *env)
{
	t_event		*ev;
	t_fdf		*fdf;
	t_camera	*cam;
	static t_2dpair off;

	ev = &env->event;
	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	if (ev->mouse.move)
	{
		t_2dpair	d;
		t_3dvertex	z;
		z.x = 0;
		z.y = 0;
		z.z = 1;
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
			rotate_3dvertex(&cam->n, z, ft_degtorad(d.x));
			rotate_3dvertex(&cam->v, z, ft_degtorad(d.x));
			rotate_3dvertex(&cam->n, cam->u, ft_degtorad(d.y));
			rotate_3dvertex(&cam->v, cam->u, ft_degtorad(d.y));
			SDL_WarpMouseInWindow(NULL, cam->size.x / 2, cam->size.y / 2);
			fdf->to_draw = 1;
		}
	}
	if (ev->keys[SDL_SCANCODE_ESCAPE])
		ev->exit = 1;
	if (1 || ev->keys[SDL_SCANCODE_LEFT])
	{
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_z_pos);
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_RIGHT])
	{
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_z_neg);
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_UP])
	{
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_x_pos);
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_DOWN])
	{
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_x_neg);
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_PAGEUP])
	{
		fdf_apply_matrix(fdf->map, fdf->matrix.homo_in);
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_PAGEDOWN])
	{
		fdf_apply_matrix(fdf->map, fdf->matrix.homo_out);
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_W])
	{
		cam->pos.x += cam->n.x * cam->speed;
		cam->pos.y += cam->n.y * cam->speed;
		cam->pos.z += cam->n.z * cam->speed;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_A])
	{
		cam->pos.x -= cam->u.x * cam->speed;
		cam->pos.y -= cam->u.y * cam->speed;
		cam->pos.z -= cam->u.z * cam->speed;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_S])
	{
		cam->pos.x -= cam->n.x * cam->speed;
		cam->pos.y -= cam->n.y * cam->speed;
		cam->pos.z -= cam->n.z * cam->speed;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_D])
	{
		cam->pos.x += cam->u.x * cam->speed;
		cam->pos.y += cam->u.y * cam->speed;
		cam->pos.z += cam->u.z * cam->speed;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_O])
	{
		fdf->range *= 1.1;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_L])
	{
		fdf->range *= .9;
		fdf->to_draw = 1;
	}
	static int tmp_m;
	if (ev->keys[SDL_SCANCODE_M])
	{
		tmp_m = 1;
	}
	else if (tmp_m == 1)
	{
		if (cam->projection == parallel)
			cam->projection = perspective;
		else
			cam->projection = parallel;
		fdf->to_draw = 1;
		tmp_m = 0;
	}
	if (ev->keys[SDL_SCANCODE_I])
	{
		cam->speed *= 1.1;
	}
	if (ev->keys[SDL_SCANCODE_K])
	{
		cam->speed *= .9;
	}
}
