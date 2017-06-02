/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:20:26 by nboste            #+#    #+#             */
/*   Updated: 2017/06/02 10:38:16 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_reader.h"

static int	fdf_get_width(char **split)
{
	int i;

	i = 0;
	while (*split++)
		i++;
	return (i);
}

t_color		fdf_getcolorz(int z)
{
	t_color	c;

	if (z <= 0)
	{
		c.r = 0;
		c.g = 0;
		if (z >= -255)
			c.b = z + 255;
		else
			c.b = 0;
	}
	else if (z < 50)
	{
		c.r = 0;
		c.g = z + 45;
		c.b = 0;
	}
	else
	{
		c.r = (z % 200) + 55;
		c.g = (z % 128);
		c.b = (z % 64);
	}
	return (c);
}

static void	fdf_fill_obj(t_3dobject *obj, t_list *lst, int width, t_3dvertex v)
{
	int		x;
	int		y;
	char	*str;

	y = 0;
	obj->faces = NULL;
	while (lst)
	{
		x = -1;
		while (++x < width)
		{
			str = ((*(char ***)lst->content)[x]);
			if (!(ft_isdigit(str[0]) || (str[0] == '-' && ft_isdigit(str[1]))))
				ft_exit("Bad map :')");
			obj->vertexes.v[x + width * y].x = x * v.x;
			obj->vertexes.v[x + width * y].y = y * v.y;
			obj->vertexes.v[x + width * y].z = ft_atoi(str) / v.z;
			if (x < width - 1 && lst->next != NULL)
				fdf_add_faces(x, y, width, &obj->faces);
			free(str);
		}
		y++;
		lst = fdf_free_list(lst);
	}
}

static void	fdf_build_obj(int fd, t_3dobject *o, t_3dvertex v)
{
	char	*line;
	char	**split_line;
	t_list	*list;
	int		width;
	int		i;

	list = NULL;
	width = -1;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		split_line = ft_strsplit(line, ' ');
		free(line);
		if (width != -1 && fdf_get_width(split_line) != width)
			ft_exit("Bad map :'(");
		width = fdf_get_width(split_line);
		ft_lstadd(&list, ft_lstnew(&split_line, sizeof(char ***)));
		i++;
	}
	o->vertexes.size = i * width;
	o->vertexes.v2 = (t_3dvertex *)malloc(sizeof(t_3dvertex) * i * width);
	o->vertexes.v = (t_3dvertex *)malloc(sizeof(t_3dvertex) * i * width);
	if (width == -1 || list->next == 0 || !(o->vertexes.v) || !(o->vertexes.v2))
		ft_exit("Bad map :'(");
	fdf_fill_obj(o, list, width, v);
}

t_3dobject	*fdf_get_obj(char *path)
{
	int			fd;
	t_3dobject	*obj;
	t_3dvertex	v;

	if ((fd = open(path, O_RDONLY)) < 0)
		ft_exit("The file can't be opened.");
	if (!(obj = (t_3dobject *)malloc(sizeof(t_3dobject))))
		ft_exit("Could not allocate memory");
	v.x = 10;
	v.y = 10;
	if (!ft_strcmp("maps/MGDS_WHOLE_WORLD_OCEAN1_XXL.fdf", path)
	|| !ft_strcmp("maps/MGDS_EAST_AFRICAN_RIFT_SYSTEM_OCEAN1_XXL.fdf", path))
		v.z = 20;
	else
		v.z = 1;
	fdf_build_obj(fd, obj, v);
	obj->get_color = &fdf_getcolorz;
	close(fd);
	fdf_set_obj(obj);
	return (obj);
}
