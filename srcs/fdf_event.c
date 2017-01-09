/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:18:34 by nboste            #+#    #+#             */
/*   Updated: 2017/01/09 19:45:29 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_event.h"
#include "fdf.h"
#include "fdf_process.h"

static int	event_to_process(t_event *ev)
{
	if (ev->move_left || ev->move_right || ev->move_up
			|| ev->move_down || ev->plus || ev->minus)
		return (1);
	return (0);
}

static void	reset_event(t_event *ev)
{
	ev->move_left = 0;
	ev->move_right = 0;
	ev->move_up = 0;
	ev->move_down = 0;
	ev->plus = 0;
	ev->minus = 0;
}

void	fdf_events(t_env *env)
{
	t_event		*ev;
	t_fdf		*fdf;

	ev = &env->event;
	fdf = (t_fdf *)env->app.d;
	if (ev->move_left)
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_z_pos);
	if (ev->move_right)
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_z_neg);
	if (ev->move_up)
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_x_pos);
	if (ev->move_down)
		fdf_apply_matrix(fdf->map, fdf->matrix.rot_x_neg);
	if (ev->plus)
		fdf_apply_matrix(fdf->map, fdf->matrix.homo_in);
	if (ev->minus)
		fdf_apply_matrix(fdf->map, fdf->matrix.homo_out);
	if (event_to_process(ev))
		fdf->to_draw = 1;
	if (fdf->to_draw == 1)
	reset_event(ev);
}
