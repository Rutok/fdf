/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:59:28 by nboste            #+#    #+#             */
/*   Updated: 2017/02/18 05:10:55 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_matrix.h"
#include "fdf_reader.h"
#include "fdf_process.h"
#include "fdf_drawer.h"
#include "drawer.h"
#include "fdf_event.h"
#include "camera.h"

#define APP_FPS 60

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
	t_fdf		*fdf;
	t_camera	*cam;

	if(!(env->app.d = (void *)malloc(sizeof(t_fdf))))
		ft_exit(MALLOC_FAILED);
	fdf = (t_fdf *)env->app.d;
	init_matrix(fdf);
	fdf->map = fdf_get_map(env->app.argv[1]);
	fdf->to_draw = 0;
	fdf_translate(fdf->map, DIR_Y, -fdf->map->height * 10 / 2);
	fdf_translate(fdf->map, DIR_X, -fdf->map->width * 10 / 2);
	cam = &fdf->scene.camera;
	init_camera(env, ft_degtorad(135), &fdf->scene.camera);
//	SDL_WarpMouseInWindow(NULL, cam->size.x / 2, cam->size.y / 2);
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 10;
	cam->n.x = 0;
	cam->n.y = 1;
	cam->n.z = 0;
	cam->v.x = 0;
	cam->v.y = 0;
	cam->v.z = -1;
	cam->u.x = 1;
	cam->u.y = 0;
	cam->u.z = 0;
	cam->speed = 15;
	cam->sensitivity = 0.04;
//	SDL_ShowCursor(SDL_DISABLE);
//	SDL_SetWindowGrab(env->win.win_sdl, SDL_TRUE);
}

int		process_app(void *venv)
{
	t_env	*env;
	t_fdf	*fdf;
//	int		time;
//	int		etime;

	env = (t_env *)venv;
	fdf = (t_fdf *)env->app.d;
//	time = SDL_GetTicks();
//	fdf->to_draw = 1;
//	env->event.mouse.move = 0;
//	while (!env->event.exit)
//	{
//		etime = SDL_GetTicks() - time;
//		if (etime < 1000 / APP_FPS)
//			SDL_Delay((1000 / APP_FPS) - etime);
//		time += etime;
		fdf_events(env);
		if (fdf->to_draw)
		{
			fdf_draw_img(env);
			drawer_wait_copy(env, &((t_fdf *)env->app.d)->scene.camera);
		//	env->event.draw = 1;
			fdf->to_draw = 0;
		}
//	}
	return (1);
}
