/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:33:02 by nboste            #+#    #+#             */
/*   Updated: 2016/12/09 00:37:59 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_hooks.h"
#include "libft.h"

static	void dn(void *param)
{
	void *lol;

	lol = param;
}

int		fdf_expose_hook(void *param)
{
	ft_putendl("EXPOSED");
	dn(param);
	return (0);
}

int		fdf_key_hook(int keycode, void *param)
{
	ft_putstr("Keycode : ");
	ft_putnbr(keycode);
	ft_putchar('\n');
	dn(param);
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
	dn(param);
	return (0);
}

int		fdf_loop_hook(void *param)
{
	static int i=1;
	if (i%2 == 0)
		dn(param);
	return (0);
}
