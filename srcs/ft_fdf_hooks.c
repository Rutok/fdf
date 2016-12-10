/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:33:02 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 02:21:18 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_hooks.h"
#include "libft.h"
#include "ft_fdf.h"
#include "ft_fdf_process.h"
#include "ft_fdf_drawer.h"

int		fdf_expose_hook(void *param)
{
	t_map	*map;
	t_env	*env;

	map = fdf_get_map("maps/42.fdf");
	env = (t_env *)param;
	env->map = map;
	fdf_project_iso(map);
	fdf_draw_img(env);
	fdf_display_img(env);
	ft_putendl("EXPOSED");
	return (0);
}

int		fdf_key_hook(int keycode, void *param)
{
	param = NULL;
	if (keycode == 53)
		exit(1);
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

/*int		fdf_loop_hook(void *param)
{
	param = NULL;
	return (0);
}*/
