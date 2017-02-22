/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:52 by nboste            #+#    #+#             */
/*   Updated: 2017/02/22 04:24:59 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_DRAWER_H
# define FT_FDF_DRAWER_H

#include "libft.h"
#include "fdf.h"

void	fdf_draw_img(t_env *env);

void	fdf_draw_line(t_point* p1, t_point *p2, t_camera *cam);

t_color	fdf_getcolor(int z);

#endif
