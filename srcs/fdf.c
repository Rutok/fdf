/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:59:28 by nboste            #+#    #+#             */
/*   Updated: 2017/05/28 13:48:32 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_reader.h"
#include "drawer.h"
#include "fdf_event.h"
#include "camera.h"
#include "scene.h"

void	init_app(t_env *env)
{
	t_fdf		*fdf;
	t_camera	*cam;
	t_3dobject	obj;

	if(!(env->app.d = (void *)malloc(sizeof(t_fdf))))
		ft_exit(MALLOC_FAILED);
	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	fdf->scene.objects = NULL;
	ft_lstadd(&(fdf->scene.objects), ft_lstnew(&(obj), sizeof(t_3dobject)));
	(fdf->scene.objects->content) = fdf_get_obj(env->app.argv[1]);
	init_camera(env, ft_degtorad(90), &fdf->scene.camera);
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 0;
	cam->n.x = 1;
	cam->n.y = 0;
	cam->n.z = 0;
	cam->v.x = 0;
	cam->v.y = 0;
	cam->v.z = 1;
	cam->u.x = 0;
	cam->u.y = -1;
	cam->u.z = 0;
	cam->speed = 1;
	cam->sensitivity = 0.04;
	cam->projection = perspective;
	cam->range = 500;
	fdf->to_draw = 1;
}

int		process_app(void *venv)
{
	t_env	*env;
	t_fdf	*fdf;

	env = (t_env *)venv;
	fdf = (t_fdf *)env->app.d;
	fdf_events(env);
	if (fdf->to_draw)
	{
		draw_scene(&fdf->scene, env);
		drawer_wait_copy(env, &((t_fdf *)env->app.d)->scene.camera);
		fdf->to_draw = 0;
	}
	return (1);
}

void	destroy_app(t_env *env)
{
	t_fdf		*fdf;

	fdf = (t_fdf *)env->app.d;
	free(((fdf)->scene.camera.z_buffer));
	free(fdf);
}
