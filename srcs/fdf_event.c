/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:18:34 by nboste            #+#    #+#             */
/*   Updated: 2017/02/14 05:48:56 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_event.h"
#include "fdf.h"
#include "fdf_process.h"
#include "SDL.h"

static int	event_to_process(t_event *ev)
{
	if (ev->key_nav.keys[KEY_LEFT]
			|| ev->key_nav.keys[KEY_RIGHT] || ev->key_nav.keys[KEY_UP]
			|| ev->key_nav.keys[KEY_DOWN] || ev->key_nav.keys[KEY_PAGEUP]
			|| ev->key_nav.keys[KEY_PAGEDOWN] || ev->key_alphan.letters[KEY_W]
			|| ev->key_alphan.letters[KEY_A] || ev->key_alphan.letters[KEY_S]
			|| ev->key_alphan.letters[KEY_D] || ev->mouse.move)
		return (1);
	return (0);
}

static void	reset_event(t_event *ev)
{
	ev->key_nav.keys[KEY_LEFT] = 0;
	ev->key_nav.keys[KEY_RIGHT] = 0;
	ev->key_nav.keys[KEY_UP] = 0;
	ev->key_nav.keys[KEY_DOWN] = 0;
	ev->key_nav.keys[KEY_PAGEUP] = 0;
	ev->key_nav.keys[KEY_PAGEDOWN] = 0;
	ev->key_alphan.letters[KEY_W] = 0;
	ev->key_alphan.letters[KEY_A] = 0;
	ev->key_alphan.letters[KEY_S] = 0;
	ev->key_alphan.letters[KEY_D] = 0;
	ev->mouse.move = 0;
}

static void	rotate_3dvertex(t_3dvertex *v, t_3dvertex n, double a)
{
	t_3dvertex	tmp;

	if (!a)
		return;
	tmp.x = ((cos(a) + ((1 - cos(a)) * n.x * n.x)) * v->x)
		+ ((((1 - cos(a)) * n.x * n.y) - (sin(a) * n.z)) * v->y)
		+ ((((1 - cos(a)) * n.x * n.z) + (sin(a) * n.y)) * v->z);
	tmp.y = ((((1 - cos(a)) * n.x * n.y) + (sin(a) * n.z)) * v->x)
		+ ((cos(a) + ((1 - cos(a)) * n.y * n.y)) * v->y)
		+ ((((1 - cos(a)) * n.y * n.z) - (sin(a) * n.x)) * v->z);
	tmp.z = ((((1 - cos(a)) * n.x * n.z) - (sin(a) * n.y)) * v->x)
		+ ((((1 - cos(a)) * n.y * n.z) + (sin(a) * n.x)) * v->y)
		+ ((cos(a) + ((1 - cos(a)) * n.z * n.z)) * v->z);
	*v = tmp;
}

void	fdf_events(t_env *env)
{
	t_event		*ev;
	t_fdf		*fdf;
	t_camera	*cam;

	ev = &env->event;
	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	while (ev->in_use) {SDL_Delay(2);}
	ev->in_use = 1;
	if (ev->key_special.keys[KEY_ESCAPE])
		ev->exit = 1;
	if (ev->key_nav.keys[KEY_LEFT])
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_z_pos);
	if (ev->key_nav.keys[KEY_RIGHT])
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_z_neg);
	if (ev->key_nav.keys[KEY_UP])
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_x_pos);
	if (ev->key_nav.keys[KEY_DOWN])
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_x_neg);
	if (ev->key_nav.keys[KEY_PAGEUP])
		fdf_apply_matrix(fdf->map, fdf->matrix.homo_in);
	if (ev->key_nav.keys[KEY_PAGEDOWN])
		fdf_apply_matrix(fdf->map, fdf->matrix.homo_out);
	if (ev->key_alphan.letters[KEY_W])
	{
		cam->pos.x += cam->n.x * cam->speed;
		cam->pos.y += cam->n.y * cam->speed;
		cam->pos.z += cam->n.z * cam->speed;
	}
	if (ev->key_alphan.letters[KEY_A])
	{
		cam->pos.x -= cam->u.x * cam->speed;
		cam->pos.y -= cam->u.y * cam->speed;
		cam->pos.z -= cam->u.z * cam->speed;
	}
	if (ev->key_alphan.letters[KEY_S])
	{
		cam->pos.x -= cam->n.x * cam->speed;
		cam->pos.y -= cam->n.y * cam->speed;
		cam->pos.z -= cam->n.z * cam->speed;
	}
	if (ev->key_alphan.letters[KEY_D])
	{
		cam->pos.x += cam->u.x * cam->speed;
		cam->pos.y += cam->u.y * cam->speed;
		cam->pos.z += cam->u.z * cam->speed;
	}
	if (ev->mouse.move)
	{
		t_2ipair	d;

		d.x = ev->mouse.pos.x - (cam->size.x / 2);
		d.y = ev->mouse.pos.y - (cam->size.y / 2);
		d.x *= cam->sensitivity;
		d.y *= cam->sensitivity;
		rotate_3dvertex(&cam->u, cam->v, d.x);
		rotate_3dvertex(&cam->n, cam->v, d.x);
		rotate_3dvertex(&cam->n, cam->u, d.y);
		rotate_3dvertex(&cam->v, cam->u, d.y);
		SDL_WarpMouseInWindow(NULL, cam->size.x / 2, cam->size.y / 2);
	}
	if (event_to_process(ev))
		fdf->to_draw = 1;
	reset_event(ev);
	ev->in_use = 0;
}
