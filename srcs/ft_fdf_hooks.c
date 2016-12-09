/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:33:02 by nboste            #+#    #+#             */
/*   Updated: 2016/12/09 01:49:25 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_hooks.h"
#include "libft.h"
#include "ft_fdf.h"

int		fdf_expose_hook(void *param)
{
	ft_putendl("EXPOSED");
	param = NULL;
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
