/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_process.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 05:32:32 by nboste            #+#    #+#             */
/*   Updated: 2016/12/12 22:18:45 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_PROCESS_H
# define FT_FDF_PROCESS_H

#include "ft_fdf_reader.h"
#include "libft.h"

# define DIR_X 0
# define DIR_Y 1

void	fdf_project_iso(t_map *map);

void	fdf_apply_matrix(t_map *map, double **matrix);

void	fdf_translate(t_map *map, char dir, double step);

#endif
