/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:15:04 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 07:00:41 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "ft_fdf_hooks.h"
#include "ft_fdf_matrix.h"

static void	fdf_init_matrix(t_env *env)
{
	env->matrix.rot_left = fdf_get_rotmat(1);
	env->matrix.rot_right = fdf_get_rotmat(-1);
	env->matrix.homo_in = fdf_get_homo(1.2);
	env->matrix.homo_out = fdf_get_homo(0.8);
}

int			fdf_init(t_env *env, int width, int height)
{
	if ((env->mlx = mlx_init()) == NULL)
		return (0);
	if ((env->win.mlx_win = mlx_new_window(env->mlx, width, height, "FDF")) == NULL)
		return (0);
	if ((env->img.mlx_img = mlx_new_image(env->mlx, width, height)) == NULL)
		return (0);
	env->img.data = mlx_get_data_addr(env->img.mlx_img, &env->img.bpp, &env->img.line_size, &env->img.endian);
	mlx_expose_hook(env->win.mlx_win, &fdf_expose_hook, (void *)env);
	mlx_key_hook(env->win.mlx_win, &fdf_key_hook, (void *)env);
	mlx_mouse_hook(env->win.mlx_win, &fdf_mouse_hook, (void *)env);
//	mlx_loop_hook(env->win.mlx_win, &fdf_loop_hook, (void *)env);
	env->win.size.x = width;
	env->win.size.y = height;
	fdf_init_matrix(env);
	return (1);
}

int			fdf_loop(t_env *env)
{
	mlx_loop(env->mlx);
	return (0);
}
