/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:18:34 by nboste            #+#    #+#             */
/*   Updated: 2017/02/19 07:50:15 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_event.h"
#include "fdf.h"
#include "fdf_process.h"
#include <SDL2/SDL.h>

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
	t_2dpair	trig;

	if (!a)
		return;
	trig.x = cos(a);
	trig.y = sin(a);
	tmp.x = ((trig.x + ((1 - trig.x) * n.x * n.x)) * v->x)
		+ ((((1 - trig.x) * n.x * n.y) - (trig.y * n.z)) * v->y)
		+ ((((1 - trig.x) * n.x * n.z) + (trig.y * n.y)) * v->z);
	tmp.y = ((((1 - trig.x) * n.x * n.y) + (trig.y * n.z)) * v->x)
		+ ((trig.x + ((1 - trig.x) * n.y * n.y)) * v->y)
		+ ((((1 - trig.x) * n.y * n.z) - (trig.y * n.x)) * v->z);
	tmp.z = ((((1 - trig.x) * n.x * n.z) - (trig.y * n.y)) * v->x)
		+ ((((1 - trig.x) * n.y * n.z) + (trig.y * n.x)) * v->y)
		+ ((trig.x + ((1 - trig.x) * n.z * n.z)) * v->z);
	*v = tmp;
}

void	fdf_events(t_env *env)
{
	t_event		*ev;
	t_fdf		*fdf;
	t_camera	*cam;
	static t_2ipair mouse;

	ev = &env->event;
	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	ev->in_use = 1;
	if (ev->mouse.move)
	{
		if (mouse.x)
		{
			t_2dpair	d;
			t_3dvertex	z;
			z.x = 0;
			z.y = 0;
			z.z = 1;
			d.x = ev->mouse.pos.x - (cam->size.x / 2);
			d.y = ev->mouse.pos.y - (cam->size.y / 2);
			if (d.x != 0 && d.y != 0)
			{
				d.x *= -cam->sensitivity;
				d.y *= -0.1;
				rotate_3dvertex(&cam->u, z, ft_degtorad(d.x));
				rotate_3dvertex(&cam->n, z, ft_degtorad(d.x));
				rotate_3dvertex(&cam->v, z, ft_degtorad(d.x));
				rotate_3dvertex(&cam->n, cam->u, ft_degtorad(d.y));
				rotate_3dvertex(&cam->v, cam->u, ft_degtorad(d.y));
				SDL_WarpMouseInWindow(NULL, cam->size.x / 2, cam->size.y / 2);
			}
		}
		else
		{
			mouse.x = ev->mouse.pos.x;
			mouse.y = ev->mouse.pos.y;
		}
	}
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
	if (event_to_process(ev))
		fdf->to_draw = 1;
	reset_event(ev);
	ev->in_use = 0;
}
