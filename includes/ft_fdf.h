/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:12:30 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 05:34:04 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

#include <stdlib.h>
#include "libft.h"
#include "ft_fdf_reader.h"
#include "mlx.h"

typedef struct	s_matrix
{
	double	**rot_left;
	double	**rot_right;
}				t_matrix;

typedef struct	s_win
{
	void	*mlx_win;
	t_pair	size;
}				t_win;

typedef struct	s_img
{
	void	*mlx_img;
	char	*data;
	int		bpp;
	int		line_size;
	int		endian;
}				t_img;

typedef struct	s_env
{
	void		*mlx;
	t_win		win;
	t_img		img;
	t_map		*map;
	t_matrix	matrix;
	char		*path;
}				t_env;

int				fdf_init(t_env *env, int width, int height);

int				fdf_loop(t_env *env);

#endif
