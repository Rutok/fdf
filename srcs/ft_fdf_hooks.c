/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:33:02 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 07:00:07 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_hooks.h"
#include "libft.h"
#include "ft_fdf.h"
#include "ft_fdf_process.h"
#include "ft_fdf_drawer.h"

int		fdf_expose_hook(void *param)
{
	static int	c;
	t_map		*map;
	t_env		*env;

	env = (t_env *)param;
	if (!c)
	{
		c++;
		map = fdf_get_map(env->path);
		env->map = map;
		fdf_project_iso(map);
		fdf_draw_img(env);
		fdf_display_img(env);
	}
	return (0);
}

int		fdf_key_hook(int keycode, void *param)
{
	t_env *env;

	env = (t_env *)param;
	if (keycode == ESCAPE)
		fdf_exit(NULL);
	else if (keycode == LEFT)
		fdf_apply_matrix(env->map, env->matrix.rot_left);
	else if (keycode == RIGHT)
		fdf_apply_matrix(env->map, env->matrix.rot_right);
	else if (keycode == PLUS)
		fdf_apply_matrix(env->map, env->matrix.homo_in);
	else if (keycode == MINUS)
		fdf_apply_matrix(env->map, env->matrix.homo_out);
	else
		return (0);
	fdf_project_iso(env->map);
	fdf_draw_img(env);
	fdf_display_img(env);
	return (0);
}

int		fdf_mouse_hook(int button, int x, int y, void *param)
{
	ft_putstr("Button : ");
	ft_putnbr(button);
	ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar(' ');
	ft_putnbr(y);
	ft_putchar('\n');
	param = NULL;
	return (0);
}

int		fdf_loop_hook(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	return (0);
}
