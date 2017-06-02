/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_reader_utility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 09:15:04 by nboste            #+#    #+#             */
/*   Updated: 2017/06/02 09:38:23 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_reader.h"

t_list	*fdf_free_list(t_list *lst)
{
	t_list	*next;

	next = lst->next;
	free(*(char ***)lst->content);
	free((char ***)lst->content);
	free(lst);
	return (next);
}

void	fdf_add_faces(int x, int y, int width, t_list **lst)
{
	t_face	f;

	f.v1 = x + width * y;
	f.v2 = (x + 1) + width * y;
	f.v3 = x + width * (y + 1);
	ft_lstadd(lst, ft_lstnew(&f, sizeof(t_face)));
	f.v1 = (x + 1) + width * (y + 1);
	f.v2 = (x + 1) + width * y;
	f.v3 = x + width * (y + 1);
	ft_lstadd(lst, ft_lstnew(&f, sizeof(t_face)));
}

void	fdf_set_obj(t_3dobject *obj)
{
	obj->pos.x = 0;
	obj->pos.y = 0;
	obj->pos.z = 0;
	obj->uvn.n.x = 1;
	obj->uvn.n.y = 0;
	obj->uvn.n.z = 0;
	obj->uvn.v.x = 0;
	obj->uvn.v.y = 0;
	obj->uvn.v.z = 1;
	obj->uvn.u.x = 0;
	obj->uvn.u.y = 1;
	obj->uvn.u.z = 0;
	obj->scale.x = 1;
	obj->scale.y = 1;
	obj->scale.z = 1;
}
