/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:14:27 by nboste            #+#    #+#             */
/*   Updated: 2016/12/13 01:21:56 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_READER_H
# define FT_FDF_READER_H

#include "ft_fdf_error.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
	t_pair	projected;
	t_color	color;
}				t_point;

typedef struct	s_map
{
	t_point	**points;
	int		width;
	int		height;
	t_pair	min;
	t_pair	max;
}				t_map;

t_map	*fdf_get_map(char *path);

#endif
