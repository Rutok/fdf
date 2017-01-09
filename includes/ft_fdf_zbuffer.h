/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_zbuffer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 00:56:05 by nboste            #+#    #+#             */
/*   Updated: 2016/12/15 01:48:46 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_ZBUFFER_H
# define FT_FDF_ZBUFFER_H

# include "ft_fdf_reader.h"
# include "libft.h"

# define ZB_MIN_DEPTH -1
# define ZB_MAX_DEPTH 1

typedef struct	s_zbuffer_point
{
	t_color		color;
	double		depth;
}				t_zbuffer_point;

typedef struct	s_zbuffer
{
	t_zbuffer_point		**points;
	t_pair				size;
}				t_zbuffer;

t_zbuffer	*init_zbuffer(int width, int height);

void		reset_zbuffer(t_zbuffer *b, t_color bckgrnd);

#endif
