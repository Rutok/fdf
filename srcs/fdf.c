/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:59:28 by nboste            #+#    #+#             */
/*   Updated: 2017/03/24 20:13:49 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_reader.h"
#include "fdf_process.h"
#include "fdf_drawer.h"
#include "drawer.h"
#include "fdf_event.h"
#include "camera.h"
#include "scene.h"
#include "obj_parser.h"

void	init_app(t_env *env)
{
	t_fdf		*fdf;
	t_camera	*cam;
	t_3dobject	*obj;

	if(!(env->app.d = (void *)malloc(sizeof(t_fdf))))
		ft_exit(MALLOC_FAILED);
	obj = malloc(sizeof(t_3dobject));
	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	fdf->scene.objects = NULL;
	ft_lstadd(&(fdf->scene.objects), ft_lstnew((obj), sizeof(t_3dobject)));
	obj = (t_3dobject *)fdf->scene.objects->content;
	obj->faces = parse_obj(env->app.argv[1]);
	obj->pos.x = 0;
	obj->pos.y = 0;
	obj->pos.z = 0;
	obj->uvn.n.x = 1;
	obj->uvn.n.y = 0;
	obj->uvn.n.z = 0;
	obj->uvn.v.x = 0;
	obj->uvn.v.y = 1;
	obj->uvn.v.z = 0;
	obj->uvn.u.x = 0;
	obj->uvn.u.y = 0;
	obj->uvn.u.z = 1;
	obj->scale.x = 0.5;
	obj->scale.y = 0.5;
	obj->scale.z = 5;
	ft_lstadd(&(fdf->scene.objects), ft_lstnew((obj), sizeof(t_3dobject)));
	(fdf->scene.objects->content) = fdf_get_obj(env->app.argv[2]);
	fdf->range = 500000;
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
	fdf->to_draw = 1;
}

int		process_app(void *venv)
{
	t_env	*env;
	t_fdf	*fdf;

	env = (t_env *)venv;
	fdf = (t_fdf *)env->app.d;
	fdf_events(env);
	fdf->scene.camera.pos = ((t_3dobject *)(fdf->scene.objects->next->content))->pos;
//	((t_3dobject *)(fdf->scene.objects->next->content))->uvn.u = fdf->scene.camera.u;
//	((t_3dobject *)(fdf->scene.objects->next->content))->uvn.v = fdf->scene.camera.v;
//	((t_3dobject *)(fdf->scene.objects->next->content))->uvn.n = fdf->scene.camera.n;
	fdf->scene.camera.pos.x -= fdf->scene.camera.n.x * 10;
	fdf->scene.camera.pos.y -= fdf->scene.camera.n.y * 10;
	fdf->scene.camera.pos.z -= fdf->scene.camera.n.z * 10;
	fdf->scene.camera.pos.x += fdf->scene.camera.v.x * 8;
	fdf->scene.camera.pos.y += fdf->scene.camera.v.y * 8;
	fdf->scene.camera.pos.z += fdf->scene.camera.v.z * 8;
	fdf->scene.camera.pos.x -= fdf->scene.camera.u.x * 8;
	fdf->scene.camera.pos.y -= fdf->scene.camera.u.y * 8;
	fdf->scene.camera.pos.z -= fdf->scene.camera.u.z * 8;

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
