/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:18:34 by nboste            #+#    #+#             */
/*   Updated: 2017/01/17 05:00:45 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_event.h"
#include "fdf.h"
#include "fdf_process.h"

static int	event_to_process(t_event *ev)
{
	if (ev->key_nav.keys[KEY_LEFT]
		|| ev->key_nav.keys[KEY_RIGHT] || ev->key_nav.keys[KEY_UP]
		|| ev->key_nav.keys[KEY_DOWN] || ev->key_nav.keys[KEY_PAGEUP]
		|| ev->key_nav.keys[KEY_PAGEDOWN])
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
}

void	fdf_events(t_env *env)
{
	t_event		*ev;
	t_fdf		*fdf;

	ev = &env->event;
	fdf = (t_fdf *)env->app.d;
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
	if (event_to_process(ev))
		fdf->to_draw = 1;
	reset_event(ev);
	ev->in_use = 0;
}
