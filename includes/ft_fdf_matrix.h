/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_matrix.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 05:17:17 by nboste            #+#    #+#             */
/*   Updated: 2016/12/13 02:11:57 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_MATRIX_H
# define FT_FDF_MATRIX_H

double	**fdf_get_rotmat_z(double angle_deg);

double	**fdf_get_rotmat_x(double angle_deg);

double	**fdf_get_rotmat_y(double angle_deg);

double	**fdf_get_homo(double k);

#endif
