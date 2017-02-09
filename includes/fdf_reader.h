/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:14:27 by nboste            #+#    #+#             */
/*   Updated: 2017/02/09 01:54:22 by nboste           ###   ########.fr       */
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
	double	x;
	double	y;
	double	z;
	t_2dpair	projected;
	double		d;
	t_color	color;
}				t_point;

typedef struct	s_map
{
	t_point	**points;
	int		width;
	int		height;
	t_2ipair	min;
	t_2ipair	max;
}				t_map;

t_map	*fdf_get_map(char *path);

#endif
