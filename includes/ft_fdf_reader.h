/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:14:27 by nboste            #+#    #+#             */
/*   Updated: 2016/12/09 04:38:26 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_READER_H
# define FT_FDF_READER_H

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
	int	xp;
	int	yp;
}				t_point;

typedef struct	s_map
{
	t_point	**points;
	int		width;
	int		height;
}				t_map;

t_map	*fdf_get_map(char *path);

#endif
