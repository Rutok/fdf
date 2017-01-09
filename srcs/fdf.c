/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:59:28 by nboste            #+#    #+#             */
/*   Updated: 2017/01/09 19:42:31 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_matrix.h"
#include "fdf_reader.h"
#include "fdf_process.h"
#include "fdf_drawer.h"
#include "drawer.h"
#include "fdf_event.h"

static void		init_matrix(t_fdf *fdf)
{
	fdf->matrix.rot_z_pos = fdf_get_rotmat_z(1);
	fdf->matrix.rot_z_neg = fdf_get_rotmat_z(-1);
	fdf->matrix.rot_x_pos = fdf_get_rotmat_x(1);
	fdf->matrix.rot_x_neg = fdf_get_rotmat_x(-1);
	fdf->matrix.rot_y_pos = fdf_get_rotmat_y(1);
	fdf->matrix.rot_y_neg = fdf_get_rotmat_y(-1);
	fdf->matrix.homo_in = fdf_get_homo(1.2);
	fdf->matrix.homo_out = fdf_get_homo(0.8);
}

void	init_app(t_env *env)
{
	t_fdf	*fdf;

	if(!(env->app.d = (void *)malloc(sizeof(t_fdf))))
		ft_exit(MALLOC_FAILED);
	fdf = (t_fdf *)env->app.d;
	init_matrix(fdf);
	fdf->map = fdf_get_map(env->app.argv[1]);
	fdf->to_draw = 0;
	fdf_translate(fdf->map, DIR_Y, -fdf->map->height / 2);
	fdf_translate(fdf->map, DIR_X, -fdf->map->width / 2);
}

int		process_app(void *venv)
{
	t_env	*env;
	t_fdf	*fdf;

	env = (t_env *)venv;
	fdf = (t_fdf *)env->app.d;
	fdf_project_iso(fdf->map);
	fdf_normalize_points(env);
	fdf_draw_img(env);
	env->event.draw = 1;
	drawer_wait_copy(env);
	while (!env->event.exit)
	{
		fdf_events(env);
		if (fdf->to_draw)
		{
			fdf_project_iso(fdf->map);
			fdf_normalize_points(env);
			fdf_draw_img(env);
			env->event.draw = 1;
			drawer_wait_copy(env);
			drawer_clean(&env->rend);
			fdf->to_draw = 0;
		}
	}
	return (1);
}
