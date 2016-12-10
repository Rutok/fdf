/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_hooks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:26:19 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 06:59:33 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_HOOKS_H
# define FT_FDF_HOOKS_H

# define ESCAPE 53
# define LEFT 123
# define RIGHT 124
# define PLUS 24
# define MINUS 27

int		fdf_expose_hook(void *param);

int		fdf_key_hook(int keycode, void *param);

int		fdf_mouse_hook(int button, int x, int y, void *param);

int		fdf_loop_hook(void *param);

#endif
