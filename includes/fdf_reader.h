/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:14:27 by nboste            #+#    #+#             */
/*   Updated: 2017/06/02 09:37:11 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_READER_H
# define FT_FDF_READER_H

# include "error.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include "types.h"

t_3dobject		*fdf_get_obj(char *path);

t_color			fdf_getcolorz(int z);

t_list			*fdf_free_list(t_list *lst);

void			fdf_add_faces(int x, int y, int width, t_list **l);

void			fdf_set_obj(t_3dobject *obj);

#endif
