/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:18:34 by nboste            #+#    #+#             */
/*   Updated: 2017/03/24 20:14:15 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_event.h"
#include "fdf.h"
#include "fdf_process.h"
#include <SDL2/SDL.h>
#include "vertex_utility.h"
#include "camera.h"

void	fdf_events(t_env *env)
{
	t_event		*ev;
	t_fdf		*fdf;
	t_camera	*cam;
	static t_2dpair off;

	ev = &env->event;
	fdf = (t_fdf *)env->app.d;
	cam = &fdf->scene.camera;
	t_3dvertex	z;
	z.x = 0;
	z.y = 0;
	z.z = 1;

	t_3dobject *obj = (t_3dobject *)fdf->scene.objects->next->content;
	if (ev->mouse.move)
	{
		t_2dpair	d;
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

			rotate_3dvertex(&obj->uvn.u, obj->uvn.v, ft_degtorad(d.x));
			  rotate_3dvertex(&obj->uvn.n, obj->uvn.v, ft_degtorad(d.x));
			  rotate_3dvertex(&obj->uvn.n, z, ft_degtorad(-d.y));
			  rotate_3dvertex(&obj->uvn.v, z, ft_degtorad(-d.y));
			  rotate_3dvertex(&obj->uvn.u, z, ft_degtorad(-d.y));
			SDL_WarpMouseInWindow(NULL, cam->size.x / 2, cam->size.y / 2);
			fdf->to_draw = 1;
		}
	}
	if (ev->keys[SDL_SCANCODE_ESCAPE])
		ev->exit = 1;
	if (ev->keys[SDL_SCANCODE_W])
	{
		obj->pos.x += cam->n.x * cam->speed;
		obj->pos.y += cam->n.y * cam->speed;
		obj->pos.z += cam->n.z * cam->speed;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_A])
	{
		obj->pos.x -= cam->u.x * cam->speed;
		obj->pos.y -= cam->u.y * cam->speed;
		obj->pos.z -= cam->u.z * cam->speed;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_S])
	{
		obj->pos.x -= cam->n.x * cam->speed;
		obj->pos.y -= cam->n.y * cam->speed;
		obj->pos.z -= cam->n.z * cam->speed;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_D])
	{
		obj->pos.x += cam->u.x * cam->speed;
		obj->pos.y += cam->u.y * cam->speed;
		obj->pos.z += cam->u.z * cam->speed;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_O])
	{
		fdf->range *= 1.1;
		fdf->scene.camera.range *= 1.01;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_L])
	{
		fdf->range *= .9;
		fdf->scene.camera.range *= .09;
		fdf->to_draw = 1;
	}
	static int tmp_u;
	if (ev->keys[SDL_SCANCODE_U])
		tmp_u = 1;
	else if (tmp_u)
	{
		init_camera(env, fdf->scene.camera.fov.y * 1.1, &fdf->scene.camera);
	//	rotate_3dvertex(&(((t_3dobject *)fdf->scene.objects->next->content)->uvn.v), (((t_3dobject *)fdf->scene.objects->next->content)->uvn.u), ft_degtorad(1));
	//	rotate_3dvertex(&(((t_3dobject *)fdf->scene.objects->next->content)->uvn.u), z, ft_degtorad(1));
	//	rotate_3dvertex(&(((t_3dobject *)fdf->scene.objects->next->content)->uvn.n), (((t_3dobject *)fdf->scene.objects->next->content)->uvn.u), ft_degtorad(1));
		fdf->to_draw = 1;
		tmp_u = 0;
	}
	static int tmp_j;
	if (ev->keys[SDL_SCANCODE_J])
		tmp_j = 1;
	else if (tmp_j)
	{
		init_camera(env, fdf->scene.camera.fov.y * 0.9, &fdf->scene.camera);
	//	rotate_3dvertex(&(((t_3dobject *)fdf->scene.objects->next->content)->uvn.v), z, ft_degtorad(-1));
	//	rotate_3dvertex(&(((t_3dobject *)fdf->scene.objects->next->content)->uvn.u), z, ft_degtorad(-1));
	//	rotate_3dvertex(&(((t_3dobject *)fdf->scene.objects->next->content)->uvn.n), z, ft_degtorad(-1));
		fdf->to_draw = 1;
		tmp_j = 0;
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
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_K])
	{
		cam->speed *= .9;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_UP])
	{
		((t_3dobject *)fdf->scene.objects->content)->scale.z *= 1.1;
		fdf->to_draw = 1;
	}
	if (ev->keys[SDL_SCANCODE_DOWN])
	{
		((t_3dobject *)fdf->scene.objects->content)->scale.z *= .9;
		fdf->to_draw = 1;
	}

}
