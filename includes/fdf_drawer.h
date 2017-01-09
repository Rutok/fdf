/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_drawer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:07:52 by nboste            #+#    #+#             */
/*   Updated: 2017/01/09 18:09:34 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_DRAWER_H
# define FT_FDF_DRAWER_H

#include "libft.h"
#include "fdf.h"

void	fdf_normalize_points(t_env *env);

void	fdf_draw_img(t_env *env);

void	fdf_display_img(t_env *env);

#endif
