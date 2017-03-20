/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:14:27 by nboste            #+#    #+#             */
/*   Updated: 2017/03/20 16:07:10 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_READER_H
# define FT_FDF_READER_H

#include "error.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include "types.h"

typedef struct	s_fdfpoint
{
	t_3dvertex	pos;
	t_3dvertex	c_space;
	t_2dpair	c_view;
	double		d;
	t_color		color;
	t_bool		draw;
}				t_fdfpoint;

typedef struct	s_map
{
	t_fdfpoint	**points;
	int			width;
	int			height;
}				t_map;

t_3dobject		*fdf_get_obj(char *path);

#endif
