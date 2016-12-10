/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 05:16:33 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 05:41:37 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_matrix.h"
#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "ft_fdf_error.h"

double	**fdf_get_rotmat(int dir)
{
	int		i;
	double	**rotmat_left;
	double	o;

	o = ft_degtorad(dir);
	if (!(rotmat_left = (double **)malloc(sizeof(double *) * 3)))
		fdf_exit("Could not allocate memory.");
	i = 0;
	while (i < 3)
		if (!(rotmat_left[i++] = (double*)malloc(sizeof(double) * 3)))
			fdf_exit("Mem");
	rotmat_left[0][0] = cos(o);
	rotmat_left[0][1] = sin(o);
	rotmat_left[0][2] = 0;
	rotmat_left[1][0] = -sin(o);
	rotmat_left[1][1] = cos(o);
	rotmat_left[1][2] = 0;
	rotmat_left[2][0] = 0;
	rotmat_left[2][1] = 0;
	rotmat_left[2][2] = 1;
	return (rotmat_left);
}
