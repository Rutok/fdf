/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:15:04 by nboste            #+#    #+#             */
/*   Updated: 2016/12/09 00:29:25 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "ft_fdf_hooks.h"

int		fdf_init(t_env *env, int width, int height)
{
	if ((env->mlx = mlx_init()) == NULL)
		return (0);
	if ((env->win = mlx_new_window(env->mlx, width, height, "FDF")) == NULL)
		return (0);
	if ((env->img = mlx_new_image(env->mlx, width, height)) == NULL)
		return (0);
	mlx_expose_hook(env->win, &fdf_expose_hook, env);
	mlx_key_hook(env->win, &fdf_key_hook, env);
	mlx_mouse_hook(env->win, &fdf_mouse_hook, env);
//	mlx_loop_hook(env->win, &fdf_loop_hook, env);
	return (1);
}

int		fdf_loop(t_env *env)
{
	mlx_loop(env->mlx);
	return (0);
}
