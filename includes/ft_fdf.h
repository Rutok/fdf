/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:12:30 by nboste            #+#    #+#             */
/*   Updated: 2016/12/08 23:24:28 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

#include <stdlib.h>

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	void	*img;
}				t_env;

int				fdf_init(t_env *env, int width, int height);

int				fdf_loop(t_env *env);

#endif
