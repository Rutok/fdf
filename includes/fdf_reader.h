/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:14:27 by nboste            #+#    #+#             */
/*   Updated: 2017/02/24 21:19:43 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_READER_H
# define FT_FDF_READER_H

#include "error.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include "types.h"

typedef struct	s_point
{
	t_3dvertex	pos;
	t_3dvertex	c_space;
	t_2dpair	c_view;
	double		d;
	t_color		color;
	t_bool		draw;
}				t_point;

typedef struct	s_map
{
	t_point		**points;
	int			width;
	int			height;
}				t_map;

t_map	*fdf_get_map(char *path);

#endif
