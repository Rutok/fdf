/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:20:26 by nboste            #+#    #+#             */
/*   Updated: 2017/05/29 16:44:14 by nboste           ###   ########.fr       */
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

/*static t_color	fdf_c(char *str, int z)
{
	char	*c;
	int		val;
	int		i;
	t_color	color;

	val = 0;
	i = 0;
	if ((c = ft_strchr(str, 'x')))
	{
		c++;
		while (c[i] != '\0' && i < 6)
		{
			c[i] = ft_toupper(c[i]);
			val = val << 4;
			if (c[i] >= '0' && c[i] <= '9')
				val += c[i] - '0';
			else if (c[i] >= 'A' && c[i] <= 'F')
				val += 10 + c[i] - 'A';
			else
				ft_exit("Bad map colors !!!");
			i++;
		}
		color.r = val >> 16;
		color.g = (val & 0xFF00) >> 8;
		color.b = (val & 0xFF);
	}
	else
		color = fdf_getcolorz(z);
	return (color);
}*/

static void	fdf_fill_obj(t_3dobject *obj, t_list *lst, int width, t_3dvertex v)
{
	int		x;
	int		y;
	char	*str;
	t_list	*tmp;
	t_face	f;

	y = 0;
	obj->faces = NULL;
	while (lst)
	{
		x = 0;
		while (x < width)
		{
			str = ((*(char ***)lst->content)[x]);
			if (!(ft_isdigit(str[0]) || (str[0] == '-' && ft_isdigit(str[1]))))
				ft_exit("Bad map :')");
			obj->vertexes.v[x + width * y].x = x * v.x;
			obj->vertexes.v[x + width * y].y = y * v.y;
			obj->vertexes.v[x + width * y].z = ft_atoi(str) / v.z;
			if (x < width - 1 && lst->next != NULL)
			{
				f.v1 = x + width * y;
				f.v2 = (x + 1) + width * y;
				f.v3 = x + width * (y + 1);
				ft_lstadd(&obj->faces, ft_lstnew(&f, sizeof(t_face)));
				f.v1 = (x + 1) + width * (y + 1);
				f.v2 = (x + 1) + width * y;
				f.v3 = x + width * (y + 1);
				ft_lstadd(&obj->faces, ft_lstnew(&f, sizeof(t_face)));
			}
			free(str);
			x++;
		}
		y++;
		tmp = lst;
		lst = lst->next;
		free(*(char ***)tmp->content);
		free((char ***)tmp->content);
		free(tmp);
	}
}

static void	fdf_build_obj(int fd, t_3dobject *obj, t_3dvertex v)
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
		if (width == -1)
			width = fdf_get_width(split_line);
		if (fdf_get_width(split_line) != width)
			ft_exit("Bad map :'(");
		ft_lstadd(&list, ft_lstnew(&split_line, sizeof(char ***)));
		i++;
	}
	obj->vertexes.size = i * width;
	if (width == -1 || list->next == 0 || !(obj->vertexes.v = (t_3dvertex *)malloc(sizeof(t_3dvertex) * i * width)) || !(obj->vertexes.v2 = (t_3dvertex *)malloc(sizeof(t_3dvertex) * i * width)))
		ft_exit("Bad map :'(");
	fdf_fill_obj(obj, list, width, v);
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
	obj->getColor = &fdf_getcolorz;
	close(fd);
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
	return (obj);
}
