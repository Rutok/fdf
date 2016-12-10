/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_process.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 05:32:32 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 05:39:35 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_PROCESS_H
# define FT_FDF_PROCESS_H

#include "ft_fdf_reader.h"
#include "libft.h"

void	fdf_project_iso(t_map *map);

void	fdf_apply_matrix(t_map *map, double **matrix);

#endif
