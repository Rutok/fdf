/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:59:40 by nboste            #+#    #+#             */
/*   Updated: 2017/06/02 09:26:39 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "types.h"
# include "fdf_reader.h"
# include "error.h"

# define MALLOC_FAILED "Error on malloc."

typedef struct		s_fdf
{
	t_bool		to_draw;
	t_scene		scene;
	double		range;
}					t_fdf;

void				init_app(t_env *env);

int					process_app(void *env);

void				destroy_app(t_env *env);

#endif
